//***** Load Libraries *****
#include <SparkFunLSM6DS3.h>
#include <Wire.h>
#include <SPI.h>
#include <Sodaq_BMP085.h>
#include <Servo.h>

//***** Initialize Naming Scheme For Sensors and Control *****
LSM6DS3 myIMU; //Default constructor is I2C, addr 0x6B
Sodaq_BMP085 bmp;
Servo myServo1, myServo2;

//***** Servo Pin Designations *****
int servo1Pin = 9;
int servo2Pin = 10;

void setup() {

  Serial.begin(9600);
  delay(1000); //relax...
  Serial.println("Processor came out of reset.\n");
  Wire.setClock(800000UL);

//***** Attatch Servo to Board *****
  myServo1.attach(servo1Pin);
  myServo2.attach(servo2Pin);

  //Call .begin() to configure the IMU & Barometer
  myIMU.begin();
  bmp.begin();
}


void loop()
{

  //______________________________________________
  // *****Gets Linear Acceleration Off IMU*****
  //______________________________________________
  float ax = myIMU.readFloatAccelX();
  float ay = myIMU.readFloatAccelY();
  float az = myIMU.readFloatAccelZ();
  Serial.print("\nAccelerometer:\n");
  Serial.print(ax);
  Serial.print("\t");
  Serial.print(ay);
  Serial.print("\t");
  Serial.println(az);

  if (ax > 0) {
    myServo1.write(90+40*ax);
  }
  if (ax < 0) {
    myServo1.write(90+40*ax);
  }
  if (ax = 0) {
    myServo1.write(90);
  }
  if (ay > 0) {
    myServo2.write(90+40*ay);
  }
  if (ay < 0) {
    myServo2.write(90+40*ay);
  }
  if (ay = 0) {
    myServo2.write(90);
  }

  //_______________________________________________
  //  *****Gets Angular Velocity Off IMU*****
  //_______________________________________________
  float gx = myIMU.readFloatGyroX();
  float gy = myIMU.readFloatGyroY();
  float gz = myIMU.readFloatGyroZ();
  Serial.print("\nGyroscope:\n");
  Serial.print(gx);
  Serial.print("\t");
  Serial.print(gy);
  Serial.print("\t");
  Serial.println(gz);

  //_______________________________________________________
  //  *****Get Temperature Values in °F and °C Off IMU*****
  //_______________________________________________________

  float TF_I = myIMU.readTempF();
  float TC_I = myIMU.readTempC();
  Serial.print("\nThermometer IMU:\n");
  Serial.print(TF_I);
  Serial.print("\t");
  Serial.println(TC_I + 1.59);

  //__________________________________________________________
  //  *****Get Temperature Values in °F and °C Off BMP180*****
  //__________________________________________________________

  float TC_bmp = bmp.readTemperature();
  Serial.print("\nThermometer BPM:\n");
  Serial.println(TC_bmp - 0.5);

  //___________________________________________________
  //  *****Get Pressure Values in Pa Off BMP180*****
  //___________________________________________________

  float pr = bmp.readPressure();
  Serial.print("\nBarometer (Pa):\n");
  Serial.print(pr);
  Serial.println(" Pa");

  delay(1);
}
