/*
 * main.c
 *
 *  Created on: Aug 29, 2020
 *      Author: Abdallah Khater
 */


#include "stdio.h"

int main()
{
	int Num1 , Num2;
	printf("Enter two integers: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d", &Num1, &Num2);
	printf("Sum: %d", Num1 + Num2);
	return 0;

}
