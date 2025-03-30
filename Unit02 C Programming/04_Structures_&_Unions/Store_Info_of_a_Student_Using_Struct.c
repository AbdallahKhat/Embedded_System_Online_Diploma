/*
 * main.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Abdallah
 */

#include "stdio.h"

/*C Program to store information(name, roll and marks) of a student using structure */

struct SStudent
{
	char name[50];
	int rollnum;
	float marks;
};

void main()
{
	struct SStudent x;

	printf("Enter information of student: \n");

	printf("Enter name: ");
	fflush(stdin); fflush(stdout);
	scanf("%s", x.name);


	printf("Enter roll number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &x.rollnum);


	printf("Enter marks: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &x.marks);

	printf("Displaying information \n");
	printf("Name: %s \n",x.name);
	printf("Roll: %d \n",x.rollnum);
	printf("Marks: %.1f \n",x.marks);

}
