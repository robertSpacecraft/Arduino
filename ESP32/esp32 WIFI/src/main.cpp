#include <Arduino.h>
#include <WiFi.h>

const char* ssid ="ENLAONDA-plus";
const char* password ="jupiterRX8";

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("");
  Serial.println("");

  Serial.print("Conectado a: ");
  Serial.print(ssid);

  //me conecto a la red WiFi

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }

  Serial.println("");
  Serial.println("CONECTADO");

  Serial.print("Mi ip es: ");
  Serial.println(WiFi.localIP());
}

void loop() {

}
