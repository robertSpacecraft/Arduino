const byte controlPin = 36;
const byte led_gpio = 32;

void setup() {
  Serial.begin(9600);
  ledcAttachPin(led_gpio, 0);
  ledcSetup(0,4000,12);  
}

void loop() {
 ledcWrite(0,analogRead(controlPin));
 Serial.println(analogRead(controlPin));
}
