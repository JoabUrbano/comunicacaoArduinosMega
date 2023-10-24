#include <SoftwareSerial.h>
#include <string.h>
/*#include <iostream>
using namespace std;*/
//#include <vector.h>

SoftwareSerial ArduinoSlave(10,11);

String cmd;
String old_cmd;
String answer;
String old_answer;

String butStr;
String luzStr;

int buttonPin = 12;
int led = 13;
bool estadoled = 0;
int val_luz=0;
const int LDR=A0;

void setup(){
  Serial.begin(9600);
  Serial.println("ENTER Commands:");

  ArduinoSlave.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

 

void loop(){
 int val_luz = analogRead(LDR);
 luzStr = String(val_luz);
 //Serial.print("Valor de luz: ");
 //Serial.println(val_luz);
 delay(1500);

if (digitalRead(buttonPin) == LOW){
 //estadoled = !estadoled;
 //digitalWrite(led, estadoled);
 //Serial.println("Botão LOW");
 butStr = 'L';
 } else{
 //Serial.println("Botão HIGH");
 butStr = 'H';
 }

//Serial.println(butStr);
 cmd = butStr + "*" + valStr;
 //Serial.println (cmd);
 //old_cmd=cmd;
 //old_answer=answer;


 //Read answer from slave
 readSlavePort();
 //Send data to slave
 //if(cmd!=old_cmd){
 Serial.print("Master sent : ");
 Serial.println(cmd);
 ArduinoSlave.write(cmd);
 //ArduinoSlave.write(val_luz);
 old_cmd = cmd;

//}
 //Send answer to monitor
if (answer!=""){
  Serial.print("Slave received : ");
  Serial.println(answer);
  }
}

void readSlavePort(){
 delay(10);

if (ArduinoSlave.available() >0){
 char c = ArduinoSlave.read();
 answer += c;

}
}
