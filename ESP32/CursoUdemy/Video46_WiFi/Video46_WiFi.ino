#include <WiFi.h>

const char* ssid = "ENLAONDA-plus";
const char* password = "jupiterRX8";


void setup(){
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Conectado a la red WiFi, su dirección IP es: ");
  Serial.print(WiFi.localIP());  
}

void loop(){

}
