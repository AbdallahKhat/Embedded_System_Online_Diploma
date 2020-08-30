/*
 * main.c
 *
 *  Created on: Aug 29, 2020
 *      Author: Abdallah Khater
 */


#include "Stdio.h"

int main()
{

	float Num1 , Num2;
	printf("Enter two numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &Num1, &Num2);
	printf("Product: %f", Num1 * Num2);
	return 0;
}
