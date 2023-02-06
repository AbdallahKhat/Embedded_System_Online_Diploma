/*
 * state.h
 *
 *  Created on: Feb 4, 2023
 *      Author: abdal
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"

//Automatic state function generation

#define STATE_define(_StateFun_) void ST_##_StateFun_()
#define STATE(_StateFun_) ST_##_StateFun_

//States Connection
void US_Set_distance(int d);
void DC_Motor_Set(int s);

#endif /* STATE_H_ */
