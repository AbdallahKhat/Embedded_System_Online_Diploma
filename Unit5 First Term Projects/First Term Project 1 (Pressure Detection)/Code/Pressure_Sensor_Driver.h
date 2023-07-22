/*
 * Pressure_Sensor_Driver.h
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah Khater
 */

#ifndef PRESSURE_SENSOR_DRIVER_H_
#define PRESSURE_SENSOR_DRIVER_H_

#include "state.h"

//Define states
enum NUMPsensor{
    Psensor_reading,
    Psensor_waiting
};

//Declare states functions for Pressure Sensor

STATE_define(Psensor_reading);
STATE_define(Psensor_waiting);

void Psensor_init();

//State pointer to function
extern void (*pfPsensor_state)();

#endif /* PRESSURE_SENSOR_DRIVER_H_ */
