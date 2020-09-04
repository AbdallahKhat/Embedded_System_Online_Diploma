/*
 * Calculate_Average_Using_Arrays.c
 *
 *  Created on: Sep 4, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

/*This program takes n number of element from user(where, n is specified by user),
stores data in an array and calculates the average of those numbers.*/

int main()
{
	float num[100], sum, average;
	int i=0 ,n;

	printf("Enter the number of data: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	while(i<n)
	{
		printf("1. Enter number: ");
		fflush(stdin); fflush(stdout);
		scanf("%f",&num[i]);
		i++;

	}

	for(i=0; i<n; i++)
		sum += num[i];


	average = sum/n;

	printf("Average = %.2f", average);

	return 0;
}
