/*
 * DC.h
 *
 *  Created on: Feb 4, 2023
 *      Author: abdal
 */

#ifndef DC_H_
#define DC_H_

#include "state.h"

//Define states
enum {
	DC_idle,
	DC_busy
}DC_state_id;

//Declare states function DC

STATE_define(DC_idle);
STATE_define(DC_busy);

void DC_init();

//State pointer to function
void (*pfDC_state)();

#endif /* DC_H_ */
