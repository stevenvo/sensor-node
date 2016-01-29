#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8);
const byte rxAddr[11] = "svo-sensor";


// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high

#define OUTPUT_READABLE_QUATERNION

typedef struct {
  float X;
  float Y;
} Quat;

typedef struct {
  Quat Q;
} Mpu_Data;

Mpu_Data mpu_data;


void setup_RF24(){
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setAutoAck(1);
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  setup_RF24();
}

void loop() {

  Quat quat;
  quat.X = 2.0;
  quat.Y = 3.0;
  mpu_data.Q = quat;
  bool ok;
  
//  const char text[] = "Hello World";
//  ok = radio.write(&text, sizeof(text));
//  Serial.println(ok);

  ok = radio.write(&mpu_data, sizeof(mpu_data));
  Serial.println(ok);
  
  delay(1000);
}
