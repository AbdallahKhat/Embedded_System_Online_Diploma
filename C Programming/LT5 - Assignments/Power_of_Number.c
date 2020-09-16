/*
 * Power_of_Number.c
 *
 *  Created on: Sep 17, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

//C Program to Calculate the Power of a Number Using Recursion

int powerinteger(int num1 , int num2);

int main()
{
	int n , power;

	printf("Enter base number: ");
	scanf("%d", &n);

	printf("Enter power number(positive integer): ");
	scanf("%d", &power);

	printf("%d^%d = %d", n , power , powerinteger(n , power));

	return 0;
}

int powerinteger(int num1 , int num2)
{
	if(num2 != 0)
		return num1 * powerinteger(num1 , num2-1);
	else
		return 1;
}

