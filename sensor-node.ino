/**********
 * Teensy -> RF24
 * gnd    -> GND 1
 * vcc    -> Vcc 2
 * 9      -> CE 3
 * 10     -> CSN 4
 * 11     -> MOSI 6
 * 12     -> MISO 7
 * 13     -> SCK 5
 * irq(8) is not connected(black wire)
 * 
 * 
 * 
 * 
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//RF24 radio(7, 8);
RF24 radio(9, 10);
const byte rxAddr[11] = "svo-sensor";


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
  
//  delay(1000);
}
