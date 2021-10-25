#ifndef LED_H
#define LED_H

//defines for gpio pins we are using based on wiringPi value
#define HIGH 1
#define LOW 0
#define LED1 8 //GPIO 2
#define LED2 9 //GPIO 3
#define LED3 7 //GPIO 4
#define LED4 31 //GPIO 1 
#define LED5 30 //GPIO 0
#define LED6 21 //GPIO 5
#define LED7 22 //GPIO 6
#define LED8 11 //GPIO 7

void blink_leds(int x);

void pi_usage(float value);
	
void double_strobe();

void string_clear(char stirng[]);

void on_off(int one, int two, int three, int four, int five, int six, int seven ,int eight);


#endif
