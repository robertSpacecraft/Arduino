#include <Servo.h>

Servo miServo;

const byte anguloMax = 160;
const byte anguloMin = 0;
const byte pinServo = 9;
const byte pinPoten = A0;

void setup() {
  Serial.begin(9600);

  miServo.attach(pinServo);

}

void loop() {
  int valor = analogRead(pinPoten);
  int valorAdapt = map(valor,0,1024,anguloMin,anguloMax);
  miServo.write(valor);
  delay(20); 

}
