const int sensorPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int value = 0;
  value = digitalRead(sensorPin);
  if (value == HIGH){
    Serial.println("Detectado Obstaculo: ");
    Serial.print(value);
  } else if (value == LOW){
    Serial.println("No se detectan obstáculos ");
    Serial.print(value);
  }
  delay(1000);
}
