#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <Preferences.h>
#include "html_content.h"

// Servo Config
const int servoPin = 25;
Servo myServo;

// Icons
#include "icon_data.h"

// Manifest
const char manifest_json[] PROGMEM = R"json({
    "name": "にぎにぎ",
    "short_name": "にぎにぎ",
    "theme_color": "#000000",
    "background_color": "#000000",
    "display": "standalone",
    "orientation": "portrait",
    "scope": "/",
    "start_url": "/",
    "icons": [
        {
            "src": "/icon.png",
            "sizes": "192x192",
            "type": "image/png"
        }
    ]
})json";

// Movement State Machine
enum MoveState { IDLE, SQUEEZING, RETURNING };
MoveState currentState = IDLE;

// State Variables
int currentAngle = 270; 
bool isMoving = false;
unsigned long moveStartTime = 0;
unsigned long moveDuration = 0;
int startMoveAngle = 270;
int targetMoveAngle = 270;
int minAngleLimit = 90; // Default Safe Limit (270=Open, 0=Closed)
unsigned long returnDuration = 100; // Default Return Speed (ms) - 0.1s is fastest recommended

// Stats
int totalCount = 0;
float totalDuration = 0.0;

Preferences prefs;
#include <map>
std::map<String, String> clientNames;

// Network Config
const char *ssid = "焼きそば太郎";
const char *password = NULL;
const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);

// Helper: Set Servo Angle (0-270)
void setServo(int angle) {
    if (angle < 0) angle = 0;
    if (angle > 270) angle = 270;
    // Map 0-270 degrees to 500-2500 microseconds (standard for 270 degree servos)
    int width = map(angle, 0, 270, 500, 2500);
    myServo.writeMicroseconds(width);
    currentAngle = angle;
}

// HTTP Handlers
void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

void handleSqueeze() {
    if (!server.hasArg("angle") || !server.hasArg("duration")) {
        server.send(400, "text/plain", "Missing args");
        return;
    }
    
    int target = server.arg("angle").toInt();
    // Apply Safety Limit
    if (target < minAngleLimit) {
        target = minAngleLimit;
    }

    float durSec = server.arg("duration").toFloat();
    
    // Begin Squeeze Phase
    startMoveAngle = currentAngle;
    targetMoveAngle = target;
    moveDuration = (unsigned long)(durSec * 1000);
    moveStartTime = millis();
    isMoving = true;
    currentState = SQUEEZING;
    
    Serial.printf("Squeeze Start: %d -> %d in %lu ms\n", startMoveAngle, targetMoveAngle, moveDuration);
    server.send(200, "text/plain", "Squeeze OK");
}

void handleReset() {
    isMoving = false;
    currentState = IDLE;
    setServo(270); // Home position
    server.send(200, "text/plain", "Reset OK");
}

void handleStop() {
    isMoving = false;
    currentState = IDLE;
    server.send(200, "text/plain", "Stopped");
}

void handleConfig() {
    String json = "{\"limit\": " + String(minAngleLimit) + ", \"speed\": " + String(returnDuration / 1000.0, 1) + "}";
    server.send(200, "application/json", json);
}

