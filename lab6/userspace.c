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
	int count = 0;
	//Data buffer for later
	char data[100];
	int fdserial = 0;
	//Get our serial file to setup comm between AVR and RPI
	fdserial = init_serial_user();
	double voltage = 0;
	//Create file stream for input and output, as well as where to store voltages
	FILE *usart_in;
	FILE *usart_out;
	FILE *data_out;
	int from_string = 0;
	usart_in = fdopen(fdserial, "r");
	usart_out = fdopen(fdserial, "w");
	if (usart_in == NULL || usart_out == NULL) {
		printf("Error opening file(s).\n");
		return 0;
	}
	fprintf(usart_out, "Start\n");
	while (count < 10) {
		data_out = fopen("rail_voltages.dat", "r+");
		if (data_out == NULL) {
			printf("Error Opening File.\n");
			return -1;
		}
		fgets(data, 100, usart_in);
		fprintf(data_out, "%s\n", data);
		count++;
		printf("%d\n", count);
		fclose(data_out);
	}
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
	tc.c_cflag = (CS8 | CREAD | CLOCAL);
	tc.c_lflag = ICANON; // Always set, unless whatever is being done REQUIRES this not to be
	
	//Set the baud 
	cfsetispeed(&tc, B9600); //Input Baud rate
	cfsetospeed(&tc, B9600); //Output Baud rate

	tcsetattr(fd, TCSANOW, &tc);
	printf("We get this far\n");	
	return fd;
}
