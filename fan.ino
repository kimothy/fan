#include <EEPROM.h>
const int led = 13;
/* to be removed */
const int rLed = 12;
const int yLed = 11;
const int b1 = 4;
const int b2 = 5;
/* end of remove */
boolean space = false;
boolean done = false;
String command = "";
String parameter = "";
int location[3] = {1,10,50};

void setup() {
	Serial.begin(9600);
	parameter.reserve(200);
	command.reserve(200);
	/* to be removed */
	pinMode(led,OUTPUT);
	pinMode(b1,INPUT);
	pinMode(b2,INPUT);
	pinMode(yLed,OUTPUT);
	pinMode(rLed,OUTPUT);
	/* end of remove */
	gsm_start();
	Serial.println("Ready");
}
/* checks for strings from serial port */
void serialEvent() {
	int mode;
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		if (space == false) {
			if (inChar != ' ') {
				/* before space saved to "command" string */
				command += inChar;
			}
			else {
				/* if space is detected then it marks the end of the command */
				space = true;
			}
		}
		else if (space == true) {
			/* if space = true, command is ended, save to "parameter" string */
			parameter += inChar;
		}
		delay(1);
	}
	/* checks to se if command is valid */
	mode = checkCommand();
	/* executed command based on mode set in "checkString" */
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
		Serial.println("Not a valid command");
		mode = 0;
	}
	return mode;
}
void executeCommand(int mode) {
	/* if "set.it" or "set.#" */
	if ((mode == 1)||(mode == 2)) {
		Serial.println(command);
		Serial.println(parameter);
		int length = parameter.length();
			EEPROM.write(location[mode],length);
			for (int i = 0; i < length; i++) {
				EEPROM.write(i+location[mode]+1,parameter[i]);
			}
		}
	/* if "start" */
	else if (mode == 3) {
	Serial.println(command);
	EEPROM.write(1,1);
	}
	/* if "stop" */
	else if (mode == 4) {
		Serial.println(command);
		EEPROM.write(1,0);
	}
	/* if status */
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
		Serial.print(readVcc(), DEC );
		Serial.println("mV");
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
	/* change wait time to 10 sec */
	wait(led,2,500);
	Serial.println("RUNNING");
}

/* to be removed */
int push(){	
	int mode;
	boolean b1s;
	boolean b2s;
	while ((b1s==LOW)||(b2s==LOW)) {
		delay(100);
		if ((b1s==LOW) && (b2s==HIGH)) {
			mode = 1;
		}
		else if ((b1s==HIGH) && (b2s==LOW)) {
			mode = 2;
		}
		else if ((b1s==LOW) && (b2s==LOW)) {
			mode = 3;
		}
		else {
			mode = 0;
		}
		b1s = digitalRead(b1);
		b2s = digitalRead(b2);
		delay(1);
	}
	delay(1);
	return mode;
}
long readVcc() {
	long result;
	// Read 1.1V reference against AVcc
	ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
	delay(2); // Wait for Vref to settle
	ADCSRA |= _BV(ADSC); // Convert
	while (bit_is_set(ADCSRA,ADSC));
	result = ADCL;
	result |= ADCH<<8;
	result = 1126400L / result; // Back-calculate AVcc in mV
	return result;
}
/* end of remove */
void loop() {
	/* to be remvoved */
	int mode = push();
	if (mode == 1) {
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
	digitalWrite(led,LOW);
	delay(100);
	digitalWrite(led,HIGH);
	/* end of remove */
}
