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
	
	//String to hold users name!
	char username[20];

	//Flag for if username is correct or not
	char selection[1];

	//Distance between two transcievers
	int distance = 0;

	int fdserial = 0;
	//Get our serial file to setup comm between AVR and RPI
	fdserial = init_serial_user();
	double voltage = 0;
	//Create file stream for input and output, as well as where to store voltages
	FILE *usart_in;
	FILE *usart_out;
	FILE *data_out;
	int from_string = 0;
	
	//Open serial port nodes for reading and writing to AVR
	usart_in = fdopen(fdserial, "r");
	usart_out = fdopen(fdserial, "w");
	
	//If files cannot be opened
	if (usart_in == NULL || usart_out == NULL) {
		printf("Error opening file(s).\n");
		return 0;
	}
	
	//Start ADC
	fprintf(usart_out, "Start\n");

	//Grab username
	printf("Please enter your user identification: ");
	scanf("%c", &username);
	printf("You entered %s as your user ID. IS this correct? Type (Y)es or (N)o");
	//Grab selection
	scanf("%c", selection);
	
	//If the username entered is not confirmed with Y or N, kick them out
	if ((strcmp(selection, "Y") != 0) || (strcmp(selection, "N")) != 0) {
		printf("Error, invalid character entered.\n");
		return 0;
	}
	//If the user specifies Y, move on in program
	if ((strcmp(selection, "Y")) == 0) {
		printf("Okay! Proceeding with %s ID\n", username);
	}
	//If the user entered N, kick them out but differently 
	else  {
		printf("Please return to main screen and renter your valid username\n");
	}

	//For 10 loops, tell me the bandgap voltage
	while (count < 10) {

		//Take a string from the AVR
		fgets(data, 100, usart_in);
		//Convert buffer to integer
		distance = atoi(data);

		//If the infared transiever and reciever are close enough, open the door
		if (distance > 100) {
			printf("Door closed\n");
		}
		else {
			printf("Door opened, Welcome %s\n");
		}	
		count++;
		//Print the count to confirm 10 lines of data are in the code
		printf("%d\n", count);
		//Close the output file
		fclose(data_out);
	}

	//Cleanup and close all serial nodes used in program
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
