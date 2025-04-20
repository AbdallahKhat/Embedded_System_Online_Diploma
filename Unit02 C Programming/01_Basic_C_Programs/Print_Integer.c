/*
 * main.c
 *
 *  Created on: Aug 29, 2020
 *      Author: Abdallah Khater
 */


#include "stdio.h"

int main()
{

	int Num;
	printf("Enter a integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&Num);
	printf("\nYOu've entered: %d", Num);

	return 0;
}
