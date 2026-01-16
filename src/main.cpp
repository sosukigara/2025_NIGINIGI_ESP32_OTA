#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <time.h>
#include <ESP32Servo.h>
#include <Preferences.h>

// UIファイル (前回作成したものをそのまま使用)
#include "ui/ui_main.h"

// --- 設定値 ---
const char* ssid     = "Extender-G-FA88";
const char* password = "jritucr4nff7u";

WebServer server(80);
Preferences preferences;

Servo servo1, servo2, servo3;
const int PIN_SERVO1 = 25;
const int PIN_SERVO2 = 26;
const int PIN_SERVO3 = 27;

// --- サーボ設定 (ここを調整) ---
// 一般的な270度サーボのパルス幅 (500us〜2500us)
// ※もし動きが逆（閉じるつもりで開く）なら、この数値を入れ替えてください
const int US_AT_0_DEG   = 500;   // 0度 (閉/強) のときのパルス幅
const int US_AT_270_DEG = 2500;  // 270度 (開/弱) のときのパルス幅

// 状態管理
enum State { IDLE, PREPARE_SQUEEZE, SQUEEZING, HOLDING, RELEASING, WAIT_CYCLE };
State currentState = IDLE;
State lastState = IDLE; 

unsigned long stateStartTime = 0;
unsigned long sessionStartTime = 0;

// パラメータ
float holdTimeSec = 0.5;
float reachTimeSec = 0.5;
int targetStrength = 50; // 0-100%
int targetCount = 3;
int currentCycle = 0;
int pin13State = 0;

// ヘルパー: 全サーボにパルス幅(us)を指定
void setAllServosUs(int us) {
    servo1.writeMicroseconds(us);
    servo2.writeMicroseconds(us);
    servo3.writeMicroseconds(us);
}

// ヘルパー: 角度(0-270)をパルス幅に変換して移動
void setAllServosAngle(int angle) {
    // 安全リミット
    if (angle < 0) angle = 0;
    if (angle > 270) angle = 270;
    
    // 0度=500us, 270度=2500us にマッピング
    int us = map(angle, 0, 270, US_AT_0_DEG, US_AT_270_DEG);
    setAllServosUs(us);
}

// ヘルパー: 強さ(0-100%)をパルス幅に変換
// 0%(弱) = 270度, 100%(強) = 0度
int strengthToUs(int strength) {
    if (strength < 0) strength = 0;
    if (strength > 100) strength = 100;
    
    // 強度0 -> 270度(US_AT_270_DEG)
    // 強度100 -> 0度(US_AT_0_DEG)
    return map(strength, 0, 100, US_AT_270_DEG, US_AT_0_DEG);
}

// API: Start
void handleApiStart() {
    if (server.hasArg("str")) targetStrength = server.arg("str").toInt();
    if (server.hasArg("cnt")) targetCount = server.arg("cnt").toInt();
    
    if (targetStrength > 100) targetStrength = 100;
    if (targetStrength < 0) targetStrength = 0;

    Serial.printf("[API] Start: Str=%d%%, Cnt=%d\n", targetStrength, targetCount);
    
    currentCycle = 0;
    sessionStartTime = millis();
    currentState = PREPARE_SQUEEZE; 
    
    server.send(200, "text/plain", "OK");
}

void handleApiStop() {
    Serial.println("[API] Stop");
    currentState = IDLE;
    // 停止時はデフォルト位置（270度）へ戻る
    setAllServosAngle(270);
    server.send(200, "text/plain", "OK");
}

void handleApiSettings() {
    if (server.hasArg("hold")) {
        holdTimeSec = server.arg("hold").toFloat();
        preferences.putFloat("hold", holdTimeSec);
    }
    if (server.hasArg("reach")) {
        reachTimeSec = server.arg("reach").toFloat();
        preferences.putFloat("reach", reachTimeSec);
    }
    if (server.hasArg("load")) {
        // 設定読み込み用（処理なし、下のJSONを返すだけ）
    }
    
    String json = "{";
    json += "\"hold\":" + String(holdTimeSec) + ",";
    json += "\"reach\":" + String(reachTimeSec) + ",";
    json += "\"pin13\":" + String(pin13State);
    json += "}";
    server.send(200, "application/json", json);
}

