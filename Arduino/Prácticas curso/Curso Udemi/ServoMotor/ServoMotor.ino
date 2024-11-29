#include <Servo.h>

//Variables

Servo miServo;
const byte anguloMax = 160;
const byte anguloMin = 0;

void setup() {
  Serial.begin(9600);

  //pin del servo
  miServo.attach(9);

}

void loop() {
  //Ejemplo girará 90 grados
  miServo.write(90);
  delay(20); //genero el pulso de 50Hr necesario.

  //ejemplo de giro completo de 0 a 160
  for(int i=0; i<anguloMax; i++){
    miServo.write(i);
    delay(20);
    }

   //Ejemplo giro completo de 160 a 0
   for(int i=0; i>anguloMin; i--){
    miServo.write(i);
    delay(20);
    }

    //para aumentar la velocidad a la que se mueve debemos hacer que i aumente más deprisa:
    //Ejemplo for anterior con una velocidad + 5
    for(int i=0; i>anguloMin; i-5){
    miServo.write(i);
    delay(20);
    }

}
