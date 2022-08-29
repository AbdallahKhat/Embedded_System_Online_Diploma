/*
 * main.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Abdallah
 */

#include "stdio.h"

/*C program to add two complex numbers by passing structure to a function */

struct SComplex
{
	float real;
	float imag;
};

struct SComplex addition(struct SComplex n1, struct SComplex n2);

int main(void)
{
	struct SComplex num1,num2,sum;
	printf("for 1st complex number \n");

	printf("Enter real and imaginary respectivly: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &num1.real,&num1.imag);


	printf("for 2nd complex number \n");

	printf("Enter real and imaginary respectivly: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &num2.real,&num2.imag);

	sum = addition(num1,num2);

	printf("sum=%.1f+%.1fi",sum.real,sum.imag);

}

struct SComplex addition(struct SComplex n1, struct SComplex n2)
{
	struct SComplex add;
	add.real = n1.real+n2.real;
	add.imag = n1.imag+n2.imag;
	return add;
}
