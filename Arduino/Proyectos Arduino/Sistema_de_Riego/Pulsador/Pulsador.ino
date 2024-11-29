// Variables pines

const byte pinPulsador = 8;
const byte pinRele = 9;


void setup() {
  // comfiguración comunicación serie

  Serial.begin(9600);

  // modo de los pines

  pinMode(pinPulsador, INPUT);
  pinMode(pinRele, OUTPUT);

}

void loop() {
  // leer el pulsador

  byte estadoPulsador = digitalRead(pinPulsador);

  // esperamos para evitar dobles pulsaciones

  delay(300);

  // comprobamos si se ha pulsdo el pulsador

  if (estadoPulsador == HIGH) {

    // cambiamos de estado el rele
    digitalWrite(pinRele, !digitalRead(pinRele));
    
    
    }

}
