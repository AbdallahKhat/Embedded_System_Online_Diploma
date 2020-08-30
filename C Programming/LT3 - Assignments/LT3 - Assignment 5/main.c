/*
 * main.c
 *
 *  Created on: Aug 29, 2020
 *      Author: Abdallah Khater
 */


#include "stdio.h"

int main()
{

	char i;

	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &i);
	printf("ASCII value of G = %d", i);
	return 0;
}
