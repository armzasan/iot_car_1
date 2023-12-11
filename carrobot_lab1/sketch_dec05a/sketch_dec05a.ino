#include <DHT.h>

// กำหนด PIN สำหรับ Relay และปุ่มกด
const int relayPins[] = {5, 18, 19, 21}; // แก้ไขตาม PIN ของคุณ
const int buttonPins[] = {13, 14, 27, 26}; // แก้ไขตาม PIN ของคุณ
const int DHTPin = 4; // แก้ไขตาม PIN ของคุณ

// กำหนดประเภทของเซ็นเซอร์ DHT
#define DHTTYPE DHT22
DHT dht(DHTPin, DHTTYPE);

void setup() {
  // กำหนด pinMode สำหรับ relay และปุ่มกด
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
    digitalWrite(relayPins[i], HIGH); // ปิด Relay ทั้งหมด
  }

  // กำหนดเริ่มต้นสำหรับ DHT22
  dht.begin();

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      handleButtonPress(i);
      delay(500); // debounce delay
    }
  }
}

void handleButtonPress(int buttonIndex) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(relayPins[i], i == buttonIndex ? LOW : HIGH);
  }

  if (buttonIndex == 0) {
    // อ่านข้อมูลอุณหภูมิเมื่อกดปุ่มที่ 1
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%  Temperature: ");
    Serial.print(t);
    Serial.println("°C");
  }
}
