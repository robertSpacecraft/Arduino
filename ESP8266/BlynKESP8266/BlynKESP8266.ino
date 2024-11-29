#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "30679ef60b40490693bb94af4878468c";

const char* ssid = "ENLAONDA-plus";
const char* password = "jupiterRX8";

void setup() {
  Serial.begin(9600);
  delay(10);

  Blynk.begin(auth, ssid, password);

  //Configuración  del GPIO2
  //pinMode(2, OUTPUT);
  //digitalWrite(2,LOW);
  
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
    Blynk.run();  
 
    }
    