void handleApiPin13() {
    if (server.hasArg("val")) {
        pin13State = server.arg("val").toInt();
        digitalWrite(13, pin13State ? HIGH : LOW);
        preferences.putInt("pin13", pin13State);
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

    float cycleDur = reachTimeSec + holdTimeSec + 0.3; 
    float totalDur = targetCount * cycleDur;
    
    String json = "{";
    json += "\"state\":\"" + s + "\",";
    json += "\"cycle\":" + String(currentCycle) + ",";
    json += "\"total\":" + String(targetCount) + ",";
    json += "\"elap\":" + String(millis() - sessionStartTime) + ",";
    json += "\"pin13\":" + String(pin13State) + ",";
    json += "\"dur\":" + String(totalDur);
    json += "}";
    server.send(200, "application/json", json);
}

void handleApiManual() {
    if (server.hasArg("val")) {
        int anglePercent = server.arg("val").toInt();
        // UI says 0-100%, but this endpoint used to handle deg.
        // Let's assume it wants 0-270 degrees based on the user's manual comment.
        // UI current script converts pct to deg: 270 - (pct * 2.7)
        int angle = anglePercent; 
        currentState = IDLE; 
        setAllServosAngle(angle);
        Serial.printf("[API] Manual: %d deg\n", angle);
    }
    server.send(200, "text/plain", "OK");
}

void handleRoot() {
    String html = html_main;
    html.replace("{{BUILD_TIME}}", __DATE__ " " __TIME__);
    server.send(200, "text/html", html);
}

void setup() {
    Serial.begin(115200);
    
    preferences.begin("job", false);
    holdTimeSec = preferences.getFloat("hold", 0.5);
    reachTimeSec = preferences.getFloat("reach", 0.5);
    pin13State = preferences.getInt("pin13", 0);
    
    pinMode(13, OUTPUT);
    digitalWrite(13, pin13State ? HIGH : LOW);
    
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    
    servo1.setPeriodHertz(50);
    servo2.setPeriodHertz(50);
    servo3.setPeriodHertz(50);
    
    // パルス幅設定してAttach
    servo1.attach(PIN_SERVO1, US_AT_0_DEG, US_AT_270_DEG);
    servo2.attach(PIN_SERVO2, US_AT_0_DEG, US_AT_270_DEG);
    servo3.attach(PIN_SERVO3, US_AT_0_DEG, US_AT_270_DEG);
    
    // ★起動時の初期位置: 270度 (開)
    setAllServosAngle(270);
    
    WiFi.begin(ssid, password);
    Serial.print("Connecting WiFi");
    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry < 20) {
        delay(500);
        Serial.print(".");
        retry++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected.");
        Serial.print("IP: "); Serial.println(WiFi.localIP());
        configTime(9 * 3600, 0, "pool.ntp.org");
    } else {
        Serial.println("\nWiFi Connect Failed. Running offline.");
    }

    server.on("/", handleRoot);
    server.on("/api/status", handleApiStatus);
    server.on("/api/start", handleApiStart);
    server.on("/api/stop", handleApiStop);
    server.on("/api/settings", handleApiSettings);
    server.on("/api/pin13", handleApiPin13);
    server.on("/api/manual", handleApiManual);
    server.onNotFound([](){ server.send(404, "text/plain", "Not Found"); });

    server.begin();
    Serial.println("Ready.");
}

void loop() {
    server.handleClient();
    
    unsigned long now = millis();
    
    if (currentState != lastState) {
        stateStartTime = now;
        lastState = currentState;
        Serial.printf("State: %d\n", currentState);
    }

    switch (currentState) {
        case IDLE:
            break;

        case PREPARE_SQUEEZE:
            // 握る動作の前に「全開(270度)」にする
            setAllServosAngle(270);
            if (now - stateStartTime > 300) { // 物理的な移動待ち
                currentState = SQUEEZING;
            }
            break;
            
        case SQUEEZING:
            {
                unsigned long duration = reachTimeSec * 1000;
                unsigned long elapsed = now - stateStartTime;
                
                // 開始: 0%(270度), 終了: targetStrength%(0度に近い)
                int startUs = US_AT_270_DEG;
                int targetUs = strengthToUs(targetStrength);

                if (elapsed >= duration) {
                    setAllServosUs(targetUs);
                    currentState = HOLDING;
                } else {
                    float progress = (float)elapsed / (float)duration;
                    // イージング（滑らかに）
                    // progress = progress * progress * (3 - 2 * progress); 
                    
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
            // 素早く全開(270度)に戻す
            setAllServosAngle(270);
            
            if (now - stateStartTime >= 300) {
                currentState = WAIT_CYCLE;
            }
            break;
            
        case WAIT_CYCLE:
            currentCycle++;
            if (currentCycle < targetCount) {
                currentState = SQUEEZING; 
            } else {
                Serial.println("Finished.");
                setAllServosAngle(270); // Final return to open
                currentState = IDLE;
            }
            break;
    }
}
