//Asignación de pines del los motores
const byte motorIzA = 3;
const byte motorIzB = 4;
const byte motorDeA = 5;
const byte motorDeB = 6;

const byte enabIz = 10;
const byte enabDe = 11;

//Asignación de pines del sensor ultrasónico.
const byte trigger = 9;
const byte echo = 8;

//Variables de velocidad de los motores
byte velocidadInicial = 0;
byte velocidadMinima = 122;
byte velocidadMedia = 180;
byte velocidadGiro = 135;

//Función control rueda Izquierda
void controlIz(bool sentidoIz, byte velIz){
  if (sentidoIz == true){
    digitalWrite(motorIzA, HIGH);
    digitalWrite(motorIzB, LOW);
  }else {
    digitalWrite(motorIzA, LOW);
    digitalWrite(motorIzB, HIGH);
      }
   analogWrite(enabIz,velIz);
  }

//Función control rueda Derecha
void controlDe(bool sentidoDe, byte velDe){
  if (sentidoDe == true){
    digitalWrite(motorDeA, HIGH);
    digitalWrite(motorDeB, LOW);
  }else {
    digitalWrite(motorDeA, LOW);
    digitalWrite(motorDeB, HIGH);
      }
   analogWrite(enabDe,velDe);
  }

void atras(bool recto, byte velRecto){
  if (recto == true){
    controlDe(true, velocidadMedia);
    controlIz(true, velocidadMedia);
    }
  }

void adelante(bool recto, byte velRecto){
  if (recto == true){
    controlDe(false, velocidadMedia);
    controlIz(false, velocidadMedia);
    }
  }

void giraDerecha(bool giraDe, byte velGiro){
  if (giraDe == true){
    controlDe(true, velocidadGiro);
    controlIz(false, velocidadGiro);
    }
   }

void giraIzquierda(bool giraIz, byte velGiro){
  if (giraIz == true){
    controlDe(false, velocidadGiro);
    controlIz(true, velocidadGiro);
    }
   }

void setup() {
  Serial.begin(9600);

  pinMode(motorIzA, OUTPUT);
  pinMode(motorIzB, OUTPUT);
  pinMode(motorDeA, OUTPUT);
  pinMode(motorDeB, OUTPUT);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  analogWrite(enabIz,velocidadInicial);
  analogWrite(enabDe,velocidadInicial);

}

void loop() {

  adelante(true, velocidadInicial);
  delay(1000);
  giraDerecha(true, velocidadGiro);
  delay(1000);
 
  Serial.println(velocidadInicial);


}
