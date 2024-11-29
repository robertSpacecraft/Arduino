#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//descargamos display
Adafruit_SSD1306 display(-1);

//Pines
byte potenciometro = A0;
byte zumbador = 2;
byte pulsador = 3;

//variable globales
byte medidaInicialCursor = 30;
byte posicionCursor = 0;
byte balaX = 64;
byte balaY = 0;
byte balaXant = 64;
byte balaYant = 0;
byte puntos = 0;
byte vidas = 5;
byte nivel = 0;
byte cuentaPuntos = 0;

bool iniciaJuego = false;


void setup() {
  //Puerto Serial
  Serial.begin(9600);
  //declaramos display con su dirección
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(pulsador,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulsador),cambiaEstadoInicioJuego,FALLING);
  display.display();
  display.clearDisplay();
  display.display();
  
  
  dibujaCursor(50);
  mueveBala(100);
  dibujaTablaPuntos();
  dibujaNivel();
  dibujaVidas();

}

void loop() {
  if(iniciaJuego == false){
    delay(1000);
    display.clearDisplay();
    display.setCursor(5,15);
    display.println("P R E S S  S T A R T");
    display.display();

    while(iniciaJuego == false){
      delay(100);      
      }
     display.clearDisplay();
     dibujaTablaPuntos();
     dibujaNivel();
     dibujaVidas();
    }
  randomSeed(analogRead(A2));
  Serial.println(analogRead(A0));
  int valorPotenciometro = analogRead(A0);
  valorPotenciometro = map(valorPotenciometro,0,660,0,127 - medidaInicialCursor);
  dibujaCursor(valorPotenciometro);
  mueveBala(valorPotenciometro);
  
  
  
}

//funciones

void dibujaCursor(byte pos){
  display.drawLine(0,31,127,31,BLACK);
  display.drawLine(pos,31,pos + medidaInicialCursor,31, WHITE);
  display.display();
}

void mueveBala(byte posicion){
  balaX = balaX + random(-5,5);
  if(balaX>127){
    balaX =127;
    }

   if(balaX <1){
    balaX = 0;
    }

    balaY++;

    if(balaY == 31 && balaX > posicion && balaX < posicion + medidaInicialCursor){
      puntos++;
      cuentaPuntos++;
      if(cuentaPuntos > 5 ){
        nivel++;
        cuentaPuntos = 0;
        }
      medidaInicialCursor = medidaInicialCursor - 2;
      balaY = 0;
      balaX = 30;
      dibujaTablaPuntos();      
      }
    if (balaY > 64){
      vidas--;
      balaY = 0;
      balaX = 30;
      dibujaVidas();
      }
  display.drawPixel(balaXant,balaYant, BLACK);
  display.drawPixel(balaX,balaY, WHITE);
  display.display();

  balaXant = balaX;
  balaYant = balaY;
  }

void dibujaTablaPuntos(){
  display.setCursor(0,0);
  display.setTextColor(WHITE, BLACK);
  display.println("P-> " + String(puntos));
  display.display();
  tone(zumbador,5000,100);
  dibujaNivel();
  }

  void dibujaNivel(){
  display.setCursor(45,0);
  display.setTextColor(WHITE, BLACK);
  display.println("L-> " + String(nivel));
  display.display();
  tone(zumbador,5000,100);
  delay(100);
  tone(zumbador,10000,100);
  delay(100);
  tone(zumbador,15000,100);
  }

 void dibujaVidas(){
  display.setCursor(90,0);
  //display.setTextColor(WHITE,BLACK);
  display.println("V-> " + String(vidas));
  display.display();
  tone(zumbador,500,100);
  delay(100);
  tone(zumbador,200,100);
  delay(100);
  tone(zumbador,500,100);
  if (vidas == 0){
    vidas = 5;
    nivel = 0;
    medidaInicialCursor = 30;
    display.clearDisplay();
    display.setCursor(5,15);
    display.println("G A M E  O V E R");
    display.display();
    tone(zumbador, 200, 2500);
    delay(2000);
    display.clearDisplay();
    iniciaJuego = false;
    }
  }

 void cambiaEstadoInicioJuego(){
  iniciaJuego = true;
  }
