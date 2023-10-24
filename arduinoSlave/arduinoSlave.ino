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
 readMasterPort();
 valLuz = atoi(luz);

if (but == "H"){
 analogWrite(ledPin, 255);
 } else {
 if (valLuz != oldValLuz){
 Serial.print("Master sent: light value is ");
 Serial.println(valLuz);

ledPower = map(valLuz, 0, 1023, 0, 255);
 Serial.print("Led intensity: ");
 Serial.print(ledPower);
 Serial.println("%");

ArduinoMaster.print(ledPower);
 analogWrite(ledPin, ledPower);
 oldValLuz = valLuz;
 }
}

}

void readMasterPort(){
 delay(10);
 if (ArduinoMaster.available() > 0){
 char c = ArduinoMaster.read();
 msg += c;

}
 ArduinoMaster.flush();

int asteriscoIndex = msg.indexOf('*');
 but = msg.substring(0, asteriscoIndex);
 luz = msg.substring(asteriscoIndex + 1);

}

/*void convertMsgToCmd(){
 if (msg.length() > 0){
 Serial.print("Message size: ");
 Serial.println(msg.length());

char carrayl [6];
 msg.toCharArray(carrayl, sizeof(carrayl));
 val = atoi(carrayl)
 }
}*/
