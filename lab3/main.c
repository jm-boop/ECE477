#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <unistd.h>
#include <time.h>
#include "led.h"

int main(int argc, char *argv[])
{
//	int delay_value;
	FILE *ff;
	char *token, str[15];
	float value;
	int x;
	srand((int)time(NULL));

//	double_strobe();
	
	while (1) {
		//Reading value from /proc/loadavg
		ff = fopen("/proc/loadavg","r");
		fgets(str,15,ff); //get line in file
		token = strtok(str," "); //first value is seperate by space from others
		value = atof(token); //changing from string to float of first value
		pi_usage(value); //pass to function that minipulates LEDs based on that value
	//	printf("%.3f\n",value); //print value for user to see
		fclose(ff); //close file so we dont go to the next value that is seperated by a space, just repoen in loop
		sleep(2); //sleep for 2 seconds
	}

/*	while (1) {
		x = (rand() % 50 + 1);
		blink_leds(x);
		on_off(1,0,0,0,0,0,0,1);
		delay(50);
		on_off(0,1,0,0,0,0,1,0);
		delay(50);
		on_off(0,0,1,0,0,1,0,0);
		delay(50);
		on_off(0,0,0,1,1,0,0,0);
		delay(50);
		on_off(1,1,1,1,1,1,1,1);
		delay(50);
		on_off(0,0,0,0,0,0,0,0);
		delay(500);*/
//	}
	
		


	return 0;
}
