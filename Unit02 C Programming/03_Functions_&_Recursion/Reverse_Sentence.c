/*
 * Reverse_Sentence.c
 *
 *  Created on: Sep 17, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>
#include <string.h>

//C Program to Reverse a Sentence Using Recursion

void reverse(char str[] , int i);

int main()
{
	char str[100];
	int length;

	printf("Enter a sentence: ");
	gets(str);

	length = strlen(str);

	reverse(str , length);

	return 0;
}

void reverse(char str[] , int i)
{
	if(i != 0)
	{
		printf("%c", str[i-1]);
		reverse(str , i-1);
	}
}
