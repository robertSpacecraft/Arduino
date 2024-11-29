// Sensor de Temperatura:
// Incluimos las librerias, definimos el puerto con el protocolo de comunicación de OneWire.
// Declaramos la instancia y Usamos la libreria dallas
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7
OneWire oneWire (ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);

// Display librerias:
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Si el display no usa pin reset, aquí ponemos -1 para no desperdiciar un pin de la placa.
Adafruit_SSD1306 display(-1);

//Declaramos variables y constantes generales:
 byte led = 6;
 byte pulsador_down = 2; //Cable Blanco
 byte pulsador_up = 3; //Cable Verde
 byte ventilador = 5;
 
 int temperatura_limite = 18;
 int temperatura_limiteAux;
 
 float temperatura;
 
 bool ventilador_activado = false;
 bool cambioLimite = false;

 long tiempo_anterior_up;
 long diferencia_up;
 long tiempo_anterior_down;
 long diferencia_down;


void setup() {
    //Iniciamos el monitor serie.
    Serial.begin(9600);
    Serial.println("Iniciando Sistema De Control Temperatura");
    temperatura_limiteAux = temperatura_limite-1;

    //Ventilador:
    pinMode(ventilador, OUTPUT);

    //Pulsadores:
    pinMode(pulsador_up, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pulsador_up), sube_limite, FALLING);    
    pinMode(pulsador_down, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pulsador_down), baja_limite,FALLING);

    //Display:
    display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
    display.clearDisplay();

    dibujaLimite(temperatura_limite);
}

long contador1 = 0;
void loop() {

// Esta función es para que el programa se ejecute una vez por segunto... es mejor que usar delay()
  if (millis() - contador1 > 1000){
      contador1 = millis();
      sensor.requestTemperatures();
      temperatura = sensor.getTempCByIndex(0);
      ventilador_accion();
      dibujaTemperatura(temperatura);
   }

   if(cambioLimite){
      dibujaLimite(temperatura_limite);
      cambioLimite = false;    
   }
}

void ventilador_accion(){

    if (temperatura > temperatura_limite){
        digitalWrite(ventilador, HIGH);
        ventilador_activado = true;
        displayFanOn();
        Serial.println("VENTILADOR ACTIVARDO --> " + String(temperatura));
    }

    if(temperatura_limiteAux > temperatura){
        digitalWrite(ventilador, LOW);
        ventilador_activado = false;
        displayFanOff();
        Serial.println("VENTILADOR DESACTIVADO --> " + String(temperatura));
    }
    
  }

  void sube_limite(){
    diferencia_up = millis() - tiempo_anterior_up;
    tiempo_anterior_up = millis();
    if (diferencia_up > 100){
      temperatura_limite++;
      temperatura_limiteAux++;
      cambioLimite = true;
    }
    }

  void baja_limite(){
    diferencia_down = millis() - tiempo_anterior_down;
    tiempo_anterior_down = millis();
    if (diferencia_down > 100 ){
      temperatura_limite--;
      temperatura_limiteAux--;
      cambioLimite = true;
      }
    }

   void dibujaTemperatura(float temp){
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(2);
    display.setCursor(3, 15);
    display.println("T= " + String(temp, 1));
    display.display();    
    }

   void dibujaLimite(float temp){
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(0.7);
    display.setCursor(0, 0);
    display.println("Max: " + String(temp, 0));
    display.display(); 
    }

    void displayFanOn(){
      Serial.println("displayFanOn --> " );
      display.setTextColor(WHITE, BLACK);
      display.setTextSize(1);
      display.setCursor(100, 0);
      display.println("(X)");
      display.display(); 
    }

    void displayFanOff(){
      Serial.println("displayFanOff --> " );
      display.setTextColor(WHITE, BLACK);
      display.setTextSize(1);
      display.setCursor(100, 0);
      display.println("   ");
      display.display(); 
    }


    
