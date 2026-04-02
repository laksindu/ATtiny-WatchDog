#include <SoftwareSerial.h>

int rxPin = 0;

int LED = 2;
int RST = 1;

SoftwareSerial mySerial(rxPin,-1);

void setup(){
  pinMode(rxPin,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  pinMode(RST,OUTPUT);

  mySerial.begin(9600);

}
void loop(){  

  for(int i = 0 ; i <= 60 ; i++){

    if(mySerial.available() > 0){

      while(mySerial.available() > 0){
        mySerial.read();
      }

      digitalWrite(LED,HIGH);
      delay(500);
      digitalWrite(LED,LOW);

      i = 0;
    }

  delay(1000);

    if(i >= 59){
      digitalWrite(RST, HIGH);
      delay(1000);
      digitalWrite(RST,LOW);
      LED_P();
    }

  }


}

void LED_P(){

    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
}
