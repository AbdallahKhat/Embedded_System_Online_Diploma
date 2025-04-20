/*
 * main.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Abdallah
 */

#include <stdio.h>

/*program in C to demonstrate how to handle the pointers
in the program.*/

int main()
{
	int m = 29;
	int* ab = &m;

	printf("ab is an int pointer and m is int = 29\n\n");

	printf("Address of m = 0x%x\n",&m);
	printf("Value of m = %d\n", m);

	printf("Now ab is assigned with the address of m.\n");

	printf("Address of pointer ab = 0x%x\n",ab);
	printf("Content of pointer ab = %d\n", *ab);

	m = 34;

	printf("The value of m assigned to %d now.\n",m);

	printf("Address of pointer ab = 0x%x\n",ab);
	printf("Content of pointer ab = %d\n", *ab);

	*ab = 7;

	printf("The pointer variable ab is assigned with the value %d now.\n",*ab);

	printf("Address of m = 0x%x\n",&m);
	printf("Value of m = %d\n", m);


	return 0;
}
