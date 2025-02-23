#include "MPU9250.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;

void setup() {
  // serial to display data
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);
}

void loop() {

  // read the sensor
  IMU.readSensor();

  float aceleracionX = map(IMU.getAccelX_mss(),0,9.6,0,90); //Inclinacion en el eje x de 0 a 90 pero cuenta de 10 en 10
  Serial.println("Inclinacion X: " + (String(aceleracionX))+ "º");
 
  
  
 
  //Serial.print("Inclinacion Y: ");
  //Serial.println(IMU.getAccelY_mss(),3);
  //Serial.print("Inclinacion X: ");
  //Serial.println(IMU.getAccelZ_mss(),3);
  //Serial.print("\n");
  //Serial.print(IMU.getGyroX_rads(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getGyroY_rads(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getGyroZ_rads(),6);
  //Serial.print("\n");
  //Serial.print(IMU.getMagX_uT(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getMagY_uT(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getMagZ_uT(),6);
  //Serial.print("\n");
  //Serial.println(IMU.getTemperature_C(),6);
  delay(20);

}
