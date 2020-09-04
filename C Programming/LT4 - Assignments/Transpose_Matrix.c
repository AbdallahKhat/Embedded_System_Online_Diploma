/*
 * Transpose_Matrix.c
 *
 *  Created on: Sep 4, 2020
 *      Author: Abdallah Khater
 */


#include <stdio.h>

/* This program asks user to enter a matrix (size of matrix is specified by user)
and this program finds the transpose of that matrix and displays it. */

int main()
{
	int mat[10][10], trans[10][10], r, c, rn, cn;

	printf("Enter rows and columns of matrix: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d", &rn, &cn);

	for(r=0; r<rn; r++)
	{
		for(c=0; c<cn; c++)
		{
			printf("Enter element a%d%d: ", r+1, c+1);
			fflush(stdin); fflush(stdout);
			scanf("%d",&mat[r][c]);
		}
	}

	printf("Entered Matrix: \n");

	for(r=0; r<rn; r++)
	{
		for(c=0; c<cn; c++)
		{
			printf("%d\t",mat[r][c]);
		}
		printf("\n\n");
	}

	for(r=0; r<rn; r++)
	{
		for(c=0; c<cn; c++)
		{
			trans[c][r] = mat[r][c];
		}
	}

	printf("Transpose of Matrix: \n");

	for(r=0; r<cn; r++)
	{
		for(c=0; c<rn; c++)
		{
			printf("%d\t",trans[r][c]);
		}
		printf("\n\n");
	}
	return 0;
}
