/*
 * DC.c
 *
 *  Created on: Feb 4, 2023
 *      Author: abdal
 */

#include "DC.h"	//check if thats correct then delete comment

//Variables (Scope: only DC.c)

static int DC_speed = 0;

//STATE pointer to function


extern void (*pfDC_state)();

//function definition

void DC_init()
{
	//init PWM
	printf("DC_init \n");
}

void DC_Motor_Set(int s)
{
	DC_speed = s;
	pfDC_state = STATE(DC_busy);
	printf("CA ------speed=%d------> DC\n",DC_speed);
}

STATE_define(DC_idle)
{

	//State Name
	DC_state_id = DC_idle;

	//State Action
	//Call PWM to make speed = DC_speed

	printf("DC_idle state: Speed = %d\n",DC_speed);

}
STATE_define(DC_busy)
{

	//State Name
	DC_state_id = DC_busy;

	//State Action
	//Call PWM to make speed = DC_speed

	printf("DC_busy state: Speed = %d\n",DC_speed);
	pfDC_state = STATE(DC_idle);
}
