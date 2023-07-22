/*
 * state.h
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah Khater
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"
#include "driver.h"

//Automatic state function generation

#define STATE_define(_StateFun_) void ST_##_StateFun_()
#define STATE(_StateFun_) ST_##_StateFun_

//States Connection

void set_pressure_val(int Pval);
void Highpressure_detected();
void StartAlarm();
void StopAlarm();


#endif /* STATE_H_ */
