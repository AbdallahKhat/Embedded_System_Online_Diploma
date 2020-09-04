/*
 * Sum_Of_Multidimensional_Arrays.c
 *
 *  Created on: Sep 4, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

/*program to find sum of two matrix of order 2*2 using multidimensional arrays
where, elements of matrix are entered by user.*/

int main()
{
	float mat1[2][2] , mat2[2][2] , matsum[2][2];
	int r , c;

	printf("Enter the elements of 1st matrix \n");

	for(r=0; r<2; r++)
	{
		for(c=0; c<2; c++)
		{
			printf("Enter a%d%d: ",r+1 ,c+1);
			fflush(stdin); fflush(stdout);
			scanf("%f",&mat1[r][c]);
		}
	}

	printf("Enter the elements of 2nd matrix \n");

	for(r=0; r<2; r++)
	{
		for(c=0; c<2; c++)
		{
			printf("Enter b%d%d: ",r+1 ,c+1);
			fflush(stdin); fflush(stdout);
			scanf("%f",&mat2[r][c]);
		}
	}

	for(r=0; r<2; r++)
	{
		for(c=0; c<2; c++)
		{
			matsum[r][c] = mat1[r][c] + mat2[r][c];
		}
	}

	printf("Sum of the matrices: \n");
	for(r=0; r<2; r++)
	{
		for(c=0; c<2; c++)
		{
			printf("%.1f\t", matsum[r][c]);
		}
		printf("\n");
	}
	return 0;

}
