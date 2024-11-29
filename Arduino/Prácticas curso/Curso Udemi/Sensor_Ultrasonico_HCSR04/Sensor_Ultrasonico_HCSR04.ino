const byte trigg = 3;
const byte echo = 2;


void setup() {
  Serial.begin(9600);
  pinMode(trigg, OUTPUT);
  pinMode(echo, INPUT);

  digitalWrite(trigg, LOW);

  
}

void loop() {
  Serial.println(mideDistancia());  

}

int mideDistancia(){
  gatillo();
  long tiempo = pulseIn(echo, HIGH);
  int distancia = tiempo / 58;
  return distancia;
  }

void gatillo(){
  digitalWrite(trigg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigg, LOW);
  
  }
