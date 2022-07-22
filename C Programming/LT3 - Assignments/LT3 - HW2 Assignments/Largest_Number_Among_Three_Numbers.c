/*
 * main.c
 *
 *  Created on: jul 22, 2022
 *      Author: Abdallah Khater
 */


#include <stdio.h>

int main()
{
	float num1,num2,num3;

	printf("Enter three numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f",&num1,&num2,&num3);

	if(num1 >= num2)
	{
		if(num1 >= num3)
			printf("Largest number = %.3f",num1);
		else
			printf("Largest number = %.3f",num3);
	}

	else
	{
		if(num2 >= num3)
			printf("Largest number = %.3f",num2);
		else
			printf("Largest number = %.3f",num3);
	}

	return 0;

}
