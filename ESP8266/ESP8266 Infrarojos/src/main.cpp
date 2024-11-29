#include <Arduino.h>

const int sensorPin = 5;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
      int value = 0;
  value = digitalRead(sensorPin);
  if (value == HIGH){
    Serial.println("No se detectan obstáculos: ");
    Serial.print(value);
  } else if (value == LOW){
    Serial.println("Obstáculo detectado! ");
    Serial.print(value);
  }
  delay(250);

}