/*
 * Factorial_Recursion.c
 *
 *  Created on: Sep 16, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

//C program to Calculate Factorial of a Number Using Recursion

int calcfact(int num);

int main()
{
	int n;

	printf("Enter an integer number: ");
	scanf("%d",&n);


	printf("\nFactorial of %d = %d", n , calcfact(n));


	return 0;
}

int calcfact(int num)
{
	if(num != 1)
		return num*calcfact(num-1);
	else
		return num;
}
