#include <DHT.h>

const int relayPins[] = {5, 18, 19, 21}; 
const int buttonPins[] = {13, 14, 27, 26}; 
const int DHTPin = 4; 


#define DHTTYPE DHT22
DHT dht(DHTPin, DHTTYPE);

void setup() {

  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
    digitalWrite(relayPins[i], HIGH);
  }

  
  dht.begin();

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      handleButtonPress(i);
      delay(500); 
    }
  }
}

void handleButtonPress(int buttonIndex) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(relayPins[i], i == buttonIndex ? LOW : HIGH);
  }

 
  Serial.print("Button ");
  Serial.print(buttonIndex + 1);
  Serial.println(" pressed. Relay Status:");
  for (int i = 0; i < 4; i++) {
    Serial.print("Relay ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(digitalRead(relayPins[i]) == LOW ? "ON" : "OFF");
  }

  if (buttonIndex == 0) {
   
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
