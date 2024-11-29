
const byte trigger = 4;
const byte echo = 5;

int distancia;

uint8_t redPin= 32;
uint8_t greenPin = 33;
uint8_t bluePin = 25;

uint8_t ledArray[3] = {1, 2, 3};

void setup() {
  Serial.begin(115200);
  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, LOW);

  ledcAttachPin(redPin, 1);
  ledcAttachPin(greenPin, 2);
  ledcAttachPin(bluePin, 3);

  ledcSetup(1, 12000, 8);
  ledcSetup(2, 12000, 8);
  ledcSetup(3, 12000, 8);
}

void loop() {
  Serial.println(mideDistancia());

  if (distancia < 20){
    ledcWrite(1, 50);
    } else if (distancia > 21 && distancia < 60){
      ledcWrite(2, 50);
      } else if (distancia > 61 && distancia < 90){
      ledcWrite(3, 50);
      } else{
        ledcWrite(1, 0);
        ledcWrite(2, 0);
        ledcWrite(3, 0);
        }
  
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
