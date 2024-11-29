// incluimos las librerias:
#include <OneWire.h>
#include <DallasTemperature.h>

//definimos el puerto con el protocolo de comunicación de OneWire
#define ONE_WIRE_BUS 2

//declaramos la instancia
OneWire oneWire (ONE_WIRE_BUS);

//Usamos la libreria dallas
DallasTemperature sensor(&oneWire);

 int led = 5;


void setup() {
  Serial.begin(9600);  

}

void loop() {

  sensor.requestTemperatures();
  Serial.println("La temperatura es: " + String(sensor.getTempCByIndex(0)));  

}
