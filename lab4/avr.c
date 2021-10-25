#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "avr.h"

int main(int argc, char *argv[])
{
	int fd1;
	FILE *ff;
	char *token, str[15];
	float value;

	/* Line is from Bruce Segee's original 'main()' func 
	 * from 'linux_dumb_terminal.c'
	 */
	fd1 = init();

	/* Set direction of all pins in DDRB register */
	write(fd1, "W 0x24 0xFF\n", 12);
	sleep(1);
	
	while(1) {
		/* Traverse to and read from 'loadavg' file  */
		ff = fopen("/proc/loadavg", "r");
		/* Grab first line of 'loadavg' file and store in 'str' */
		fgets(str, 15, ff);
		/* Grab the load value (first value) of first line and 
	         * convert to form str to float
  		 */
		token = strtok(str, " ");
		value = atof(token);

		/* Print val for user to see */
		printf("%.3f\n", value);
		
		/* Conditionals on val for LED pattern */
		if (value < 1.0) {
			condition1(fd1);
		} else if ((value >= 1.0) && (value < 2.0)) {
			condition2(fd1);
		} else if ((value >= 2.0) && (value < 4.0)) {
			condition3(fd1);
		} else if (value >= 4.0) {
			condition4(fd1);
		}
		
		fclose(ff);
		sleep(1);
   	}
	return 0;
 }



/* NOTE: this function is not modified - taken directly from Bruce Segee */
  int  init()
  {
    int fd1;
    struct termios tc;                // terminal control structure

    //todo serial port should not be hard coded
    fd1 = open("/dev/ttyACM0", O_RDWR|O_NOCTTY);  // really ought to check for error
    if(fd1 == -1) {
	printf("Error");
    }
    tcgetattr(fd1, &tc);
    tc.c_iflag = IGNPAR;
    tc.c_oflag = 0;
    tc.c_cflag = CS8 | CREAD | CLOCAL; //8 bit chars enable receiver no modem status lines
    tc.c_lflag =0 ;

    //todo baud rate should not be hard coded
    cfsetispeed(&tc, B9600);
    cfsetospeed(&tc, B9600);
    //todo should have bits per character set
    tcsetattr(fd1, TCSANOW, &tc);
  return fd1;
 }



void condition1(int fd1)
{	
	/* Blink LED connected to PB0 */
	write(fd1, "W 0x25 0xFE\n", 12); usleep(15000);
	write(fd1, "W 0x25 0xFF\n", 12); usleep(15000);
	/* " " " " PB1 */
	write(fd1, "W 0x25 0xFD\n", 12); usleep(15000);
	write(fd1, "W 0x25 0xFF\n", 12); usleep(15000);
	/* " " " " PB2 */
	write(fd1, "W 0x25 0xFB\n", 12); usleep(15000);
	write(fd1, "W 0x25 0xFF\n", 12); usleep(15000);
	/* " " " " PB3 */
	write(fd1, "W 0x25 0xF7\n", 12); usleep(15000);
	write(fd1, "W 0x25 0xFF\n", 12); usleep(15000);
	/* " " " " PB4 */
	write(fd1, "W 0x25 0xEF\n", 12); usleep(15000);
	write(fd1, "W 0x25 0xFF\n", 12); usleep(15000);
	/* " " " " PB5 */
	write(fd1, "W 0x25 0xDF\n", 12); usleep(15000);
	write(fd1, "W 0x25 0xFF\n", 12); usleep(15000);
	/* " " " " PB6 */
	write(fd1, "W 0x25 0xBF\n", 12); usleep(15000);
	write(fd1, "W 0x25 0xFF\n", 12); usleep(15000);
	/* " " " " PB7 */
	write(fd1, "W 0x25 0x7F\n", 12); usleep(15000);
	write(fd1, "W 0x25 0xFF\n", 12); usleep(15000);
}



void condition2(int fd1)
{
	/* Light all but the two most sig LEDs */
	write(fd1, "W 0x25 0xC0\n", 12); usleep(15000);
}



void condition3(int fd1)
{
	/* Light all but the most sig LED */
	write(fd1, "W 0x25 0x80\n", 12); usleep(15000);
}



void condition4(int fd1)
{	
	/* Light all LEDs */
	write(fd1, "W 0x25 0x00\n", 12); usleep(15000);
}
