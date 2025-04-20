/*
 * main.c
 *
 *  Created on: jul 22, 2022
 *      Author: Abdallah Khater
 */


#include <stdio.h>

int main()
{
	char op;
	float a,b;

	printf("Enter an operator, either (+) or (-) or (*) or( /): ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&op);

	printf("Enter two operands: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&a,&b);

	switch(op)
	{
	case '+':
		printf("\n%.2f + %.2f = %.2f",a,b,a+b);
		break;
	case '-':
		printf("\n%.2f - %.2f = %.2f",a,b,a-b);
		break;
	case '*':
		printf("\n%.2f * %.2f = %f.2",a,b,a*b);
		break;
	case '/':
		printf("\n%.2f / %.2f = %.2f",a,b,a/b);
		break;
	default:
		printf("\nError! incorrect operator.");
	}

	return 0;

}
