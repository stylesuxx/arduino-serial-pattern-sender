#include <SoftwareSerial.h>

int tx = 11;
int rx = 10;

char *pattern = "Q"; /* 0101 0001*/
long delayTime = 10;
long baudRate = 9600;

SoftwareSerial testSerial(rx, tx);
  
void setup()
{
  Serial.begin(115200);
  testSerial.begin(baudRate);
  
  Serial.println("Available baud rates:");
  Serial.println("1. 9600     5. 31250");
  Serial.println("2. 14400    6. 38400");
  Serial.println("3. 19200    7. 57600");
  Serial.println("4. 28800    8. 115200");
  Serial.println("");
  Serial.println("Change delay:   dXXXX  (0-9999)");
  Serial.println("Change pattern: pXXXXX (5 chars max)");
  Serial.println("");
  
  printStats();
}

void printStats()
{
  Serial.print("Sending Pattern \"");
  Serial.print(pattern);
  Serial.print("\" with a delay of ");
  Serial.print(delayTime);
  Serial.print("ms, on pin ");
  Serial.print(tx);
  Serial.print(" @ ");
  Serial.print(baudRate);
  Serial.println(" baud.");
}

void loop()
{
  if(Serial.available()){
    long newBaudRate = -1;
    int foo = Serial.read();
    switch(foo) {
      /* Change Baud Rate */
      case '1': newBaudRate = 9600; break;      
      case '2': newBaudRate = 14400; break;
      case '3': newBaudRate = 19200; break;
      case '4': newBaudRate = 28800; break;
      case '5': newBaudRate = 31250; break;
      case '6': newBaudRate = 38400; break;
      case '7': newBaudRate = 57600; break;
      case '8': newBaudRate = 115200; break;

      /* Set a new delay values from 0-9999 */
      case 'd': {
        char newDelay[5];
        int counter = 0;
        while(Serial.available() && counter < 4){
          newDelay[counter] = Serial.read();
          counter++;
        }
        newDelay[counter] = '\0';
        delayTime = atol(newDelay);
        printStats();
      } break;
      
      /* Set a new pattern for sending */
      case 'p': {
        int counter = 0;
        while(Serial.available() && counter < 5){
          pattern[counter] = Serial.read();
          counter++;
        }
        pattern[counter] = '\0';
        printStats();
      } break;
    }
    
    if(newBaudRate > 0) {
      testSerial.begin(newBaudRate);
      baudRate = newBaudRate;
      printStats();
    }
  }
  
  testSerial.print(pattern);
  delay(delayTime);
}




