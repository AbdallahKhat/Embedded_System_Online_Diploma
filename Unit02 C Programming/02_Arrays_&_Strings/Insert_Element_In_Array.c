/*
 * Insert_Element_In_Array.c
 *
 *  Created on: Sep 4, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

//C program to insert an element in an array

int main()
{
	int a[30], num, i, element, loc;
	printf("Enter no of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num);

	for(i=0; i<num ; i++)
	{
		a[i] = i+1;
		printf("%d ",a[i]);
	}

	printf("\nEnter the element to be inserted: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &element);

	printf("Enter the location: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &loc);

	for(i=num; i>=loc ; i--)
		a[i] = a[i-1];
	num++;

	a[loc-1] = element;
	for(i=0; i<num; i++)
		printf("%d ",a[i]);

	return 0;
}
