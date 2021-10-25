#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "led.h"
//PRE: LEDS not lit. POST: LEDS lit from each end of breadboard torwards center, then back again
void double_strobe ()
{
	int x;
	int runtime;
	int i = 0;
	int iteration = 0;
	
	//Initialize WiringPi
	wiringPiSetup();	
	//Allocate each LED in WiringPi
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);
	pinMode(LED5,OUTPUT);
	pinMode(LED6,OUTPUT);
	pinMode(LED7,OUTPUT);
	pinMode(LED8,OUTPUT);

	printf ("Enter delay time for double-ended strobe, and the time you would like this to run!: ");
	scanf ("%d %d", &x, &runtime);

	while (iteration < runtime) {
	  	
		//Toggles LED's from each end of line torwards the middle
		digitalWrite(30, HIGH);
		digitalWrite(11, HIGH);
		delay(x);
		digitalWrite(30, LOW);
		digitalWrite(11, LOW);
		digitalWrite(31, HIGH);
		digitalWrite(22, HIGH);
		delay(x);
		digitalWrite(31, LOW);
		digitalWrite(22, LOW);
		digitalWrite(8, HIGH);
		digitalWrite(21, HIGH);
		delay(x);
		digitalWrite(8, LOW);
		digitalWrite(21,LOW);
		digitalWrite(9, HIGH);
		digitalWrite(7, HIGH);
		delay(x);
		digitalWrite(9, LOW);
		digitalWrite(7, LOW);
		digitalWrite(9, HIGH);
		digitalWrite(7, HIGH);
		delay(x);
		
		//TOGGLES LEDs back the other direction to each end
		
		digitalWrite(9, HIGH);
		digitalWrite(7, HIGH);
		delay(x);
		digitalWrite(9, LOW);
		digitalWrite(7, LOW);
		digitalWrite(8, HIGH);
		digitalWrite(21, HIGH);
		delay(x);
		digitalWrite(8, LOW);
		digitalWrite(21, LOW);
		digitalWrite(31, HIGH);
		digitalWrite(22, HIGH);
		delay(x);
		digitalWrite(31, LOW);
		digitalWrite(22, LOW);
		digitalWrite(30, HIGH);
		digitalWrite(11, HIGH);
		delay(x);
		digitalWrite(30, LOW);
		digitalWrite(11, LOW);
      		
		//Check variable for counting repeats
    		iteration++;
	}
}
