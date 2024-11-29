const int pulsador = 3;
const int led = 5;

bool estado_pulsador;
String estado;

long tiempoAnterior;
long diferencia;

void setup() {
  
  Serial.begin(9600);

  pinMode (pulsador, INPUT);
  pinMode (led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pulsador), consulta_estado, FALLING);
  
}

void loop() {
 
 // Serial.println(millis()); //esto es solo para ver en el monitor serie los datos que devulve millis()


}

void consulta_estado(){

  diferencia = millis() - tiempoAnterior;
  Serial.println(String(diferencia) + " Este es tiempo anterior: " + String(tiempoAnterior) + " Este es millis: " + millis());
  tiempoAnterior = millis();
  

  if(diferencia > 500){
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
  
    
    
  }
