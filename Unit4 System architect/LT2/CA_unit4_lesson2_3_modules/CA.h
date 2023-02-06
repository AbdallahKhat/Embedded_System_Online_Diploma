/*
 * CA.h
 *
 *  Created on: Feb 4, 2023
 *      Author: abdal
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"

//Define states
enum {
	CA_Waiting,
	CA_Driving
}CA_state_id;

//Declare states function CA

STATE_define(CA_waiting);
STATE_define(CA_driving);

//State pointer to function
void (*pfCA_state)();

#endif /* CA_H_ */
