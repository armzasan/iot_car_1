#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// เปลี่ยนเป็น SSID และรหัสผ่านของ Wi-Fi ของคุณ
const char* ssid = "carbot";
const char* password = "11111111";

// กำหนดขา GPIO ที่เชื่อมต่อกับ L293D
const int motorA1 = 5; // D1
const int motorA2 = 4; // D2
const int motorB1 = 0; // D3
const int motorB2 = 2; // D4

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  // ตั้งค่าขา GPIO เป็น OUTPUT
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  // ตั้งค่า Wi-Fi
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

  // กำหนด route สำหรับเว็บเซิร์ฟเวอร์
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "Hello from ESP8266!");
  });
  server.on("/forward", HTTP_GET, []() {
    moveForward();
    server.send(200, "text/plain", "Moving Forward");
  });
  server.on("/stop", HTTP_GET, []() {
    stopMoving();
    server.send(200, "text/plain", "Stopped");
  });
  // เพิ่ม route อื่นๆ ที่นี่ตามต้องการ

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void moveForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void stopMoving() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
