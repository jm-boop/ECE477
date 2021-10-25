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
	int seconds = 0;
	//FILE *ff;
	//char *token, str[15];
	//float value;

	/* Line is from Bruce Segee's original 'main()' func 
	 * from 'linux_dumb_terminal.c'
	 */
	fd1 = init();

	/* Set direction of all pins in DDRB register */
	write(fd1, "W 0x24 0xFF\n", 12);
	sleep(1);
	
	while(1) {
		//Blip for a new second. Blip is a 1khz tone 
		write(fd1, "W 0x25 0xFD\n", 12); //Toggle Speaker high for 1ms
		usleep(1000);
		write(fd1, "W 0x25 0xFF\n", 12); //Toggle Speaker low for 1ms
		usleep(1000);			
		//Increment second counter
		seconds++;
		//IF one minute has gone by, bleep a minute alarm
		if ((seconds % 60) == 0) {
			for (int i = 0; i < 30; i++) {
			write(fd1, "W 0x25 0xFD", 12);
			usleep(200);
			write(fd1, "W 0x25 0xFF", 12);
			usleep(200);
			}
		}
		//Wait one second (the remainder of one second)
		usleep(998600);
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
