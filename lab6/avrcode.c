#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <math.h>
#include <avr/sleep.h>
#include <string.h>

#define F_CPU 8000000UL
#include <util/delay.h>

//STDIO Functions
int serial_putchar(char, FILE *);
int serial_getchar(FILE *);
static FILE serial_stream = FDEV_SETUP_STREAM (serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void init_pwm(void);
void update_clock_speed(void);
void init_usart(unsigned int baud);
void init_ADC(void);
int read_ADC(void);

int serial_putchar(char value, FILE *);
int serial_getchar(FILE *);
//This code is distributed with no warranty expressed or implied.
//It does not contain any known bugs, but has not been tested.  
//What it is intended to do is use the first two bytes of eeprom
//as an offset and direction for adjusting the internal oscillator
//The first byte is an unsigned byte that is the amount to adjust 
//the OSCCAL register.  The next byte will be 0 or 1 depending on 
//whether the adjustment should be positive (0) or negative (1).
//The value 0xff is intentionally avoided to distinguish unprogrammed
//eeprom locations.

//main first calls update_clock_speed to make the adjustments to
//the oscillator calibration and then calls init_pwm to set up 
//a 100Hz 50% duty cycle square wave on OC1A (pin 15 on the 28 pin 
//DIP package).


int main()
{
  char buffer[100] = "Anything But Start";
  update_clock_speed();  //adjust OSCCAL
  init_pwm();     //set up hardware PWM
  init_usart(51);
  init_ADC();
  _delay_ms(1000);
int x = 0;
double voltage = 0;
while ((strncmp("Start", buffer, sizeof("Start"))) != 0) { //Wait until start string is recieved
	fgets(stdin, 100, buffer);
	}
while(1) {
	x = read_ADC();
	voltage = (double) x * 1.1; //Mutliply by reference
	voltage = voltage / 1023; //and divide by 1023 to get Vin

	fprintf(stdout, "Rail voltage is equal to: %lf V\n", voltage);
	_delay_ms(1000);
	}
}
//read the first two bytes of eeprom, if they have been programmed
//use the first byte as an offset for adjusting OSCCAL and the second as
//the direction to adjust 0=increase, 1=decrease.
//Any offset is allowed and users are cautioned that it is possible to
// adjust the oscillator beyond safe operating bounds.
void update_clock_speed(void)
{
  char temp;
  temp=eeprom_read_byte((void *)1); //read oscillator offset sign 
                                    //0 is positive 1 is  negative
                                    //erased reads as ff (so avoid that)
  if(temp==0||temp==1)      //if sign is invalid, don't change oscillator
  {
      if(temp==0)
	  {
	     temp=eeprom_read_byte((void *)0);
		 if(temp != 0xff) OSCCAL+=temp;
	  }
	  else
	  {
	     temp=eeprom_read_byte((void *)0);
		 if(temp!=0xff) OSCCAL -=temp;
	  }
  }
}


void init_pwm(void)
{
  // **************************************************************
  // ***   Timer 1                                                *
  // **************************************************************
  
  DDRB |= (1<<PB1);  //set OC1A as an output
  OCR1A=19999;    //set initial compare at 50%
  ICR1=39999U; // 8 MHz /40000/2 = PWM frequency = 100 Hz
  TCCR1A = (1<<COM1A1); //zeros in COM1B1,COM1B0,WGM11,WGM10  
  //internal clock, no prescaler , PWM mode 8
  TCCR1B = (1<<WGM13) | (1<<CS10);
}

void init_usart(unsigned int baud) 
{
	//Set baud rate
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char) baud; 
	UCSR0A = 0;
	//Enable reciever and transmitter
	UCSR0B = (1<<RXEN0) | (3<<TXEN0);

	//Set 8 data, 2 stop
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
	stdin = &serial_stream;
	stdout = &serial_stream;
}
void init_ADC()
{
	ADMUX = (3 << REFS0); // sets the mux for adc to recieve avcc
	ADCSRA = (1 << ADEN) | (6 << ADPS0); //Toggle ADC Enable bit to initialize the ADC
	ADCSRB = 0;
	DIDR0 = 0; //Advice from Bruce to enable digital input
}

int serial_putchar (char val, FILE *fp)
{
	while((UCSR0A & (1 << UDRE0)) == 0); //Wait for AVR register to empty, and signal it's ready
	UDR0 = val; //Sets the bit to the specified value
	return 0;
}

int serial_getchar (FILE *fp)
{
	while ((UCSR0A & (1 << RXC0)) == 0); //Wait for RPI to be ready for transfer
	return UDR0; //Transmits the data held in serial register

}
int read_ADC(void) 
{	
		ADCSRA |= (1 << ADSC);
		while ((ADCSRA & (1 << ADSC))); //Wait for ADC to finish conversion	
		return ADC;
}
