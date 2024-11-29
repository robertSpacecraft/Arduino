#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>


//Punteros
const char* ssid = "WEBSTART5G";
const char* password ="jupiterRX85G";

//Datos de conexión Wifi estática
IPAddress ip(192,168,1,22);
IPAddress gateway(192,168,1,1);
IPAddress Subnet(255,255,255,0);
IPAddress wifiDNS1(8,8,8,8);
IPAddress wifiDNS2(8,8,4,4);

//Datos de acceso al servidor MQTT
const char *mqtt_server = "	farmer.cloudmqtt.com";
const int mqtt_port = 18659;
const char *mqtt_user = "hohyzidj";
const char *mqtt_pass = "	tF4d1etFplxm";

//Declaramos instancias
WiFiClient espCient;
PubSubClient client(espCient);

long lastMsg = 0;
char msg[50];
int value = 0;

//Función conectar wifi
void setupWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, Subnet, wifiDNS1, wifiDNS2);
  Serial.print("conectando a: \t");
  Serial.println(ssid);

  //Esperamos 30 segundos a que nos conectemos:
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 100){
    delay(500);
    Serial.print('.');
  }
  if (i == 101){
    Serial.println("No ha sido posible establecer la conexión.");
    return;
  }

  //Mostramos mensaje de conexión exitosa y la ip:
  Serial.println("Conexión Establecida \n");
  Serial.print("IP address: \t");
  Serial.println(WiFi.localIP());  
}

//Función callBack que es cuando el servidor manda un mensaje
void callBack(char* topic, byte* payload, unsigned int length){
  Serial.print("Mensaje recibido bajo el tópico --> ");
  Serial.print(topic);
  Serial.print("\n");

  for (int i = 0; i < length; i++){
    Serial.print((char)payload[i]);
  }

  Serial.println();
}
// Función reconexión 
void reconnect(){
  while (!client.connected()){
    Serial.println("Intentando Conexión MQTT");
    String clientId = "client_Id_";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(),mqtt_user,mqtt_pass)){
      Serial.println("Conexión MQTT Establecida!");
      client.publish("salida", "Primer mensaje");
      client.subscribe("entrada");
    }else {
      Serial.println("Fallo de conexión");
      Serial.println(client.state());
      Serial.println("Reintentando en 5s");
      delay(5000);
    }
  }
}

void setup() {
  //Encendemos un LED y ponemos en marcha el monitor serial
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  delay(10);
  Serial.println();

  setupWifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callBack);

  
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);

  if (!client.connected()){
    reconnect();
  }

  client.loop();
  
  if (millis() - lastMsg > 2000){
    lastMsg = millis();
    value++;

    String mes = "Valor --> " + String(value);
    mes.toCharArray(msg, 50);
    client.publish("salida", msg);
    Serial.println("Mensaje Enviado -->" + String(value) );
  }
}