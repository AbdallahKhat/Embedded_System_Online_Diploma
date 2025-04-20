/*
 * main.c
 *
 *  Created on: jul 22, 2022
 *      Author: Abdallah Khater
 */


#include <stdio.h>

int main()
{
	char c;

	printf("Enter an alphabet: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);

	if(c=='a'||c=='i'||c=='o'||c=='u'||c=='A'||c=='I'||c=='O'||c=='U')
		printf("\n%c is a vowel",c);
	else
		printf("\n%c is a Consonant",c);


	return 0;

}
