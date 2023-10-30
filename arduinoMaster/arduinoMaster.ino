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
bool estadoled = 0;
int val_luz = 0;
const int LDR = A0;
int valButton;

void setup(){
  Serial.begin(9600);
  ArduinoSlave.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
}

 

void loop(){
  int val_luz = analogRead(LDR); // Recebe o valor do LDR
  luzStr = String(val_luz); // Transforma o valor lido do LDR em uma string
  Serial.print("Valor de luz: ");
  Serial.println(val_luz);
  valButton = digitalRead(buttonPin);

  if (valButton == LOW){ // Se o botão não foi pressionado
    butStr = 'L';
  } else{ // Se foi pressionado
    Serial.println("Botão HIGH");
    butStr = 'H';
  }
  msg = butStr + '*' + luzStr + ']'; // Concatena os textos do estado do botão e do valor do LDR separados po *

  // Ler a resposta do arduino escravo
  readSlavePort();
  // Imprime a mensagem do escravo
  if (answer!=""){
    Serial.print("Slave answer: ");
    Serial.println(answer);
    answer = ""; // Após imprimir a mensagem limpa ela
  }
  //  Manda a mensagem para o escravo
  Serial.print("Master sent : ");
  Serial.println(msg);
  ArduinoSlave.print(msg);
  //ArduinoSlave.write(val_luz);
  old_msg = msg;
  delay(1500);
}

void readSlavePort(){ // Ler a porta do escravo
  if (ArduinoSlave.available() > 0){ // Ver se a mensagem está disponível
    while(true){ // Enquanto a mensagem não chegar ao caractere final que é o [ recebe a mensagem
      char c = ArduinoSlave.read();
      if(c == ']' || c == -1){
        break;
      } else {
        answer += c;
    }
   } 
  }
}
