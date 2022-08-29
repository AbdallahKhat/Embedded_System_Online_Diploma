/*
 * main.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Abdallah
 */

#include "stdio.h"
#define PI 3.145
#define area(r) (PI*(r)*(r))

/*C program to find area of circle, passing arguments to macros */

int main()
{
	int radius;
	float area;

	printf("Enter radius: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&radius);

	area=area(radius);

	printf("Area=%.2f",area);

	return 0;
}

