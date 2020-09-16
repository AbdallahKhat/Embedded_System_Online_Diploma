/*
 * Prime_Check.c
 *
 *  Created on: Sep 16, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

//Prime Numbers Between two Intervals by Making User-defined Function

int checkprime(int num);

int main()
{
	int x , y, i , result;

	printf("Enter two numbers: ");
	fflush(stdout); fflush(stdin);
	scanf("%d %d",&x,&y);


	printf("\nPrime numbers between %d and %d are: ", x , y);

	for(i=x+1; i<y ; ++i){

		result = checkprime(i);
		if(result == 0)
			printf("%d ",i);

	}


	return 0;
}

int checkprime(int num)
{
	int result = 0, j;

	for(j=2; j<= num/2; ++j)
	{
		if(num%j == 0)
		{
			result = 1;
			break;
		}

	}
	return result;
}
