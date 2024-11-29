const int sensorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int humedad = analogRead(sensorPin);
  Serial.println(humedad);

  if (humedad < 500)
  {
    Serial.println("Encendido");
  }
  delay(1000);
}
