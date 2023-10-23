#include <SoftwareSerial.h>

SoftwareSerial ArduinoSlave(10,11);

char cmd="";

char old_cmd;

char answer="";

char old_answer;




int button = 12;

int led = 13;

bool estadoled = 0;



int val_luz=0;

const int LDR=A0;



void setup(){

  Serial.begin(9600);

  Serial.println("ENTER Commands:");

  ArduinoSlave.begin(9600);



  pinMode(button, INPUT_PULLUP);

  pinMode(led, OUTPUT);



}

void loop(){

  int val_luz = analogRead(LDR);

  Serial.print("Valor de luz: ");

  Serial.println(val_luz);

  delay(500);



  if (digitalRead(button == LOW){

    //estadoled = !estadoled;

    //digitalWrite(led, estadoled);

    Serial.println("Botão LOW");

  } else {

    Serial.println("Botão HIGH");

  }



  old_cmd=cmd;

  old_answer=answer;

  //Read command from monitor

  if(Serial.available()){

    cmd=Serial.read();

  }

    //Read answer from slave

    if (ArduinoSlave.available()){

      answer=ArduinoSlave.read();

    }

    //Send data to slave

    if(cmd!=old_cmd){

      Serial.print("Master sent : ");

      Serial.println(cmd);

      ArduinoSlave.write(cmd);

    }

    //Send answer to monitor

    if (answer!=old_answer){

      Serial.print("Slave received : ");

      Serial.println(answer);

    }

}
