#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <time.h>
#include <ESP32Servo.h>
#include <Preferences.h>

// Selected UI: Main
#include "ui/ui_main.h"

const char* ssid     = "Extender-G-FA88";
const char* password = "jritucr4nff7u";

WebServer server(80);
Preferences preferences;

// Servos
Servo servo1;
Servo servo2;
Servo servo3;
const int PIN_SERVO1 = 25;
const int PIN_SERVO2 = 26;
const int PIN_SERVO3 = 27;
const int PIN_LED = 13;
bool pin13State = false;

// Servo Config (270 degree servo, 500-2500us usually covers full range)
// Logic: 0 deg = 100% (Strong), 270 deg = 0% (Weak/Rest)
const int MIN_US = 500;
const int MAX_US = 2500;
const int REF_ANGLE = 270; // 0% Strength

// State Machine
enum State { IDLE, SQUEEZING, HOLDING, RELEASING, WAIT_CYCLE, PAUSED };
State currentState = IDLE;

unsigned long stateStartTime = 0;
float holdTimeSec = 0.5; // Default 0.5s
float reachTimeSec = 0.5; // Default 0.5s
int targetStrength = 50; // 0-100%
int targetCount = 3;
int currentCycle = 0;

void setAllServos(int angle) {
  servo1.write(angle);
  servo2.write(angle);
  servo3.write(angle);
}

// NTP Settings
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 9 * 3600;
const int   daylightOffset_sec = 0;

// Root handler
void handleRoot() {
  String html = html_main; // Copy raw literal to String
  html.replace("{{BUILD_TIME}}", __DATE__ " " __TIME__);
  server.send(200, "text/html", html);
}

// API Endpoints
void handleApiStart() {
  if (server.hasArg("str")) targetStrength = server.arg("str").toInt();
  if (server.hasArg("cnt")) targetCount = server.arg("cnt").toInt();
  
  Serial.printf("[API] Start: Str=%d%%, Cnt=%d\n", targetStrength, targetCount);
  
  currentState = SQUEEZING;
  currentCycle = 0;
  stateStartTime = millis();
  
  // Ensure proper start from open position for ramping
  setAllServos(REF_ANGLE);
  
  server.send(200, "text/plain", "OK");
}

void handleApiStop() {
  Serial.println("[API] Stop");
  currentState = IDLE;
  setAllServos(REF_ANGLE); // Return to safe pos
  server.send(200, "text/plain", "OK");
}

void handleApiSettings() {
  if (server.hasArg("hold")) {
    holdTimeSec = server.arg("hold").toFloat();
    preferences.putFloat("hold", holdTimeSec);
    Serial.printf("[API] Hold: %.2fs\n", holdTimeSec);
  }
  if (server.hasArg("reach")) {
    reachTimeSec = server.arg("reach").toFloat();
    preferences.putFloat("reach", reachTimeSec);
    Serial.printf("[API] Reach: %.2fs\n", reachTimeSec);
  }
  
  // Return JSON
  String json = "{";
  json += "\"hold\":" + String(holdTimeSec) + ",";
  json += "\"reach\":" + String(reachTimeSec) + ",";
  json += "\"pin13\":" + String(pin13State ? 1 : 0);
  json += "}";
  server.send(200, "application/json", json);
}

void handleApiPin13() {
  if(server.hasArg("val")) {
    int v = server.arg("val").toInt();
    pin13State = (v == 1);
    digitalWrite(PIN_LED, pin13State ? HIGH : LOW);
    preferences.putBool("pin13", pin13State);
    Serial.printf("[API] Pin 13: %d\n", pin13State);
  }
  server.send(200, "text/plain", pin13State ? "1" : "0");
}

void handleApiStatus() {
  String s = "IDLE";
  if(currentState == SQUEEZING) s = "SQUEEZING";
  if(currentState == HOLDING) s = "HOLDING";
  if(currentState == RELEASING) s = "RELEASING";
  if(currentState == WAIT_CYCLE) s = "WAIT_CYCLE";
  if(currentState == PAUSED) s = "PAUSED";
  
  String json = "{";
  json += "\"state\":\"" + s + "\",";
  json += "\"cycle\":" + String(currentCycle) + ",";
  json += "\"total\":" + String(targetCount) + ",";
  json += "\"hold\":" + String(holdTimeSec) + ",";
  json += "\"reach\":" + String(reachTimeSec) + ",";
  json += "\"str\":" + String(targetStrength) + ",";
  json += "\"elap\":" + String(millis() - stateStartTime);
  json += "}";
  server.send(200, "application/json", json);
}

void handleApiPause() {
  currentState = PAUSED;
  setAllServos(REF_ANGLE); // Safe pos
  server.send(200, "text/plain", "OK");
}

