#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "header.h"

void phases(char data[], char arg[])
{

	char temp[100];
	uint32_t i = 0, k = 0, j = 0;
	int value;	
		
	// iterate through each character in 'data' array
	while (i < strlen(data)) {
		// segregate data by commas and store into temp array
		if (data[i] != ',') {
			temp[k] = data[i]; 
			k++;
		} else{
			/* when reach comma in data, reset iterator and clear 
			 * temp array
			 */
			k=0;
			memset(temp, 0, 50);
		}
		
		/* further segregate data by colons, then check if string is 
		 * equivalent to "moon_phases"
		 */
		if (data[i] == ':') {
			value = strcmp(temp, arg);
                        /* if equivalent, print phase of the moon to standard 
			 * output    
			 */
			if (value == 0) {
				for (j=0; j < strlen(temp); j++) {
					printf("%c", temp[j]);
				}

				i++;	

				while (data[i] != ',') {
					printf("%c", data[i]);
					i++;
				}
		
				printf("\n");
			}
		}	
		i++;
	}
}
