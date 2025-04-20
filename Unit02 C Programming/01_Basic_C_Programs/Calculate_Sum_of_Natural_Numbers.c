/*
 * main.c
 *
 *  Created on: jul 22, 2022
 *      Author: Abdallah Khater
 */


#include <stdio.h>

int main()
{
	int num,sum,count;

		printf("Enter a positive integer: ");
		fflush(stdin); fflush(stdout);
		scanf("%d",&num);

		for(sum=0,count=1 ; count<=num ; ++count)
			sum+=count;

		printf("\nSum = %d",sum);

		return 0;

}
