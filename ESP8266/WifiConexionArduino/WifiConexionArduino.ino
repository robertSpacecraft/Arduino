#include <ESP8266WiFi.h>

const char* ssid = "ENLAONDA-plus";
const char* password = "jupiterRX8";

void setup() {
  Serial.begin(9600);
  delay(10);

  //Configuración  del GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
  
  Serial.print("Conectandose a red : ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); //Conexión a la red
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conexión Establecida \n");
  Serial.print("IP address: \t");
  Serial.println(WiFi.localIP());
}

void loop() {
  
 
    }
    
