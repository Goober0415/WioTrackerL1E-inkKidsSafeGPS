#include <Wire.h>
#include <SPI.h>

const int BATTERY_PIN = A0;

void setup() {
  Serial.begin(115200);
  pinMode(BATTERY_PIN, INPUT);
}

void loop() {
  int batteryReading = analogRead(BATTERY_PIN);
  float batteryVoltage = batteryReading * 3.3 / 1024.0;
  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage);
  
  delay(1000);
}
