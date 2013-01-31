#include <EEPROM.h>
const int led = 13;
const int rLed = 12;									// to be removed
const int yLed = 11;									// to be removed

const int b1 = 4;											// to be removed
const int b2 = 5;											// to be removed
boolean space = false;
boolean done = false;
String command = "";
String parameter = "";
int location[3] = {1,10,50};

void setup() {
  Serial.begin(9600);
  parameter.reserve(200);
  command.reserve(200);
  pinMode(led,OUTPUT);
	pinMode(b1,INPUT);									// to be removed
  pinMode(b2,INPUT);									// to be removed
  pinMode(yLed,OUTPUT);								// to be removed
  pinMode(rLed,OUTPUT);								// to be removed
  gsm_start();
  Serial.println("Ready");
}

 void serialEvent() {
   int mode;
   while (Serial.available()) {
     char inChar = (char)Serial.read();
     if (space == false) {
       if (inChar != ' ') {
         command += inChar;
       }
        else {
          space = true;
        }
      }
       else if (space == true) {
        parameter += inChar;
      }
      delay(1);
    }
   mode = checkCommand();
   executeCommand (mode);
   delay(1);
 }
 int checkCommand() {
   int mode;
   if (command == "set.id") {
     mode = 1;
   }
   else if (command == "set.#") {
     mode = 2;
   }
   else if (command == "start") {
     mode = 3;
   }
   else if (command == "stop") {
     mode = 4;
   }
   else if (command == "status") {
     mode = 5;
   }
   else {
     mode = 0;
   }
   return mode;
 }
 void executeCommand(int mode) {
   if ((mode == 1)||(mode == 2)) {
     Serial.println(command);
     Serial.println(parameter);
     int length = parameter.length();
     EEPROM.write(location[mode],length);
     for (int i = 0; i < length; i++) {
       EEPROM.write(i+location[mode]+1,parameter[i]);
     }
   }
   else if (mode == 3) {
     Serial.println(command);
     EEPROM.write(1,1);
   }
   else if (mode == 4) {
     Serial.println(command);
     EEPROM.write(1,0);
   }
   else if (mode == 5) {
     int stopped = EEPROM.read(1);
     if (stopped != 0) {
       Serial.println("RUNNING");
     }
     else {
       Serial.println("STOPED");
     }
     for (int i = 0; i < 2; i++) {
       int length = EEPROM.read(location[i+1]);
       for (int j = 0; j < length; j++) {
         Serial.print((char)EEPROM.read(j+location[i+1]+1));
         delay(1);
       }
       Serial.print("\n");
     }
   }
   delay(100);
   mode = 0;
   command = "";
   parameter = ""; 
   space = false; 
   delay(1);
}

void wait(int pin, int cycles, int period){
  for (int i=0; i<cycles; i++){
    digitalWrite(led,HIGH);
    delay(period/2);
    digitalWrite(led,LOW);
    delay(period/2);
  }
}
void gsm_start(){
  Serial.print("Starting GSM... ");
  wait(led,2,500);														//change wait time to 10 sec
  Serial.println("RUNNING");
}

int push(){																		// to be removed. complete function!
  int mode;
  boolean b1s;
  boolean b2s;
  while ((b1s==LOW)||(b2s==LOW))
  {
    delay(100);
    if ((b1s==LOW) && (b2s==HIGH))
    {
     mode = 1;
    }
    else if ((b1s==HIGH) && (b2s==LOW))
    {
      mode = 2;
    }
    else if ((b1s==LOW) && (b2s==LOW))
    {
      mode = 3;
    }
    else
    {
      mode = 0;
    }
    b1s = digitalRead(b1);
    b2s = digitalRead(b2);
    delay(1);
  }
  delay(1);
  return mode;
}


void loop() {
  int mode = push();
  if (mode == 1) {									// if statement to be replaced by actual program
    digitalWrite(yLed,HIGH);
    delay(250);
    digitalWrite(yLed,LOW);
  }
  else if (mode == 2) {
    digitalWrite(rLed,HIGH);
    delay(250);
    digitalWrite(rLed,LOW);
  }
  else if (mode == 3) {
    digitalWrite(yLed,HIGH);
    digitalWrite(rLed,HIGH);
    delay(250);
    digitalWrite(yLed,LOW);
    digitalWrite(rLed,LOW);
  }
  mode = 0;
  digitalWrite(led,LOW);						// to be removed
  delay(100);
  digitalWrite(led,HIGH);
}
