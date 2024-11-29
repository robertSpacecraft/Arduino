
const int LED_GPIO = 32;
bool led_state = false;
     
const byte interruptPin = 25;
volatile int interruptCounter = 0;
int numberOfInterrupts = 0;

long deboucing_time = 1000;
volatile unsigned long last_micros;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR handleInterrupt(){
  portENTER_CRITICAL_ISR(&mux);
  if((long)(micros() - last_micros) >= deboucing_time * 1000){
    interruptCounter++;
    last_micros = micros();
    }
    portEXIT_CRITICAL_ISR(&mux);
  }

void setup() {
  Serial.begin(115200);
  pinMode(LED_GPIO, OUTPUT);
  Serial.println("Monitorizando interupción: ");
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
}

void loop() {
  if(interruptCounter < 0){
    portENTER_CRITICAL(&mux);
    interruptCounter++;
    portEXIT_CRITICAL(&mux);

    digitalWrite(LED_GPIO, led_state);
    led_state = !led_state;

    numberOfInterrupts++;
    Serial.print("Ha ocurrido una interrupción. Total: ");
    Serial.print(numberOfInterrupts);
  }
}
