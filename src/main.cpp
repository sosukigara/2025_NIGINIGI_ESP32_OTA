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
// サーボ設定 (us制御)
const int US_MIN = 500;  // 270度 (Weak/Rest)
const int US_MAX = 2500; // 0度 (Strong/Squeeze)

// State Machine
// 状態管理
enum State { IDLE, PREPARE_SQUEEZE, SQUEEZING, HOLDING, RELEASING, WAIT_CYCLE };
State currentState = IDLE;
State lastState = IDLE;
int pin13State = 0;
long stateStartTime = 0;
unsigned long sessionStartTime = 0; // ms when /api/start was called
float holdTimeSec = 0.5; // Default 0.5s
float reachTimeSec = 0.5; // Default 0.5s

int targetStrength = 0; // Global variable for target strength
int targetCount = 0;    // Global variable for target count
int currentCycle = 0;   // Global variable for current cycle

// ヘルパー: パーセントからパルス幅(us)を計算
int strengthToUs(int strength) {
    return map(strength, 0, 100, US_MIN, US_MAX);
}

// ヘルパー: 全サーボ制御 (us指定)
void setAllServosUs(int us) {
    servo1.writeMicroseconds(us);
    servo2.writeMicroseconds(us);
    servo3.writeMicroseconds(us);
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
  
    currentCycle = 0;
    sessionStartTime = millis();
    currentState = PREPARE_SQUEEZE; 
    
    server.send(200, "text/plain", "OK");
}

void handleApiStop() {
    Serial.println("[API] Stop");
    currentState = IDLE;
    setAllServosUs(US_MIN);
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
  json += "\"pin13\":0"; // Temporarily hardcoded for this version
  json += "}";
  server.send(200, "application/json", json);
}

void handleApiPin13() {
  if (server.hasArg("val")) {
    pin13State = server.arg("val").toInt();
    digitalWrite(13, pin13State ? HIGH : LOW);
    preferences.putInt("pin13", pin13State);
    Serial.printf("[API] Pin 13: %d\n", pin13State);
  }
  server.send(200, "text/plain", "OK");
}

void handleApiStatus() {
  String s;
  switch (currentState) {
    case IDLE: s = "IDLE"; break;
    case PREPARE_SQUEEZE: s = "PREPARE_SQUEEZE"; break;
    case SQUEEZING: s = "SQUEEZING"; break;
    case HOLDING: s = "HOLDING"; break;
    case RELEASING: s = "RELEASING"; break;
    case WAIT_CYCLE: s = "WAIT_CYCLE"; break;
  }

  float cycleDur = reachTimeSec + holdTimeSec + 0.3; // estimated cycle time
  float totalDur = targetCount * cycleDur;
  
  String json = "{";
  json += "\"state\":\"" + s + "\",";
  json += "\"cycle\":" + String(currentCycle) + ",";
  json += "\"total\":" + String(targetCount) + ",";
  json += "\"hold\":" + String(holdTimeSec) + ",";
  json += "\"reach\":" + String(reachTimeSec) + ",";
  json += "\"str\":" + String(targetStrength) + ",";
  json += "\"elap\":" + String(millis() - sessionStartTime) + ",";
  json += "\"pin13\":" + String(pin13State) + ",";
  json += "\"dur\":" + String(totalDur);
  json += "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  
  // Preferences
  // Preferences
  preferences.begin("job", false);
  holdTimeSec = preferences.getFloat("hold", 0.5);
  reachTimeSec = preferences.getFloat("reach", 0.5);
  pin13State = preferences.getInt("pin13", 0);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, pin13State ? HIGH : LOW);
  
  // Servo Setup
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);
  servo3.setPeriodHertz(50);
    servo1.attach(PIN_SERVO1, US_MIN, US_MAX);
    servo2.attach(PIN_SERVO2, US_MIN, US_MAX);
    servo3.attach(PIN_SERVO3, US_MIN, US_MAX);
    
    setAllServosUs(US_MIN);
  
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
  server.on("/api/status", handleApiStatus);
  server.on("/api/start", handleApiStart);
  server.on("/api/stop", handleApiStop);
  server.on("/api/settings", handleApiSettings);
  server.on("/api/pin13", handleApiPin13);
  server.onNotFound([](){ server.send(404, "text/plain", "Not Found"); });

  server.begin();
  
  Serial.println("=================================");
  Serial.println("ONIGIRI MACHINE (Main) READY");
  Serial.printf("Settings: Hold=%.2fs, Reach=%.2fs\n", holdTimeSec, reachTimeSec);
  Serial.print("Access URL: http://");
  Serial.println(WiFi.localIP());
  Serial.println("=================================");
}


// Improved Loop Logic
void loop() {
  server.handleClient();
  unsigned long now = millis();

  if (currentState != lastState) {
    stateStartTime = now;
    lastState = currentState;
    Serial.printf("State Changed to: %d\n", currentState);
  }

  switch (currentState) {
    case IDLE:
      break;

    case PREPARE_SQUEEZE:
      setAllServosUs(US_MIN);
      if (now - stateStartTime > 200) { // Wait 200ms in PREPARE_SQUEEZE
        currentState = SQUEEZING;
      }
      break;
      
    case SQUEEZING:
      {
        unsigned long duration = reachTimeSec * 1000;
        if (duration == 0) duration = 1; // Avoid division by zero
        unsigned long elapsed = now - stateStartTime;
        int targetUs = strengthToUs(targetStrength);
        int startUs = US_MIN;

        if (elapsed >= duration) {
          setAllServosUs(targetUs);
          currentState = HOLDING;
        } else {
          float progress = (float)elapsed / (float)duration;
          int currentUs = startUs + (targetUs - startUs) * progress;
          setAllServosUs(currentUs);
        }
      }
      break;
      
    case HOLDING:
      if (now - stateStartTime >= (holdTimeSec * 1000)) {
        currentState = RELEASING;
      }
      break;
      
    case RELEASING:
      setAllServosUs(US_MIN); // Immediately return to rest position
      if (now - stateStartTime >= 300) { // Wait 300ms for release to complete
        currentState = WAIT_CYCLE;
      }
      break;
      
    case WAIT_CYCLE:
      currentCycle++;
      if (currentCycle < targetCount) {
        currentState = SQUEEZING; // Start next cycle
      } else {
        Serial.println("Session Finished.");
        currentState = IDLE; // All cycles complete
      }
      break;
  }
}
