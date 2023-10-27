#include <SoftwareSerial.h>

#define ledPin 12
SoftwareSerial ArduinoMaster(10,11);

String msg="";
String but="", luz=""; 

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
  if (luz != "" || luz != " "){
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

void readMasterPort(){ // Função para ler a porta serial
  if (ArduinoMaster.available() > 0){
    msg = "";
    while (true){ // Loop infinito
      char c = ArduinoMaster.read();
      if(c == ']'){
        break;
      } else {
        msg += c;
      }
    }
    ArduinoMaster.flush(); // Limpa o buffer da porta serial 'ArduinoMaster'.

    int asteriscoIndex = msg.indexOf('*'); // Encontra a posição do caractere '*' na string 'msg' e armazena em 'asteriscoIndex'.
    but = msg.substring(0, asteriscoIndex); // Extrai uma subtring da 'msg' do início até 'asteriscoIndex' e armazena em 'but'.
    luz = msg.substring(asteriscoIndex + 1); // Extrai uma subtring da 'msg' a partir de 'asteriscoIndex + 1' até o final e armazena em 'luz'.
  }
}
