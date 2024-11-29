// Incluimos librerías
#include <Wire.h>
#include "RTClib.h"

// Variables pines
const byte pinPulsador = 8;
const byte pinRele = 9;

// Instancia a la clase RTC_DS3231
RTC_DS3231 rtc;

// Parámetros de riego
const byte diasRiego = 3;
const byte horaRiego = 21;
byte contadorDias = 0;
boolean centinelaHora = true;

// Tiempo de riego
const long duracionRiego = 6000; // Cuánto tiempo riega en milisegundos
unsigned long marcaTiempo; // Marca de tiempo para contar los milisegundos

void setup() {
  // Configuración comunicación serie
  Serial.begin(9600);

  // Modo de los pines
  pinMode(pinPulsador, INPUT);
  pinMode(pinRele, OUTPUT);

  // Iniciamos el rtc
  if (!rtc.begin()) {
    Serial.println("No se ha encontrado el módulo RTC");
    while (1);
  }
}

void loop() {
  // Leer el pulsador
  byte estadoPulsador = digitalRead(pinPulsador);

  // Esperamos para evitar dobles pulsaciones
  delay(400);

  // Comprobamos si se ha pulsado el pulsador
  if (estadoPulsador == HIGH) {

    // Cambiamos de estado el relé
    digitalWrite(pinRele, !digitalRead(pinRele));

    // Comenzamos a contar el tiempo
    marcaTiempo = millis();
  }

  // Obtenemos la fecha
  DateTime tiempoReferencia = rtc.now();

  // Mostramos la fecha por el monitor serie
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

  // Si es la hora de regar
  if (tiempoReferencia.hour() == horaRiego && centinelaHora) {
    // Marcamos para que no vuelva a entrar
    centinelaHora = false;

    // Sumamos una al contador de días
    contadorDias = contadorDias + 1;

    // Si han pasado los días para regar
    if (contadorDias == diasRiego) {
      // Regamos
      digitalWrite(pinRele, HIGH);
      Serial.println("Enciende riego automático");

      // Comenzamos a contar el tiempo
      marcaTiempo = millis();

      // Iniciamos el contador de días
      contadorDias = 0;
    }
    // Si es otra hora marcamos para que vuelva a detectar
  } else if (tiempoReferencia.hour() != horaRiego) {
    centinelaHora = true;
  }

  // Si está regando
  if (digitalRead(pinRele)) {
    
    // Protegemos para cuando se reinicie millis()
    if (millis() < marcaTiempo) {
      marcaTiempo = 0;
    }
    
    // Comprobamos si ha pasado el tiempo
    if (millis() - marcaTiempo >= duracionRiego) {
      // Apagamos el riego
      digitalWrite(pinRele, LOW);
      Serial.println("Apaga riego automático");
    }
  }
}
