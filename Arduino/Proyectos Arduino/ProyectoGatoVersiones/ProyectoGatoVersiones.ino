const byte trigger = 2;
const byte echo = 3;

int distancia;


void setup() {
  Serial.begin(9600);
  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, LOW);

}

void loop() {
  Serial.println(mideDistancia());
}

int mideDistancia(){
  gatillo();
  long tiempo = pulseIn(echo, HIGH);
  distancia = tiempo / 58;
  return distancia;
  }

void gatillo(){
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  }
