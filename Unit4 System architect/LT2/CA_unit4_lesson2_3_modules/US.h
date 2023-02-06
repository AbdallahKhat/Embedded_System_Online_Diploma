/*
 * US.h
 *
 *  Created on: Feb 4, 2023
 *      Author: abdal
 */

#ifndef US_H_
#define US_H_

#include "state.h"

//Define USates
enum {
	US_busy
}US_state_id;

//Declare USates function US

STATE_define(US_busy);

void US_init();

//USate pointer to function
void (*pfUS_state)();

#endif /* US_H_ */
