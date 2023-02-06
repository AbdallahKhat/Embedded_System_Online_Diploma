/*
 * US.c
 *
 *  Created on: Feb 4, 2023
 *      Author: abdal
 */

#include "US.h"	//check if thats correct then delete comment

//Variables (Scope: only US.c)

static int US_distance = 0;

//STATE pointer to function


extern void (*pfUS_state)();

int US_Get_distance_random(int l,int r,int count);

//function definition

void US_init()
{
	//init US Driver
	printf("US init\n");
}

STATE_define(US_busy)
{

	//State Name
	US_state_id = US_busy;

	//State Action
	US_distance = US_Get_distance_random(45,55,1);

	printf("US_busy state: distance = %d\n",US_distance);

	US_Set_distance(US_distance);
	pfUS_state = STATE(US_busy);
}

int US_Get_distance_random(int l,int r,int count)
{
	//random number generation in range l and r
	int i,rand_num;
	for(i=0;i<count;i++)
	{
		rand_num =(rand() % (r - l +1));
		rand_num += l;
		return rand_num;
	}
	return 0;
}
