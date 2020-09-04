/*
 * Reverse_String.c
 *
 *  Created on: Sep 5, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>
#include <string.h>

/* Program to Reverse String Without Using Library Function.
You can only use library function strlen(), To find the length of the string. */

int main()
{
	char str[1000], temp;
	int i = 0 , j;

	printf("Enter the string : ");
	fflush(stdin); fflush(stdout);
	gets(str);

	j = strlen(str) - 1;

	while(i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}

	printf("Reverse sting is : %s", str);

	return 0;
}
