/*
 * main.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Abdallah
 */

#include "stdio.h"

/*c program to store information of students using structure */

struct SStudent
{
	char name[50];
	int roll;
	float marks;
};

void main()
{
	struct SStudent s[10];
	int i;

	printf("Enter information of student\n");

	for(i=0;i<10;i++)
	{
		s[i].roll=i+1;
		printf("For roll number %d\n",s[i].roll);
		printf("Enter name:");
		fflush(stdin); fflush(stdout);
		scanf("%s",s[i].name);
		printf("Enter marks: ");
		fflush(stdin); fflush(stdout);
		scanf("%f",&s[i].marks);
	}

	printf("Displaying informations of students:\n");

	for(i=0;i<10;i++)
	{
		printf("information for roll number %d\n", s[i].roll);
		printf("Name: %s\n", s[i].name);
		printf("Marks: %.1f\n", s[i].marks);

	}


}

