#include <SoftwareSerial.h>

#define ledPin 12
SoftwareSerial ArduinoMaster(10,11);

String msg="", oldMsg="";
String but="", luz=""; 
char old_cmd;

int ledPower = 0;
int valLuz, oldValLuz;

void setup() {
 Serial.begin(9600);
 ArduinoMaster.begin(9600);
 pinMode(ledPin, OUTPUT);

}

void loop() {
delay(1000);
 readMasterPort();

 //Serial.println(luz);
 if (luz != ""){
    valLuz = luz.toInt();
 }

if (but == 'H'){
 Serial.println("Botão HIGH");
 analogWrite(ledPin, 255);
 String resposta = String(255);
 resposta = resposta + ']';
 ArduinoMaster.print(resposta);

 } else {
Serial.println("Botão LOW");
 if (valLuz != oldValLuz){
 Serial.print("Master sent: light value ");
 Serial.println(valLuz);

ledPower = map(valLuz, 0, 1023, 0, 255);
 Serial.print("Led intensity: ");
 Serial.println(255 - ledPower);

 
 analogWrite(ledPin, 255 - ledPower);
 oldValLuz = valLuz;
 ledPower = 255 - ledPower;
 String resposta = String(ledPower);
 resposta = resposta + ']';
 ArduinoMaster.print(resposta);
 }
}

}

void readMasterPort(){
 if (ArduinoMaster.available() > 0){
 bool colchete = false; 
 while(colchete == false){
  char c = ArduinoMaster.read();
  if(c == ']'){
    colchete = true;
  } else {
    msg += c;
  }

 }
  
}
 ArduinoMaster.flush();
 

int asteriscoIndex = msg.indexOf('*');
but = msg.substring(0, asteriscoIndex);
luz = msg.substring(asteriscoIndex + 1);
msg = "";
}
