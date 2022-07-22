/*
 * main.c
 *
 *  Created on: jul 22, 2022
 *      Author: Abdallah Khater
 */


#include <stdio.h>

int main()
{
	int Num;

	printf("Enter an ingeter you want to check: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&Num);

	if(Num%2==0)
		printf("\n%d is even.",Num);
	else
		printf("\n%d is odd.",Num);

	return 0;

}
