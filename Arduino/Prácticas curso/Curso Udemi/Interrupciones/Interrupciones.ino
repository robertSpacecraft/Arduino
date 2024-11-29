const int pulsador = 3;
const int led = 5;
bool estado_pulsador;
String estado;
void setup() {
  
  Serial.begin(9600);

  pinMode (pulsador, INPUT);
  pinMode (led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pulsador), consulta_estado, FALLING);
  
}

void loop() {

  
  

}

void consulta_estado(){
       
    if (digitalRead(led) == true){ //Si solo ponemos digitalRead(led) ya se le asigna true, no sería necesario poner "= true=
        digitalWrite(led, LOW);
        estado = "APAGADO";
        delay(500);
    } else {
        digitalWrite(led, HIGH);
        estado = "ENCENDIDO";
        delay(500);
      }
    
    Serial.println("estado_pulsador vale: " + String(estado_pulsador) 
                  + " y está: " + (estado));
    
  }
