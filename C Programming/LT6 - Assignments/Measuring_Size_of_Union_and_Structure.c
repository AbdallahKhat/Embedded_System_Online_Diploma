/*
 * main.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Abdallah
 */

#include "stdio.h"

/*Measuring the size of a struct and a union */

union job
{
	char name[32];
	float salary;
	int worker_no;
}u;

struct job1
{
	char name[32];
	float salary;
	int worker_no;
}s;

int main()
{
	printf("Size of union= %d ",sizeof(u));
	printf("\nSize of structure= %d ",sizeof(s));

	return 0;
}

