#include <SoftwareSerial.h>
#include <string.h>

SoftwareSerial ArduinoSlave(10,11);

String msg;
String old_msg;
String answer;
String old_answer;

String butStr;
String luzStr;

int buttonPin = 12;
int led = 13;
bool estadoled = 0;
int val_luz=0;
const int LDR=A0;
int b;

void setup(){
  Serial.begin(9600);

  ArduinoSlave.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

 

void loop(){
 int val_luz = analogRead(LDR);
 luzStr = String(val_luz);
 //Serial.print("Valor de luz: ");
 Serial.println(val_luz);
 delay(1500);
 b = digitalRead(buttonPin);

if (b == LOW){
  butStr = 'L';
 } else{
 Serial.println("Botão HIGH");
  butStr = 'H';
 }

 msg = butStr + '*' + luzStr + ']';


 //Read answer from slave
 readSlavePort();
 //Send answer to monitor
if (answer!=""){
  Serial.print("Slave received : ");
  Serial.println(answer);
  answer = "";
}
 //Send data to slave
 Serial.print("Master sent : ");
 Serial.println(msg);
 ArduinoSlave.print(msg);
 //ArduinoSlave.write(val_luz);
 old_msg = msg;

}

void readSlavePort(){
  delay(10);
  if (ArduinoSlave.available() > 0){
    bool colchete = false; 
    while(colchete == false){
      char c = ArduinoSlave.read();
      if(c == ']' || c == -1){
        colchete = true;
      } else {
        answer += c;
    }

   } 
  }
}
