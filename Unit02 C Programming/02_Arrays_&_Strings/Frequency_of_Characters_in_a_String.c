/*
 * Frequency_of_Characters_in_a_String.c
 *
 *  Created on: Sep 4, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>
#include <string.h>

/* This program asks user to enter a string and a character and this program
checks how many times that character is repeated in the string entered by user. */

int main()
{
	char a[1000], c;
	int freq = 0, i;

	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(a);

	printf("Enter a character to find frequency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &c);

	for(i=0 ; i<strlen(a) ; i++)
	{
		if(c == a[i])
			freq++;
	}

	printf("Frequency of %c = %d", c , freq);

	return 0;
}
