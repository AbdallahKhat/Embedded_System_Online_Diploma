/*
 * main.c
 *
 *  Created on: Sept 23, 2022
 *      Author: Abdallah
 */

#include <stdio.h>

/*Write a program in C to show a pointer to an array which contents
are pointer to structure. */

struct SEmployees
{
	char *name;
	int id;
};

int main()
{
struct SEmployees emp1={"Marc",1001},emp2 ={"Alex",1002},emp3 ={"Noah",1003};
struct SEmployees *arr[3] = {&emp1,&emp2,&emp3};
struct SEmployees *(*p)[3]= &arr;

/*Printing the info of employee using complex pointer*/

printf("Employee name is %s\n", (**(*p+1)).name);
printf("Employee id is %d\n",(*(*p+1))->id);



	return 0;
}