void handleSave() {
    bool saved = false;
    if (server.hasArg("limit")) {
        minAngleLimit = server.arg("limit").toInt();
        prefs.putInt("limit", minAngleLimit);
        saved = true;
    }
    if (server.hasArg("speed")) {
        float speedSec = server.arg("speed").toFloat();
        returnDuration = (unsigned long)(speedSec * 1000);
        prefs.putLong("speed", (long)returnDuration);
        saved = true;
    }
    
    if (saved) {
        server.send(200, "text/plain", "Saved");
    if (saved) {
        server.send(200, "text/plain", "Saved");
    } else {
        server.send(400, "text/plain", "No args");
    }
}

void handleGetStats() {
    String json = "{\"count\": " + String(totalCount) + ", \"duration\": " + String(totalDuration, 2) + "}";
    server.send(200, "application/json", json);
}

void handleSyncStats() {
    if (server.hasArg("plain")) {
        String body = server.arg("plain");
        // Simple manual parsing or assume format
        // Expected: {"count": 123, "duration": 45.6}
        // Basic parsing:
        int cStart = body.indexOf("\"count\":");
        int dStart = body.indexOf("\"duration\":");
        
        if (cStart != -1) {
            int valStart = cStart + 8;
            int valEnd = body.indexOf(",", valStart);
            if (valEnd == -1) valEnd = body.indexOf("}", valStart);
            int clientCount = body.substring(valStart, valEnd).toInt();
            
            if (clientCount > totalCount) {
                totalCount = clientCount;
                prefs.putInt("total_count", totalCount);
            }
        }
        
        if (dStart != -1) {
            int valStart = dStart + 11;
            int valEnd = body.indexOf(",", valStart);
            if (valEnd == -1) valEnd = body.indexOf("}", valStart);
            float clientDur = body.substring(valStart, valEnd).toFloat();
            
            if (clientDur > totalDuration) {
                totalDuration = clientDur;
                prefs.putFloat("total_duration", totalDuration);
            }
        }
        handleGetStats(); // Return updated/current stats
    } else {
        server.send(400, "text/plain", "Body required");
    }
}

void handleResetStats() {
    totalCount = 0;
    totalDuration = 0.0;
    prefs.putInt("total_count", 0);
    prefs.putFloat("total_duration", 0.0);
    server.send(200, "text/plain", "Stats Reset");
}

void handleDebug() {
    if (server.hasArg("angle")) {
        int ang = server.arg("angle").toInt();
        if (ang < minAngleLimit) ang = minAngleLimit;
        
        isMoving = false;
        currentState = IDLE;
        setServo(ang);
        server.send(200, "text/plain", "Debug OK");
    } else {
        server.send(400, "text/plain", "Missing angle");
    }
}

void handleManifest() {
    server.send(200, "application/manifest+json", manifest_json);
}

void handleIcon() {
    server.send_P(200, "image/png", (const char*)icon_png, icon_png_len);
}

void handleNotFound() {
    // Redirect for Captive Portal
    // If the host is not the device IP or domain, redirect to root
    String host = server.hostHeader();
    if (host != "192.168.4.1" && host != "onigiri.local") {
         server.sendHeader("Location", String("http://192.168.4.1/"), true);
         server.send(302, "text/plain", "Redirecting to Captive Portal");
         return;
    }
    server.send(404, "text/plain", "Not Found");
}

void setup() {
    Serial.begin(115200);

    // Load Persistent Settings
    prefs.begin("onigiri", false);
    minAngleLimit = prefs.getInt("limit", 90);
    returnDuration = (unsigned long)prefs.getLong("speed", 100);
    totalCount = prefs.getInt("total_count", 0);
    totalDuration = prefs.getFloat("total_duration", 0.0);

    // Initialize Servo
    myServo.setPeriodHertz(50);
    myServo.attach(servoPin, 500, 2500); 
    setServo(270); // Force initial position to 270 (Normal Open)

    // WiFi Access Point
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    
    // DNS (Captive Portal)
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

    // mDNS
    if (MDNS.begin("onigiri")) {
        Serial.println("MDNS: http://onigiri.local");
    }

    // Server Routes
    server.on("/", handleRoot);
    server.on("/squeeze", handleSqueeze);
    server.on("/reset", handleReset);
    server.on("/stop", handleStop);
    server.on("/config", handleConfig);
    server.on("/save", handleSave);
    server.on("/stats", HTTP_GET, handleGetStats);
    server.on("/sync_stats", HTTP_POST, handleSyncStats);
    server.on("/reset_stats", HTTP_POST, handleResetStats);
    server.on("/debug", handleDebug);
    server.on("/manifest.json", handleManifest);
    server.on("/icon.png", handleIcon);
    server.on("/generate_204", handleRoot); // Android Captive Portal
    server.on("/fwlink", handleRoot); // Microsoft Captive Portal
    server.on("/register_client", []() {
        if (server.hasArg("name")) {
            String ip = server.client().remoteIP().toString();
            clientNames[ip] = server.arg("name");
            server.send(200, "text/plain", "OK");
        } else {
            server.send(400, "text/plain", "Bad Name");
        }
    });

    server.on("/status", []() {
        String json = "{\"clients\": " + String(WiFi.softAPgetStationNum()) + ", \"name\": \"" + String(ssid) + "\", \"devices\": [";
        bool first = true;
        // Clean up or just list (softAPgetStationNum is only active ones, but map might have old ones)
        // For simplicity, we just list the registered ones. 
        // In a real app we might verify against WiFi.softAPgetStationNum()
        for (auto const& [ip, name] : clientNames) {
            if (!first) json += ",";
            json += "\"" + name + "\"";
            first = false;
        }
        json += "]}";
        server.send(200, "application/json", json);
    });
    server.onNotFound(handleNotFound);
    server.begin();

    // OTA Setup
    ArduinoOTA.begin();

    Serial.println("System Ready. Defaulting servo to 270 deg.");
}

void loop() {
    dnsServer.processNextRequest();
    server.handleClient();
    ArduinoOTA.handle();

    // Non-blocking Movement State Machine
    if (isMoving) {
        unsigned long elapsed = millis() - moveStartTime;
        
        if (elapsed >= moveDuration) {
            // Reached target of current phase
            setServo(targetMoveAngle);
            
            if (currentState == SQUEEZING) {
                // Squeeze phase done, start Return phase
                currentState = RETURNING;
                startMoveAngle = targetMoveAngle;
                targetMoveAngle = 270; // Always return to Open position
                moveDuration = returnDuration; // User defined return speed
                moveStartTime = millis();
                Serial.printf("Returning to 270 in %lu ms...\n", returnDuration);
            } else {
                // Done with all movements
                isMoving = false;
                currentState = IDLE;
                Serial.println("Locked at 270.");
            }
        } else {
            // Interpolating move
            float progress = (float)elapsed / moveDuration;
            int nextAngle = startMoveAngle + (int)((targetMoveAngle - startMoveAngle) * progress);
            setServo(nextAngle);
        }
    }
}
