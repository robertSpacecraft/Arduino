//Simple sketch to access the internal hall effect detector on the esp32.
//values can be quite low. 
//Brian Degger / @sctv  

int val = 0;
void setup() {
  Serial.begin(115200);
    }

void loop() {
  // put your main code here, to run repeatedly:
  val = hallRead();
  // print the results to the serial monitor:
  //Serial.print("sensor = ");
  Serial.println(val);//to graph
  delay(1000); 
}
