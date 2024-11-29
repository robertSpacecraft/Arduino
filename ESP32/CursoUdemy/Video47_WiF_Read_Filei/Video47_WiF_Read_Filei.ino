#include <WiFi.h>

const char* ssid = "ENLAONDA-plus";
const char* password = "jupiterRX8";

const char* host = "https://iottsesp32.s3.eu-west-2.amazonaws.com";
String url = "/iottsAWS.txt";


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
  delay(5000);

  Serial.print("Conectando con: ");
  Serial.print(host);

  WiFiClient client;
  const int httpPort = 80;
  if(!client.connect(host, httpPort)){
    Serial.print("Conexión fallida");
    return;
    }

  Serial.print("Solicitando URL: ");
  Serial.print(url);

  client.print(String("GET ") + url + "(HTTP/1.1\r\n" +  "Host: " + host + "\r\n" + "Conexión: Finalizada\r\n\r\n");
  unsigned long timeout = millis();
  while(client.available() == 0){
    if(millis() - timeout > 5000){
      Serial.println(">>> Tiempo de espera agotado! ");
      client.stop();
      return;
      }
    } 
}
