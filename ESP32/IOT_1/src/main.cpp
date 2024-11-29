#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

#define LED_BUILTIN 2

//Variables sensor
const int sensorPin = 3;

// Punteros nombre y contraseña red wifi
const char* ssid ="ENLAONDA-plus";
const char* password ="jupiterRX8";

//Constantes y credenciales del servidor MQTT
const char *mqtt_server = "farmer.cloudmqtt.com";
const int mqtt_port = 18944;
const char *mqtt_user ="rxtshwoe";
const char *mqtt_pass = "ECKuR1mRK6Ru";

//instancias
WiFiClient espClient;
PubSubClient client(espClient); //Esto le dice al protocolo MQTT que todas las conexiones las va a hacer a través del ESP32 

//variables y constantes generales
long lastMsg = 0;
char msg[50];
int value = 0;

long lastMsgInfrared = 0;
char msgInfrared[50];
int valueInfrared = 0;

//función callback: Es un servicio que se mantiene atento por si el servidor MQTT se pone en contacto con ESP32
void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Mensaje recibido bajo el tópico: ");
  Serial.print(topic);
  Serial.print("\n");

  for (int i = 0; i<length; i++){
    Serial.print((char)payload[i]);
  }
  
  if ((char)payload[0] == '0'){
    Serial.println("\n Led Apagado");
    digitalWrite(LED_BUILTIN, HIGH);

  }else{
    Serial.println("\n Led Encendido");
    digitalWrite(LED_BUILTIN, LOW);
  }

Serial.println();

}

//función para comprobar y reconectar al servidor
void reconnect(){
  while(!client.connected()){
    Serial.println("Intentando conexión MQTT: ");

    String clientId = "client_Id_";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)){
      Serial.println("Conexión exitosa!");
      client.publish("salidaESPtoMQTT", "Primer mensaje");
      client.subscribe("entradaMQTTtoESP");
    }else{
      Serial.println("Conexión Fallida!");
      Serial.print(client.state());
      Serial.print("Reintentado en 5s");
      delay(5000);
    }
  }
}

//funcion conexión wifi
void setupWifi(){
  Serial.println();
  Serial.println("Conectando a: ");
  Serial.println(ssid);
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);

  //conectamos a Wifi
  setupWifi();

  //Conectamos con el servidor
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if(!client.connected()){
    reconnect();
  }

  client.loop();
  
   /*if (millis() - lastMsg > 2000){
   lastMsg = millis();
    value++;
    String mes = "Valor -->" + String(value);
    mes.toCharArray(msg, 50);
    client.publish("salidaESPtoMQTT", msg);
    Serial.println("Mensaje enviado desde ESP8266 -->" + String(value));
  }*/
bool sent = false;
   if (millis() - lastMsgInfrared > 500){
    lastMsgInfrared = millis();
    int infrared = 0;
    infrared = digitalRead(sensorPin);
      if (infrared == HIGH){
        sent = false;
        //String mesInfrared = String(infrared);
        //mesInfrared.toCharArray(msgInfrared, 50);
        //client.publish("salidaESPtoMQTT", msgInfrared);
        Serial.println("El mensaje envíado cuando NO se detecta es este: " + String(msgInfrared));
        } else if (infrared == LOW && sent == false){
          String mesInfrared = String(infrared);
          mesInfrared.toCharArray(msgInfrared, 50);
          client.publish("salidaESPtoMQTT", msgInfrared);
          Serial.println("El mensaje envíado cuando SI se detecta es este: " + String(msgInfrared));
          sent = true;
          }
    }
}