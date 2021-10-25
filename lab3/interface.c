#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include "led.h"


void blink_leds(int x)
{
//	int i;

	wiringPiSetup();	

	//setting the gpio locations to outputs
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);
	pinMode(LED5,OUTPUT);
	pinMode(LED6,OUTPUT);
	pinMode(LED7,OUTPUT);
	pinMode(LED8,OUTPUT);

	//turning on and off leds, LEDs numbers are based on the location on bread board
	digitalWrite(LED1,HIGH); delay(x); 
	digitalWrite(LED1,LOW); delay(x);	
	digitalWrite(LED2,HIGH); delay(x);
	digitalWrite(LED2,LOW); delay(x);	
	digitalWrite(LED3,HIGH); delay(x);
	digitalWrite(LED3,LOW); delay(x);	
	digitalWrite(LED4,HIGH); delay(x);
	digitalWrite(LED4,LOW); delay(x);	
	digitalWrite(LED5,HIGH); delay(x);
	digitalWrite(LED5,LOW); delay(x);	
	digitalWrite(LED6,HIGH); delay(x);
	digitalWrite(LED6,LOW); delay(x);	
	digitalWrite(LED7,HIGH); delay(x);
	digitalWrite(LED7,LOW); delay(x);	
	digitalWrite(LED8,HIGH); delay(x);
	digitalWrite(LED8,LOW); delay(x);
 
}

void on_off(int one, int two, int three, int four, int five, int six, int seven ,int eight)
{
	wiringPiSetup();
	
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);
	pinMode(LED5,OUTPUT);
	pinMode(LED6,OUTPUT);
	pinMode(LED7,OUTPUT);
	pinMode(LED8,OUTPUT);
	
	digitalWrite(LED1,one); 
	digitalWrite(LED2,two); 
	digitalWrite(LED3,three);
	digitalWrite(LED4,four);
	digitalWrite(LED5,five);;
	digitalWrite(LED6,six); 
	digitalWrite(LED7,seven); 
	digitalWrite(LED8,eight); 


}

void pi_usage(float value)
{
	wiringPiSetup(); //for use of wiringPi

	//if value greater than 4 turn on all LEDs
	if (value > 4) {
		digitalWrite(LED1,HIGH);
		digitalWrite(LED2,HIGH);
		digitalWrite(LED3,HIGH);
		digitalWrite(LED4,HIGH);
		digitalWrite(LED5,HIGH);
		digitalWrite(LED6,HIGH);
		digitalWrite(LED7,HIGH);
		digitalWrite(LED8,HIGH);
	}
	
	//if value is between 2 and 4 turn on but most sig. LEE
	if (value >= 2 && value <= 4) {
		digitalWrite(LED1,HIGH);
		digitalWrite(LED2,HIGH);
		digitalWrite(LED3,HIGH);
		digitalWrite(LED4,HIGH);
		digitalWrite(LED5,HIGH);
		digitalWrite(LED6,HIGH);
		digitalWrite(LED7,HIGH);
		digitalWrite(LED8,LOW);
	}
	
	//if value is between 1 and 2 turn all but 2 most sig. LEDs
	if (value >= 1 && value <=2) {
		digitalWrite(LED1,HIGH);
		digitalWrite(LED2,HIGH);
		digitalWrite(LED3,HIGH);
		digitalWrite(LED4,HIGH);
		digitalWrite(LED5,HIGH);
		digitalWrite(LED6,HIGH);
		digitalWrite(LED7,LOW);
		digitalWrite(LED8,LOW);
	}

	if (value < 1) {
		blink_leds(15);

	}



}
