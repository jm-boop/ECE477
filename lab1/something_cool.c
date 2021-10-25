#include <stdio.h>

void color(void)
{
	int i, color = 31;
	
	// print in color 'sizeof(int)' number of times
	for (i = 1; i <= sizeof(int); i++) { 
		// changing color each iteration
		printf("\033[1;4;%dm", color);
		printf("Hello World!\n");

		color++;

		// 'color' can only by 31 - 38
		if (color > 38) {
		       color = 31;
		}	       		
	}
	printf("\n");
}
