#include <EEPROM.h>
const int led = 13;
const int b1 = 6;
const int b2 = 7;
int incomingByte = 0;

void wait(int pin, int cycles, int period){
  for (int i=0; i<cycles; i++){
    digitalWrite(led,HIGH);
    delay(period/2);
    digitalWrite(led,LOW);
    delay(period/2);
  }
}
void gsm_start(){
  /* start gsm */
  wait(led,2,500);
  Serial.print("GSM Activated\n");
}
void gsm_send(){
  /* Swichcase which defines what kind of message should be sendt */
}
void gsm_check(){
  /* checks for messages */
}
void LOG(){
  /* writes to log */
}
void listen(){
  /* checks for signal from alarm */
}
void initial(){
  /* default setup */
}

int push(){
  int b1s, b2s;
  int mode;
  while ((b1s==HIGH)||(b2s==HIGH))
  {
    delay(100);
    if ((b1s==HIGH) && (b2s==LOW))
    {
      mode = 1;
    }
    else if ((b1s==LOW) && (b2s==HIGH))
    {
      mode = 2;
    }
    else if ((b1s==HIGH) && (b2s==HIGH))
    {
      mode = 3;
    }
    else
    {
      mode = 0;
    }
    b1s = digitalRead(b1);
    b2s = digitalRead(b2);
  }
    return mode;
}
    
void setup(){
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  gsm_start();
}
void loop(){
  int mode = push();
  Serial.print("In the right place");
    incomingByte = Serial.read();
    Serial.println(incomingByte, DEC);
  
  switch(mode)
  {
  case 1:
    Serial.print("Check messages\n");
    break;
  case 2:
    Serial.print("Activate alarm\n");
    break;
  case 3:
    Serial.print("Reset defaut settings\n");
    break;
  default:
    Serial.print("Waiting\n");
    break;
  }
  delay(1);
}
  


