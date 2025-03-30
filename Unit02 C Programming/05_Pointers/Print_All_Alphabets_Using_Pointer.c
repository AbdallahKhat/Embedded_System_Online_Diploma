/*
 * main.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Abdallah
 */

#include <stdio.h>

/*Write a program in C to print all the alphabets using a pointer.*/

int main()
{
	char alpha[26];
	char* ptr;
	int i;

	ptr = alpha;

	/*Assigning the ASCII code of the alphabets to the addresses
	of the string by pointer*/

	for(i=0;i<26;i++)
	{
		*ptr = 'A' + i;
		ptr++;
	}

	/*Printing the alphabets*/

	ptr = alpha;

	for(i=0;i<26;i++)
	{
		printf("%c  ",*ptr);
		ptr++;
	}

	return 0;
}
