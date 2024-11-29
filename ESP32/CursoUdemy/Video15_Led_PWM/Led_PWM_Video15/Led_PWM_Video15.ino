const byte led_gpio = 33;
int brightness = 0;
int fadeAmount = 5;

void setup() {
 ledcAttachPin(led_gpio, 0);
 ledcSetup(0,1000,8); // (NoLoSe,es la fracuencia en KHz, Resolucion en bits) cuanto menor sea la frecuencia mas rápido "parpadea"
}

void loop() {
  ledcWrite(0, brightness);

  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255){
      fadeAmount = -fadeAmount;
    }
    delay(30);
}
