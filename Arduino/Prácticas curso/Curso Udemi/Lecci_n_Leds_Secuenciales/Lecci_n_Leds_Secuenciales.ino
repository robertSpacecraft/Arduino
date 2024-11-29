const int pinLed3 = 3;
const int pinLed5 = 5;
const int pinLed6 = 6;

const int pinPlaca =13;
int tEncendido = 100;
int tApagado = 100;
int brillo =0;

void setup() {
  pinMode(pinLed3, OUTPUT);
  pinMode(pinLed5, OUTPUT);
  pinMode(pinLed6, OUTPUT);
  pinMode(pinPlaca, OUTPUT);

}

void izquierda(){
  
  digitalWrite(pinLed3, HIGH);
  digitalWrite(pinLed5, LOW);
 // digitalWrite(pinLed6, LOW);
  delay(tEncendido);
  
  digitalWrite(pinLed3, LOW);
  digitalWrite(pinLed5, HIGH);
 // digitalWrite(pinLed6, LOW);
  delay(tEncendido);

  digitalWrite(pinLed3, LOW);
  digitalWrite(pinLed5, LOW);
 // digitalWrite(pinLed6, HIGH);
  delay(tEncendido);
  }

void derecha(){

  digitalWrite(pinLed3, LOW);
  digitalWrite(pinLed5, LOW);
 // digitalWrite(pinLed6, HIGH);
  delay(tEncendido);
  
  digitalWrite(pinLed3, LOW);
  digitalWrite(pinLed5, HIGH);
 // digitalWrite(pinLed6, LOW);
  delay(tEncendido);

  digitalWrite(pinLed3, HIGH);
  digitalWrite(pinLed5, LOW);
 // digitalWrite(pinLed6, LOW);
  delay(tEncendido);
  
  }

  void latido(){

    for (brillo; brillo <=255; brillo++ ){

      analogWrite(pinLed6, brillo);
      delay(2);     
      }

     for (brillo; brillo >=0; brillo--){

      analogWrite(pinLed6, brillo);
      delay(2);
      } 
    
    }

void loop() {

 for (int i = 0; i <= 5; i++){
  
  latido();
  izquierda();
  delay(tEncendido);
  derecha();
  delay(tEncendido);
  }

  
  
  digitalWrite(pinLed3, HIGH);
  digitalWrite(pinLed5, HIGH);
 // digitalWrite(pinLed6, HIGH);
  delay(tEncendido * 2000);
 
}
