#include <SoftwareSerial.h>

int tx = 11;
int rx = 10;

char *pattern = "AAA";
long baudRate = 115200;

SoftwareSerial testSerial(rx, tx);
  
void setup()
{
  Serial.begin(115200);
  Serial.print("Sending Pattern \"");
  Serial.print(pattern);
  Serial.print("\" on pin ");
  Serial.print(tx);
  Serial.print(" @ ");
  Serial.print(baudRate);
  Serial.println(" baud.");
  Serial.println("");
  Serial.println("Available baud rates:");
  Serial.println("1. 9600     2.");
  Serial.println("");
  
  testSerial.begin(baudRate);
}

/* Constatly send the given pattern on the softserial */
void loop()
{
  if(Serial.available()){
    int foo = Serial.read();
    switch(foo) {
      case '1': {
        Serial.print("Setting serial to 9600 baud.");
        testSerial.begin(9600);
      } break;
    }
  }
  
  testSerial.print(pattern);
}

