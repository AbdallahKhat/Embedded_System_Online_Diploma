/*
 * main.c
 *
 *  Created on: Aug 29, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

int main()
{
	float a , b , c;

	printf("Enter value of a: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &a);
	printf("Enter value of b: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &b);
	c = a;
	a = b;
	b = c;

	printf("\nAfter swapping, value of a = %f", a);
	printf("\nAfter swapping, value of b = %f", b);
	return 0;
}
