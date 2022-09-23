/*
 * main.c
 *
 *  Created on: Sept 23, 2022
 *      Author: Abdallah
 */

#include <stdio.h>

/*Write a program in C to print the elements of an array in reverse
order.*/

int main()
{
	int arr[15],count,i;
	int* arptr;

	printf("Printing elements of array in reverse order\n");
	printf("-------------------------------------------\n");

	printf("Input the number of elements to store in the array (max 15): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&count);

	/*Inserting the values of the elements*/

	printf("Input %d number of elements in the array :\n",count);

	for(i=0; i<count ; i++)
	{
		printf("element - %d : ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%d",&arr[i]);
	}

	/*Assigning pointer to address of last input element of array*/

	arptr = arr + count-1;

	/*Printing the array in reverse order*/

	printf("The elements of array in reverse order are :\n");

	for(i=count; i>0 ; i--)
	{
		printf("element - %d : %d\n",i,*arptr);
		arptr--;
	}

	return 0;
}
