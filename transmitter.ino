/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SFE_BMP180.h> // to read pressure
#include <dht.h> //for the temperature
#include <string.h>

#define ALTITUDE 1655.0
#define DHT11_PIN 8
#define DECIMAL_STR_LENGTH 11
#define TEST_STRING "CHECK CHECK 123 "
#define TEXT_MAX_LENGTH 100

RF24 radio(9, 10); // CE, CSN
SFE_BMP180 pressure;
dht DHT;

const byte address[6] = "00001";
char decimalAsString[DECIMAL_STR_LENGTH] = "         ";

char *doubleToString(double d);
void writeToMessage(char *text);
void sendMessage();

struct message{
  char text[TEXT_MAX_LENGTH];
  char *curs0r = text;
  int checksum;
}transMsg;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  if(pressure.begin() == 0)
    Serial.println("Error initializing BMP");
}

void loop() {
  char stat;
  double T,P;
  short transmit_period = 2000;
  int chk = DHT.read11(DHT11_PIN);

  //Get temp for pressure reading
  stat = pressure.startTemperature();
  if(stat != 0)
    delay(stat);
  stat = pressure.getTemperature(T);
  //If stat is 0, there is an i2c error
  if(stat == 0){
    Serial.println("BMP: Temperature Error (I2C)");
    T = -273.15;
  }
  stat = pressure.startPressure(3);
  if(stat != 0)
    delay(stat);
  if(T != -273.15){
    stat = pressure.getPressure(P,T);
    //If stat is 0, there is an i2c error
    if(stat == 0){
      Serial.println("BMP: Pressure Error (I2C)");
      P = 0;
    }
  }
  writeToMessage("Air:");
  writeToMessage(doubleToString(analogRead(A0)));
  //doubleToString(100.321);
  writeToMessage(" Soil:");
  writeToMessage(doubleToString(analogRead(A1)));

  writeToMessage(" BMPPres:");
  writeToMessage(doubleToString(P));

  writeToMessage(" BMPTemp:");
  writeToMessage(doubleToString(T));


  writeToMessage(" Hum:");
  writeToMessage(doubleToString(DHT.humidity));
  writeToMessage(" Temp:");
  writeToMessage(doubleToString(DHT.temperature));
  //writeToMessage("TESTING 123");
  Serial.println(transMsg.text);
  sendMessage();
  delay(transmit_period);
}

char *doubleToString(double d){
  int prefix, postfix;
  char pre[DECIMAL_STR_LENGTH - 3], post[2];
  char decimal = '.';

  //Get the digits before the decimal
  prefix = (int)d;
  //Get the digits 2 places after the decimal
  postfix = abs((int)(100*(d - (double)prefix)));
  //Make prefix a String in base 10
  itoa(prefix, pre, 10);
  //Serial.print(pre);
  //Make postfix a String in base 10
  itoa(postfix, post, 10);
  //Serial.print('.');
  //Serial.println(post);
  //Put it all together
  strcpy(decimalAsString,pre);
  strcat(decimalAsString,".");
  strcat(decimalAsString,post);
  //Serial.println(decimalAsString);
  return decimalAsString;
}

void writeToMessage(char *text){
  int len = strlen(text);
  strcpy(transMsg.curs0r,text);
  transMsg.curs0r += len;
}

void sendMessage(){
  //generate checksum
  for(int i = 0; i < TEXT_MAX_LENGTH; i++){
    transMsg.checksum += (short)transMsg.text[i];
  }
  //Send the message
  radio.write(&transMsg, sizeof(transMsg));
  //Reset message
  memset(transMsg.text, 0, TEXT_MAX_LENGTH);
  transMsg.curs0r = transMsg.text;
  transMsg.checksum = 0;
}

