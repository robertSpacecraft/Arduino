// Pin donde se conectan los leds
int pinLed1 = 2;
int pinLed2 = 3;
// Pin analogico de entrada para el LDR
int pinLDR = 0;
 
// Variable donde se almacena el valor del LDR
int valorLDR = 0;  
 
void setup()
{
  // Configuramos como salidas los pines donde se conectan los led
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  
  //  Configurar el puerto serial
  Serial.begin(9600);
}
 
void loop()
{
  // Apagar todos los leds siempre que se inicia el ciclo
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
 
  // Guardamos el valor leido del ADC en una variable
  // El valor leido por el ADC (voltaje) aumenta de manera directamente proporcional
  // con respecto a la luz percibida por el LDR
  valorLDR= analogRead(pinLDR);
  
  // Devolver el valor leido a nuestro monitor serial en el IDE de Arduino
  Serial.println(valorLDR);
 
  // Encender los leds apropiados de acuerdo al valor de ADC

  if(valorLDR > 200)
  {
    digitalWrite(pinLed1, HIGH);
  }
  if(valorLDR > 500)
  {
    digitalWrite(pinLed2, HIGH);
  }
  // Esperar unos milisegundos antes de actualizar
  delay(200);
}
