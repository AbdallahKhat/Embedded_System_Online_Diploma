/*
 * main.c
 *
 *  Created on: Aug 29, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

int main()
{
	float a , b;

	printf("Enter value of a: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &a);
	printf("Enter value of b: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &b);

	// Write your code to swap the content of the two variables without a temp variable
	a = a + b; // 5 + 10 =15
	b = a - b; // 15 - 10 = 5
	a = a - b; // 15 - 5 = 10

	printf("\nAfter swapping, value of a = %f", a);
	printf("\nAfter swapping, value of b = %f", b);
	return 0;
}

/*
//Another method for swapping 2 numbers w/o temp, using XOR
int main()
{
	int n1=1,n2=2;

	n1^=n2; //bitwise 0001 xor 0010 = 0011 (3)
	n2^=n1; //        0010 xor 0011 = 0001 (1)
	n1^=n2; //        0011 xor 0001 = 0010 (2)

	printf("%d %d",n1,n2);

	return 0;
}
*/
