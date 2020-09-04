/*
 * Length_of_String.c
 *
 *  Created on: Sep 5, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

// this program computes the length of a string manually without using strlen() funtion.

int main()
{
	char a[1000];
	int len = 0, i;

	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(a);

	for(i=0 ; a[i]!='\0' ; i++)
		len++;

	printf("Length of string: %d", len);

	return 0;
}
