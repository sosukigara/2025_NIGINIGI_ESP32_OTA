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

// Servo Config (270 degree servo, 500-2500us usually covers full range)
// Logic: 0 deg = 100% (Strong), 270 deg = 0% (Weak/Rest)
const int MIN_US = 500;
const int MAX_US = 2500;
const int REF_ANGLE = 270; // 0% Strength

// State Machine
enum State { IDLE, SQUEEZING, HOLDING, RELEASING, WAIT_CYCLE };
State currentState = IDLE;

unsigned long stateStartTime = 0;
float holdTimeSec = 0.5; // Default 0.5s
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
  
  // Calculate target angle based on strength
  // 0% = 270 deg, 100% = 0 deg
  // angle = 270 - (270 * strength / 100)
  int angle = 270 - (270 * targetStrength / 100);
  setAllServos(angle);
  
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
    Serial.printf("[API] Hold Time Updated: %.2fs\n", holdTimeSec);
  }
  server.send(200, "text/plain", String(holdTimeSec));
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
  preferences.begin("job", false);
  holdTimeSec = preferences.getFloat("hold", 0.5);
  
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
  server.on("/api/stop", handleApiStop);
  server.on("/api/settings", handleApiSettings);
  server.on("/api/manual", handleApiManual);
  server.onNotFound([](){ server.send(404, "text/plain", "Not Found"); });

  server.begin();
  
  Serial.println("=================================");
  Serial.println("ONIGIRI MACHINE (Main) READY");
  Serial.printf("Hold Time: %.2fs\n", holdTimeSec);
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
      if (now - stateStartTime > 100) { // minimal debounce for state entry? No.
         // Logic handled inside case logic below
      }
      // Entry logic needs to happen once.
      // We set currentState=SQUEEZING in API/Cycle.
      // But we need to record StartTime ONCE.
      // Fix: API sets to PRE_SQUEEZE or we handle "first run" flag?
      // Simpler: API sets SQUEEZING, and sets stateStartTime = millis().
      // But cycleStartTime needs setting too for the loop.
      
      // Let's refine:
      // API sets currentState = SQUEEZING; cycleStartTime = millis(); stateStartTime = millis();
      // But we need to send the servo command ONCE.
      // Use a flag or separate state?
      // Or just write it continuously? (PWN is continuous anyway)
      // Writing every loop is fine for ESP32Servo.
      
      {
         int angle = 270 - (270 * targetStrength / 100);
         setAllServos(angle);
      }
      
      // Move to HOLDING immediately?
      stateStartTime = now;
      currentState = HOLDING;
      break;
      
    case HOLDING:
      // Keep holding until time
      if (now - stateStartTime >= (holdTimeSec * 1000)) {
        setAllServos(REF_ANGLE);
        currentState = RELEASING;
        stateStartTime = now; 
      }
      break;
      
    case RELEASING:
      // Wait until Total Cycle Time (1.5s) is passed
      if (now - cycleStartTime >= 1500) {
        currentState = WAIT_CYCLE;
      }
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
