/*
 * Search_Element_In_Array.c
 *
 *  Created on: Sep 4, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

// C Program to Search an element in Array

int main()
{
	int arr[30], num, i, element;
	printf("Enter no of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num);

	for(i=0; i<num ; i++){
		arr[i] = (i+1)*11;
		printf("%d ", arr[i]);
	}

	printf("\nEnter the element to be searched: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &element);

	for(i=0 ; i<num ; i++){
		if(element == arr[i]){
			printf("Number found at location: %d", i+1);
			break;
		}
		else if(i+1 == num){
			printf("Number not found");
		}
	}


	return 0;
}
