#include <Arduino.h>

#define LED_BUILTIN 2

int trigger = D4;
int echo = D3;

//Funciones
  int calculateDistance(){
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long time = pulseIn(echo, HIGH);
  int distance = time / 58;
  return distance;
}

/*void triggerAction(){
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
}*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, LOW);
}

void loop() {
  Serial.println(calculateDistance());
  digitalWrite(LED_BUILTIN, LOW);
 // Serial.print(trigger, echo);
}