#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <PubSubClient.h>

#define LED_BUILTIN 2

//Variables sensor
const int sensorPin = 5;

//Credenciales WiFi
const char* ssid = "WEBSTART5G";
const char* password = "jupiterRX85G";

//Credenciales para Cloud MQTT
const char *mqttServer = "farmer.cloudmqtt.com";
const int mqttPort = 18659;
const char *mqttUser = "hohyzidj";
const char *mqttPass = "tF4d1etFplxm";

//Le decimos a MQTT que todas las conexiones que haga las realice a través de nuestro cliente Wifi (espClient)
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

long lastMsgInfrared = 0;
char msgInfrared[50];
int valueInfrared = 0;

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

void callback(char* topic, byte* payload, unsigned int length){ //Ver descripción en void setup(). variable 1: Topico bajo el cual viene la información entrante. variable 2: valor de la información que ha entrado bajo el tópico 1. Variable 3: Tamaño del dato de la variable 2. 
Serial.print("mensaje recibido bajo el tópico: ");
Serial.print(topic);
Serial.print("\n");

for (int i = 0; i < length; i++){
  Serial.print((char)payload[i]);
}

if ((char)payload[0] == '0'){
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("\n Led Apagado");
}else{
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("\n Led Encendido");
}

Serial.println();
}

void reconnect(){
  while (!client.connected()){
    Serial.println("Intentando Conexión MQTT");

    String clientId = "cliente_id_";//Puesto que existen casos en los que después de una conexión la conexión perdida sigue en el servidor no podemos usar el mismo ID de cliente así que al reconectar debe de cambiar automaticamente el ID del cliente.
    clientId = clientId + String(random(0xffff), HEX); //Así se le añade un número aleatorio

    if (client.connect(clientId.c_str(), mqttUser,mqttPass)){//Realizamos la conexión. Usamos un vucle if else para obtener los datos que confirman la nueva conexión o nos indiquen el error de conexión.
      Serial.println("¡Conexión MQTT Reestablecida!");
      client.publish("salidaESPtoMQTT", "Mensaje de Reconexión Exitosa"); //Enviamos un mensaje al servidor MQTT, usando el tópico salidaESPtoMQTT.
      client.subscribe("entradaMQTTtoESP"); //puesto que nos hemos reconectado, podemos y debemos suscribirnos a un topico del cual queramos recibir información gracias a callback()
    }else{
      Serial.println("Error en la Conexión MQTT");
      Serial.println(client.state());
      Serial.print("Reintentando en 3 segundos");
      delay(3000);
      }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT);
  
  setupWifi();
  client.setServer(mqttServer, mqttPort); //Credenciales para después poder conectarse a CLoudMQTT
  client.setCallback(callback); //Es un servicio que se mantiene constantemente activo esperando una conexión entrante desde Cloud MQTT bajo un tópico al que estemos suscrito.
}

void loop() {

  if (!client.connected()){
    reconnect(); //Función para reconectar y reconectar en caso de perder la conexión
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

  if (millis() - lastMsgInfrared > 500){
    lastMsgInfrared = millis();
    int infrared = 0;
    infrared = digitalRead(sensorPin);
      if (infrared == HIGH){
        String mesInfrared = String(infrared);
        mesInfrared.toCharArray(msgInfrared, 50);
        client.publish("salidaESPtoMQTT", msgInfrared);
        Serial.println("El mensaje envíado cuando NO se detecta es este: " + String(msgInfrared));
        } else if (infrared == LOW){
          String mesInfrared = String(infrared);
          mesInfrared.toCharArray(msgInfrared, 50);
          client.publish("salidaESPtoMQTT", msgInfrared);
          Serial.println("El mensaje envíado cuando SI se detecta es este: " + String(msgInfrared));
          }
    }

}