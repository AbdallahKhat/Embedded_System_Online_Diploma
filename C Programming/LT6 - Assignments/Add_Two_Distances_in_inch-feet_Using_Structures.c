/*
 * main.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Abdallah
 */

#include "stdio.h"

/*C Program to add two distances (int inch-feet) system using structure */

struct SDistance
{
	int feet;
	float inch;
}d1,d2,dsum;

void main()
{

	printf("Enter information for 1st distance \n");

	printf("Enter feet: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &d1.feet);


	printf("Enter inch: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &d1.inch);

	printf("Enter information for 2nd distance \n");

	printf("Enter feet: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &d2.feet);


	printf("Enter inch: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &d2.inch);

	dsum.feet = d1.feet + d2.feet;
	dsum.inch = d1.inch + d2.inch;

	/*Changing from inch to feet */

	if(dsum.inch > 12.0)
	{
		dsum.inch += -12;
		dsum.feet++;
	}

	printf("Sum of distances = %d\'-%.2f\"", dsum.feet,dsum.inch);

}
