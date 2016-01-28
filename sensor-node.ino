#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte rxAddr[11] = "svo-sensor";

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setAutoAck(1);
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();
}

void loop()
{
  const char text[] = "Hello World";
  bool ok = radio.write(&text, sizeof(text));
  Serial.println(ok);
  delay(1000);
}
