#include <stdio.h>
#include <ctype.h>
#include "cool.h"

int main(int argc, char *argv[])
{
	int i, k;
	char string;

	printf("Print 'Hello world!' the number of times corresponding to the size of type int:\n");
	for (i = 1; i <= sizeof(int); i++) {
		printf("Hello world!\n");
	}
	printf("type int is %d bytes = %d bits\n", sizeof(int), sizeof(int)*8);

	printf("\nPrint 'Hello world!' the number of times corresponding to the size of type long:\n"); 	
	for (k = 1; k <= sizeof(long); k++) {
		printf("Hello world!\n");
	}
	printf("type long is %d bytes = %d bits\n\n", sizeof(long), sizeof(long)*8);

	printf("To print in color press Y: ");
	scanf("%c", &string);
	string = toupper(string);

	// something cool!
	if (string == 'Y') {
		color();
	}	

	return 0;
}
