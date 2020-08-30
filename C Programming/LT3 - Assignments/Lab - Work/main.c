/*
 * main.c
 *
 *  Created on: Aug 22, 2020
 *      Author: Abdallah
 */


#include "stdio.h"

int main ()
{
	int i=0 , j=0;
	while(i<=9)
	{
		while(j<=9)
		{
			printf("%d ",j);
			j++;
		}
		printf(" \n");
		i++;
		j=i;
	}
	return 0;
}