void handleApiResume() {
  if (currentState == PAUSED) {
    currentState = SQUEEZING; // Resume from start of squeeze for safety/simplicity
    stateStartTime = millis(); 
  }
  server.send(200, "text/plain", "OK");
}

void handleApiCancel() {
  currentState = IDLE;
  currentCycle = 0;
  setAllServos(REF_ANGLE);
  server.send(200, "text/plain", "OK");
}

void handleApiManual() {
  if (server.hasArg("val")) {
    int angle = server.arg("val").toInt();
    // Manual control overrides everything
    currentState = IDLE; 
    setAllServos(angle);
    Serial.printf("[API] Manual: %d deg\n", angle);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  
  // Preferences
  // Preferences
  preferences.begin("job", false);
  holdTimeSec = preferences.getFloat("hold", 0.5);
  reachTimeSec = preferences.getFloat("reach", 0.5);
  pin13State = preferences.getBool("pin13", false);
  
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, pin13State ? HIGH : LOW);
  
  // Servo Setup
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);
  servo3.setPeriodHertz(50);
  
  servo1.attach(PIN_SERVO1, MIN_US, MAX_US);
  servo2.attach(PIN_SERVO2, MIN_US, MAX_US);
  servo3.attach(PIN_SERVO3, MIN_US, MAX_US);
  
  // Initial Position: 270 degrees (0%)
  setAllServos(REF_ANGLE);
  
  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  
  // Time Sync
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  // Routes
  server.on("/", handleRoot);
  server.on("/api/start", handleApiStart);
  server.on("/api/stop", handleApiPause); // Stop button now just Pauses
  server.on("/api/pause", handleApiPause);
  server.on("/api/resume", handleApiResume);
  server.on("/api/cancel", handleApiCancel);
  server.on("/api/cancel", handleApiCancel);
  server.on("/api/status", handleApiStatus);
  server.on("/api/settings", handleApiSettings);
  server.on("/api/pin13", handleApiPin13);
  server.on("/api/manual", handleApiManual);
  server.onNotFound([](){ server.send(404, "text/plain", "Not Found"); });

  server.begin();
  
  Serial.println("=================================");
  Serial.println("ONIGIRI MACHINE (Main) READY");
  Serial.printf("Settings: Hold=%.2fs, Reach=%.2fs\n", holdTimeSec, reachTimeSec);
  Serial.print("Access URL: http://");
  Serial.println("=================================");
}



// Improved Loop Logic
void loop() {
  server.handleClient();
  
  unsigned long now = millis();
  static unsigned long cycleStartTime = 0;

  switch (currentState) {
    case IDLE:
      break;
      
    case SQUEEZING:
      // Mark start of this cycle if new
      if (cycleStartTime == 0 || now - cycleStartTime > 5000) { // Safety reset
         cycleStartTime = now; 
      }
      
      {
         // Ramping Logic
         // Target Angle: 0% = 270, 100% = 0
         int targetAngle = 270 - (270 * targetStrength / 100);
         
         // Elapsed since state start
         unsigned long elapsed = now - stateStartTime;
         unsigned long duration = reachTimeSec * 1000;
         
         if (duration == 0) duration = 1; // avoid div0
         
         if (elapsed >= duration) {
           // Finished reaching
           setAllServos(targetAngle);
           stateStartTime = now;
           currentState = HOLDING;
           Serial.println("State: HOLDING");
         } else {
           // Interpolate: Map elapsed time to angle range
           int currentAngle = map(elapsed, 0, duration, REF_ANGLE, targetAngle);
           setAllServos(currentAngle);
         }
      }
      break;
      
    case HOLDING:
      // Keep holding until time
      if (now - stateStartTime >= (holdTimeSec * 1000)) {
        setAllServos(REF_ANGLE);
        currentState = RELEASING;
        stateStartTime = now; 
        Serial.println("State: RELEASING");
      }
      break;
      
    case RELEASING:
      // Wait until Total Cycle Time is passed
      // Total Cycle = Reach (var) + Hold (var) + Release (fixed 0.5s for now?)
      // Actually user wanted 1.5s total cycle before.
      // Now customizable.
      // Let's say RELEASING takes 0.5s to return.
      // Total dynamic cycle logic handling?
      // Or just simple state transitions?
      
      // Let's make RELEASING just a quick return state.
      if (now - stateStartTime >= 300) { // 0.3s buffer (Fastest Release)
        currentState = WAIT_CYCLE;
      }
      break;
      
    case PAUSED:
      // Do nothing, wait for Resume or Cancel
      break;
      
   case WAIT_CYCLE:
      currentCycle++;
      if (currentCycle < targetCount) {
        cycleStartTime = now; // Mark start of next
        stateStartTime = now;
        currentState = SQUEEZING; 
      } else {
        currentState = IDLE;
      }
      break;
  }
}
