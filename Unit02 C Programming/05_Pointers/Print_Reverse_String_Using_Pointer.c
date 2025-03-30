/*
 * main.c
 *
 *  Created on: sept 23, 2022
 *      Author: Abdallah
 */

#include <stdio.h>

/*Write a program in C to print a string in reverse using a pointer.*/

int main()
{
	char str[25];
	char* ptr;
	int i;

	printf("Printing a string in reverse order\n");
	printf("-----------------------------------\n");

	printf("Input a string: ");
	fflush(stdin); fflush(stdout);
	gets(str);

	ptr = str;

	/*assigning the pointer with the address of the '\0' in string*/

	for(i=0; i<25; i++)
	{
		ptr++;
		if(*ptr == '\0')
			break;
	}

	/*printf the string in reverse*/

	printf("Reverse of the string ins: ");

	do
	{
		ptr--;
		printf("%c",*ptr);
	}
	while(ptr!=str);


	return 0;
}
