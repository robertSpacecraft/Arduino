const byte controlPin = 25;


void setup() {
  Serial.begin(115200);
 
}

void loop() {
  for(int value = 0; value < 255; value++){
    dacWrite(controlPin, value);
    }

    for(int value = 255; value > 0; value--){
    dacWrite(controlPin, value);
    }

    for (int deg = 0; deg < 360; deg++){
      dacWrite(controlPin, int(128 + 80 * (sin(deg*PI/180))));
      }
}
