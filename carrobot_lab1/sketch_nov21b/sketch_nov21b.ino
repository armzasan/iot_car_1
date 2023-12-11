#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//#include "BlynkSimpleStream.h"
//#define BLYNK_PRINT Serial
//#define BLYNK_TEMPLATE_ID "TMPL6ydO45Hnf"
//#define BLYNK_TEMPLATE_NAME "Quickstart Template"
//#define BLYNK_AUTH_TOKEN "vhPtu8aAZDl4UqhV8Z_VB-OnuzUJ2i2i"
////#define EspSerial Serial1
// WiFi credentials
const char* ssid = "armwifi";
const char* password = "armarm123";

ESP8266WebServer server(80);

// GPIO pins for motors
const int motor1Pin1 = D1;
const int motor1Pin2 = D3;
const int motor2Pin1 = D2;
const int motor2Pin2 = D4;

void setup() {
  Serial.begin(115200);
//   Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup motor pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Setup server routes
  server.on("/", handleRoot);
    server.on("/forward/start", []() {
    analogWrite(motor1Pin1, 1023);
    analogWrite(motor2Pin1, 1023);
    server.send(200, "text/plain", "Forward start");
  });
  server.on("/forward/stop", []() {
    analogWrite(motor1Pin1, 0);
    analogWrite(motor2Pin1, 0);
    server.send(200, "text/plain", "Forward stop");
  });
  server.on("/left/start", []() {
    analogWrite(motor1Pin1, 1023); // มอเตอร์ 1 เลี้ยวซ้าย
    analogWrite(motor2Pin1, 0); // มอเตอร์ 2 หยุด
    server.send(200, "text/plain", "Turning left");
  });
   server.on("/left/stop", []() {
    analogWrite(motor1Pin1, 0); // มอเตอร์ 1 เลี้ยวซ้าย
    analogWrite(motor2Pin1, 0); // มอเตอร์ 2 หยุด
    server.send(200, "text/plain", "Turning left");
  });
  server.on("/right/start", []() {
    analogWrite(motor1Pin1, 0); // มอเตอร์ 1 หยุด
    analogWrite(motor2Pin1, 1023); // มอเตอร์ 2 เลี้ยวขวา
    server.send(200, "text/plain", "Turning right");
  });
    server.on("/right/stop", []() {
    analogWrite(motor1Pin1, 0); // มอเตอร์ 1 หยุด
    analogWrite(motor2Pin1, 0); // มอเตอร์ 2 เลี้ยวขวา
    server.send(200, "text/plain", "Turning right");
  });
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String message = "<html><head><style>";
  message += "body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; }";
  message += "button { background-color: #4CAF50; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; border: none; border-radius: 4px;}";
  message += "button:hover { background-color: #45a049; }";
  message += "@media screen and (max-width: 600px) {";
  message += "  button { padding: 15px; font-size: 14px; }";
  message += "}";
  message += "</style>";

  message += "<script>";
  message += "function sendRequest(url) {";
  message += "  var xhr = new XMLHttpRequest();";
  message += "  xhr.open('GET', url, true);";
  message += "  xhr.send();";
  message += "}";
  message += "</script>";

  message += "</head><body>";
  message += "<h2>crawler truck control</h2>";

  // Buttons with mouse and touch events
  message += "<button onmousedown=\"sendRequest('/forward/start')\" onmouseup=\"sendRequest('/forward/stop')\" ontouchstart=\"sendRequest('/forward/start')\" ontouchend=\"sendRequest('/forward/stop')\">Forward</button><br>";
  message += "<button onmousedown=\"sendRequest('/backward/start')\" onmouseup=\"sendRequest('/backward/stop')\" ontouchstart=\"sendRequest('/backward/start')\" ontouchend=\"sendRequest('/backward/stop')\">Backward</button><br>";
  message += "<button onmousedown=\"sendRequest('/left/start')\" onmouseup=\"sendRequest('/left/stop')\" ontouchstart=\"sendRequest('/left/start')\" ontouchend=\"sendRequest('/left/stop')\">Left</button><br>";
  message += "<button onmousedown=\"sendRequest('/right/start')\" onmouseup=\"sendRequest('/right/stop')\" ontouchstart=\"sendRequest('/right/start')\" ontouchend=\"sendRequest('/right/stop')\">Right</button><br>";

  message += "</body></html>";
  server.send(200, "text/html", message);
}
