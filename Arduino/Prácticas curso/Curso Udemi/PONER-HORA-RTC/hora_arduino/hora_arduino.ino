// Librería para convertir de BCD a decimal y viceversa
#include <RTClib.h>

// Incluimos la librería del proyecto Arduino para I2C
#include "Wire.h"

// Esta es la dirección de nuestro módulo
#define DS3231_I2C_ADDRESS 0x68

void setup() {
  // Inicializamos el Monitor Serial para nuestras pruebas
  Serial.begin(9600);

  // Inicializamos nuestra librería
  Wire.begin();

  // Opcional: configuramos la hora
  Wire.beginTransmission(DS3231_I2C_ADDRESS);

  Wire.write(0x00); // El primer byte es la dirección en la que escribiremos

  // Para nuestro ejemplo usé Junio 8, 2017 a las 18:25:30
  Wire.write(RTClib::dec2bcd(30)); // Segundos 0-59
  Wire.write(RTClib::dec2bcd(25)); // Minutos 0-59
  Wire.write(RTClib::dec2bcd(18)); // Hora 0-23 en formato de 24 horas (aunque soporta formato 12h no lo veremos)
  Wire.write(RTClib::dec2bcd(5));  // Día de la semana 1-7
  Wire.write(RTClib::dec2bcd(8));  // Dia 1-31
  Wire.write(RTClib::dec2bcd(6));  // Mes 1-12
  Wire.write(RTClib::dec2bcd(17)); // Anio 0-99
  Wire.endTransmission();
}

void loop() {
  int x;
  byte buffer[7];

  // Para leer el reloj simplemente iniciamos una transmision y enviamos un 0 solamente
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();

  // Solo leeremos 7 bytes ya que nos alcanza para la fecha y hora
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);

  // Leemos 7 bytes
  for (x = 0; x < 7; x++) {
    buffer[x] = Wire.read();
  }

  // Mostramos la fecha y hora leida
  Serial.println(String("Fecha (D/M/Y) ") + RTClib::bcd2dec(buffer[4]) + "/" + lib::bcd2dec(buffer[5])
                 + "/20" + RTClib::bcd2dec(buffer[6]) + ", Hora " + RTClib::bcd2dec(buffer[2])
                 + ":" + RTClib::bcd2dec(buffer[1]) + ":" + RTClib::bcd2dec(buffer[0]));
  Serial.println("");

  // Leeremos la hora cada 5 segundos
  delay(5000);
}
