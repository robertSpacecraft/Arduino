// Incluimos librerías
#include <Wire.h>
#include "RTClib.h"

// Instancia a la clase RTC_DS3231
RTC_DS3231 rtc;

void setup() {
  // Iniciamos comunicación serie
  Serial.begin(9600);
  
  // Iniciamos el rtc
  if (!rtc.begin()) {
    Serial.println("No se ha encontrado el módulo RTC");
    while (1);
  }

  // Ajuste de fecha y hora
  rtc.adjust(DateTime(__DATE__,__TIME__));

}

void loop() {
    // Obtenemos la fecha
  DateTime tiempoReferencia = rtc.now();

  Serial.print(tiempoReferencia.year(), DEC);
  Serial.print('/');
  Serial.print(tiempoReferencia.month(), DEC);
  Serial.print('/');
  Serial.print(tiempoReferencia.day(), DEC);
  Serial.print(" ");
  Serial.print(tiempoReferencia.hour(), DEC);
  Serial.print(':');
  Serial.print(tiempoReferencia.minute(), DEC);
  Serial.print(':');
  Serial.print(tiempoReferencia.second(), DEC);
  Serial.println();
  delay(1000);
}
