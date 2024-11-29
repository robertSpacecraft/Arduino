#include <Arduino.h>

#define LED_BUILTIN 2

int trigger = 2;
int echo = 0;

//Funciones
  int calculateDistance(){
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long time = pulseIn(echo, HIGH);
  double distance = time / 58;
  return distance;
}

/*void triggerAction(){
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
}*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, LOW);
}

void loop() {
  Serial.println(calculateDistance());
  digitalWrite(LED_BUILTIN, LOW);
 // Serial.print(trigger, echo);
}