#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

//int serial_putchar(char, FILE *);
//int serial_getchar(FILE *):
//static FILE serial_stream = FDEV_SETUP_STREAM (serial_putchar, serial_getchar, _FDEV_SETUP_RW);
int init_serial_user();

int main (int argc, char *argv[]) 
{	
	if (argc != 2) {
		return -1;
	}
	//Sample Count
	int samples = atoi(argv[1]);
	
	printf("Sample count = %d\n", samples);

	//Integer counter for seconds
	int seconds = 0;
	//Integer counter for minutes
		
	double total = 0;
	double decimal = 0;
	double average = 0;
	int results = 0;
	
	//Data buffer for later
	char data[100];
	int fdserial = 0;
	
	//Get our serial file to setup comm between AVR and RPI
	fdserial = init_serial_user();
	
	//Create file stream for input and output, as well as where to store voltages
	FILE *usart_in;
	FILE *usart_out;
	FILE *data_out;
	int from_string = 0;
	
	usart_in = fdopen(fdserial, "r");
	usart_out = fdopen(fdserial, "w");
	data_out = fopen("rail_temps.dat", "a");
	if (usart_in == NULL || usart_out == NULL || data_out == NULL) {
		printf("Error opening file(s).\n");
		return 0;
	}
	for (int iter = 0; iter < samples; iter++) {
	for (int i = 0; i < 32; i++) {

	fgets(data, 100, usart_in);	
		
	//Do appropriate equation for voltage
	results = atoi(data);
	printf("%d, raw \n", results);
	//results = results - 273;
	decimal = (double)(results * 0.83) - 273;

	total += decimal;
		}
	
	average = total / 32;
	average = average;

	fprintf(data_out, "%lf\n", average);
	total = 0;
	average = 0;
	decimal = 0;

	}


	fclose(data_out);
	fclose(usart_in);
	fclose(usart_out);
	return 0;
}
		
int init_serial_user()
{
	int fd;
	struct termios tc;

	//Step 1, open hardware serial (NOT USB) in dev
	fd = open ("/dev/serial0", O_RDWR | O_NOCTTY);

	if (fd <= 0) {
		printf("Serial port inexistent or failed to open.\n");
		return -1;
	}
	//Setup Termios
	tcgetattr(fd, &tc);
	
	//Set the flags
	tc.c_iflag = IGNPAR;
	tc.c_oflag = 0;
	tc.c_cflag = CS8 | CREAD | CLOCAL;
	tc.c_lflag = ICANON; // Always set, unless whatever is being done REQUIRES this not to be
	
	//Set the baud 
	cfsetispeed(&tc, B9600); //Input Baud rate
	cfsetospeed(&tc, B9600); //Output Baud rate

	tcsetattr(fd, TCSANOW, &tc);
	return fd;
}
