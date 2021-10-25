#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "header.h"

int main(int argc, char *argv[])
{
	FILE *ff;
	char command[50] = "curl -s wttr.in/?format=j1";
	char data[46386]; 
	uint32_t i = 0;
	char c;
	char arg[30];

	printf("What field would you like to scan.\nFeild: ");// asking for using input
	scanf("%s",arg);                          // to choose what fields 
	strcat(arg,":");			  // they want to search
		
	// open JSON file  as read only 
	ff = popen(command, "r");
	/* error checking - popen() will return NULL if not able to open 
	 * file
	 */	
	if (ff == NULL) {
		printf("Error: can not open file\n");
	}		

	// execute until end of file, (until popen() returns 0 
	while(!feof(ff)) {
		// store each character of file in 'c' 
		c = fgetc(ff);
		
		// storing each non-extrenous character in array 
		if ((c != '[') && (c != ']') && (c != '{') && (c != '}') && (c != '"') && (c != ' ') && (c != '\n')) {
			data[i] = c;
			i++;
		}
	}

	phases(data,arg);
	

	return 0;
}
