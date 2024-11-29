#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>


//Variables sensor
const int sensorPin = 5;

//Credenciales WiFi Fábrica
const char* ssid = "WEBSTART5G";
const char* password = "jupiterRX85G";

//Variables para mandar mensajes. A través de MQTT?
long lastMsg = 0;
char msg[50];
int value = 0;

//Variables para mandar datos del sensor infrarrojo. A través de MQTT?
long lastMsgInfrared = 0;
char msgInfrared[50];
int valueInfrared = 0;

//Variables
bool sent = false;

//función conexión wifi DHCP Manual
IPAddress wifiIp(192,168,1,22);
IPAddress wifiSubNet(255,255,255,0);
IPAddress wifiGW(192,168,1,1);
IPAddress wifiDNS1(8,8,8,8);
IPAddress wifiDNS2(8,8,4,4);

void setupWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.config(wifiIp, wifiSubNet, wifiGW, wifiDNS1, wifiDNS2);
  WiFi.begin(ssid, password);
  
  Serial.print("Estableciendo Conexión WiFi con: \t");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print('.');
  }

  Serial.println();
  Serial.println("¡Conextión WiFi Exitosa!");
  Serial.print("Tu dirección IP es:\t");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT);

  setupWifi();
}

void loop() {

  if (millis() - lastMsgInfrared > 500){
    lastMsgInfrared = millis();
    int infrared = 0;
    infrared = digitalRead(sensorPin);
      if (infrared == HIGH){
        sent = false;
        Serial.println("El mensaje envíado cuando NO se detecta es este: " + String(msgInfrared));
        } else if (infrared == LOW && sent == false){
          HTTPClient http;
          http.begin("http://iottechnologysystems.com/sendMail.php");
          int httpCode = http.GET();
          if(httpCode > 0) {
            String payload = http.getString();
            Serial.println(payload);
            sent = true;
            }
            http.end();

          String mesInfrared = String(infrared);
          mesInfrared.toCharArray(msgInfrared, 50);
          
          Serial.println("El mensaje envíado cuando SI se detecta es este: " + String(msgInfrared));
          }
  }

}