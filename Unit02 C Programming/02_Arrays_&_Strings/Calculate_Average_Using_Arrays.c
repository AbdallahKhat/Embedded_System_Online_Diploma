/*
 * Calculate_Average_Using_Arrays.c
 *
 *  Created on: Jul 23, 2022
 *      Author: Abdallah Khater
 */


#include <stdio.h>

/*This program takes n number of element from user(where, n is specified by user),
stores data in an array and calculates the average of those numbers.*/

int main()
{
	float sum,average, arr[100];
	int num,i;

	printf("Enter the number of data: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);

	while (num>100 || num<=0)
	{
		printf("Number should be in range of 1 to 100.\n");
		printf("Insert a new number");
		fflush(stdin); fflush(stdout);
		scanf("%d",&num);
	}

	for(i=0,sum=0;i<num;i++)
	{
		printf("%d. Enter number: ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%f",&arr[i]);
		sum += arr[i];
	}
	average = sum/i;

	printf("Average = %.2f",average);

	return 0;

}
