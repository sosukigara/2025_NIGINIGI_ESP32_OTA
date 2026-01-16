#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <time.h>

// Selected UI: Main
#include "ui/ui_main.h"

const char* ssid     = "Extender-G-FA88";
const char* password = "jritucr4nff7u";

WebServer server(80);

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
  Serial.println("[API] Start command received");
  // TODO: Add Servo Control Code Here
  server.send(200, "text/plain", "OK");
}

void handleApiStop() {
  Serial.println("[API] Stop command received");
  // TODO: Add Servo Stop Code Here
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  
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

  server.begin();
  
  Serial.println("=================================");
  Serial.println("ONIGIRI MACHINE (Main) READY");
  Serial.print("Access URL: http://");
  Serial.println(WiFi.localIP());
  Serial.println("=================================");
}

void loop() {
  server.handleClient();
}
