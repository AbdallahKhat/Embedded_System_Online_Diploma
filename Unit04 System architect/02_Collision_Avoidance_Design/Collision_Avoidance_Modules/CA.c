/*
 * CA.c
 *
 *  Created on: Feb 4, 2023
 *      Author: abdal
 */

#include "CA.h"	//check if thats correct then delete comment

//Variables (Scope: only CA.c)

static int CA_speed = 0;
static int CA_distance = 0;
static int CA_threshold = 50;

//STATE pointer to function

extern void (*pfCA_state)();

//function definition

void US_Set_distance(int d)
{
	CA_distance = d ;
	(CA_distance <= CA_threshold)? (pfCA_state = STATE(CA_waiting)) : (pfCA_state = STATE(CA_driving));
	printf("US ------distance=%d------> CA\n",CA_distance);
}

STATE_define(CA_waiting)
{

	//State Name
	CA_state_id = CA_Waiting;
	printf("CA_Waiting state: distance = %d	 Speed = %d\n",CA_distance,CA_speed);

	//State Action
	CA_speed = 0;
	DC_Motor_Set(CA_speed);

	//Event Check
	//US_Get_distance(CA_distance);

}
STATE_define(CA_driving)
{

	//State Name
	CA_state_id = CA_Driving;
	printf("CA_driving state: distance = %d	 Speed = %d\n",CA_distance,CA_speed);

	//State Action
	CA_speed = 30;
	DC_Motor_Set(CA_speed);

	//Event Check
	//US_Get_distance(CA_distance);

}
