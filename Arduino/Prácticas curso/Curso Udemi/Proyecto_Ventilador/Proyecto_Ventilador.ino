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
 
 int temperatura_limite = 25;
 
 float temperatura;
 
 bool ventilador_activado = false;
 bool cambioLimite = false;

 long tiempo_anterior_up;
 long diferencia_up;
 long tiempo_anterior_down;
 long diferencia_down;

 //Declaramos arrays
 int bufferTemps[128];

void setup() {
    //Iniciamos el monitor serie.
    Serial.begin(9600);
    Serial.println("Iniciando Sistema De Control Temperatura");

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

    //Lleno el array con valores grandes para que no me dibuje una línea inicial con valor 0
    for(int i = 0; i < 128; i++){
      bufferTemps[i] = 110;
      }
}

long contador1 = 0;
void loop() {

// Esta función es para que el programa se ejecute una vez por segunto... es mejor que usar delay()
  if (millis() - contador1 > 1000){
    contador1 = millis();
    sensor.requestTemperatures();
    temperatura = sensor.getTempCByIndex(0);
    llenaArray(temperatura);
    ventilador_accion();
    dibujaTemperatura(temperatura);
    dibujaCuadricula();
    dibujaCurva();
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
    Serial.println("VENTILADOR ACTIVARDO --> " + String(temperatura));
    } else {
      digitalWrite(ventilador, LOW);
      ventilador_activado = false;
      Serial.println("VENTILADOR DESACTIVADO --> " + String(temperatura));
      }
  
  }

  void sube_limite(){
    diferencia_up = millis() - tiempo_anterior_up;
    tiempo_anterior_up = millis();
    if (diferencia_up > 100){
      temperatura_limite++;
      cambioLimite = true;
      }
    }

  void baja_limite(){
    diferencia_down = millis() - tiempo_anterior_down;
    tiempo_anterior_down = millis();
    if (diferencia_down > 100 ){
      temperatura_limite--;
      cambioLimite = true;
      }
    }

   void dibujaTemperatura(float temp){
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("T = " + String(temp, 1));
    display.display();    
    }

   void dibujaLimite(float temp){
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(1);
    display.setCursor(64, 0);
    display.println("T = " + String(temp, 0));
    display.display(); 
    }

    void dibujaCuadricula(){
      display.fillRect(0,13,128,54, BLACK);
      //Este for repite 10 veces a una distancia de 5 pixeles verticales la linea de puntos del siguiente for.
      for(int b = 10; b < 64; b = b + 5){        
        //dibuja línea de puntos
        for (int i = 0; i < 128; i = i + 12){
         display.drawPixel(i,b,WHITE);
          }
          //Este if dibuja una linea de punto más juntos.
          if (b == 20){
          for (int i = 0; i < 128; i = i + 2){
          display.drawPixel(i,b,WHITE);
          }
        }
      }
    }

    void dibujaCurva(){
      for (int i = 0; i < 128; i++){
        if(bufferTemps[i]<109){
            int y = map(bufferTemps[i],-5,50,27,12);
            display.drawPixel(i,y,WHITE);
          }
        }
      }

    void llenaArray(float temp){
      for(int i = 1; i < 128; i++){
        bufferTemps[i-1] = bufferTemps[i];
        }
        bufferTemps[127] = temp;
      }
    
