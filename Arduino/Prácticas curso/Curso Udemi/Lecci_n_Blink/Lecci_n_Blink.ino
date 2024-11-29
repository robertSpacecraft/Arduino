int pinLed = 5;
int pinPlaca =13;
int tEncendido = 100;
int tApagado = 100;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinPlaca, OUTPUT);
}

void loop() {

  digitalWrite(pinLed, HIGH);
  delay(tEncendido);
  digitalWrite(pinLed, LOW);
  delay(tApagado);

  digitalWrite(pinPlaca, HIGH);
  delay(tEncendido);
  digitalWrite(pinPlaca, LOW);
  delay(tApagado);
}
