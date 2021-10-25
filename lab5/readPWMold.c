#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int initVal;
	int next_state = 0;
	int get_new_start = 1;
	/* Initializations for using "clock_gettime()" func. to measure signal freq.  */	
	struct timespec start, finish;
	double period = 0;

	/* Initialize wiringPi pin numbering scheme and set GPIO 27 (2) as input. */
	wiringPiSetup();
	pinMode(2,INPUT);
	
	/* Grab the initial value of incoming signal (0 or 1) */
	initVal = digitalRead(2);
	
	while(1) {
		/* Start timer immediately */
		if (get_new_start == 1) {
			clock_gettime(CLOCK_REALTIME, &start);
			get_new_start = 0;
		}
		/* Conditional for when on a falling or rising edge */
		if (initVal != digitalRead(2)) {
			next_state = 1;
		}
		/* If back at initial value (meaning one period gone by), stop timer */ 
		if ((initVal == digitalRead(2)) && (next_state == 1)){
			clock_gettime(CLOCK_REALTIME, &finish);
		}
		if (finish.tv_nsec != 0) {
			/* Cast period time to double and scale to seconds. */ 
			period = ((double)((finish.tv_nsec - start.tv_nsec)));
			period = period / 1000000000;
			/* Negate negative period nuance by adding one second */ 
			if (period < 0) {
				period += 1;
			}
			else {
				period = period;
			}
			/* Print resulting period and frequency of EVERY period of signal */
			printf("Period = %lf\n", period);
			printf("Frequency = %lf\n", 1/period);
			printf("\n\n");
			/* Reset values for next iteration */
			get_new_start = 1;
			next_state = 0;
			finish.tv_nsec = 0;
		}
	}
return 0;
}
