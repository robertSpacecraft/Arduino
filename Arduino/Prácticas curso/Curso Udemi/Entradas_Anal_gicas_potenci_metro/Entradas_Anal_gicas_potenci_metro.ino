

void setup() {
  Serial.begin(9600);

}

void loop() {

  int valorLeido = analogRead(A0); // leemos el valor de A0 y lo asignamos a una variable.
  int valorAdaptado = map(valorLeido,0,1023,0,255);
  analogWrite(3, valorAdaptado); //generando una señal PWM

  
  Serial.println("El valor leido es: " + String(valorLeido) + " El valor adaptado es: " + String(valorAdaptado));
}
