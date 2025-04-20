/*
 * main.c
 *
 *  Created on: jul 22, 2022
 *      Author: Abdallah Khater
 */


#include <stdio.h>

int main()
{
	int num,i,fact=1;

	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);

	if(num<0)
		printf("\nError!!! Factorial of negative numbers do not exist.");
	else
	{
		for(i=1;i<=num;i++)
			fact*=i;
		printf("\nFactorial = %d",fact);
	}



	return 0;

}
