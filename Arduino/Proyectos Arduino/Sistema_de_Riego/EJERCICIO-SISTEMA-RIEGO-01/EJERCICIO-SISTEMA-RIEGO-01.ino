// Variables pines
const byte pinPulsador = 8;
const byte pinRele = 9;

void setup() {
  // Configuración comunicación serie
  Serial.begin(9600);

  // Modo de los pines
  pinMode(pinPulsador, INPUT);
  pinMode(pinRele, OUTPUT);
}

void loop() {
  // Leer el pulsador
  byte estadoPulsador = digitalRead(pinPulsador);

  // Esperamos para evitar dobles pulsaciones
  delay(300);

  // Comprobamos si se ha pulsado el pulsador
  if (estadoPulsador == HIGH) {

    // Cambiamos de estado el relé
    digitalWrite(pinRele, !digitalRead(pinRele));
  }
}
