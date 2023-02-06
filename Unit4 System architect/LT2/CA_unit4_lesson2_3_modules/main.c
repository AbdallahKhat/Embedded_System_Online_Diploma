/*
 * main.c
 *
 *  Created on: Feb 4, 2023
 *      Author: abdal
 */

#include "CA.h"
#include "US.h"
#include "DC.h"

void setup()
{
	//init all drivers
	//înit IRQ ....
	//init HAL US_Driver DC_Motor
	//init BLOCK
	US_init();
	DC_init();
	//Set States pointer for each Block
	pfCA_state = STATE(CA_waiting);
	pfDC_state = STATE(DC_idle);
	pfUS_state = STATE(US_busy);

}

int main()
{
	volatile int delay;

	setup();

	while(1)
	{
		//call state for each block
		pfUS_state();
		pfCA_state();
		pfDC_state();
		//delay
		for(delay=0;delay <= 1000 ; delay++);
	}
	return 0;
}
