/*
 * Alarm_Actuator_Driver.h
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah Khater
 */

#ifndef ALARM_ACTUATOR_DRIVER_H_
#define ALARM_ACTUATOR_DRIVER_H_

#include "state.h"

//Define states
enum NUMAlarm_Act {
    Alarm_actuator_AlarmOFF,
    Alarm_actuator_AlarmON,
    Alarm_actuator_waiting
};

//Declare states functions for Pressure Sensor

STATE_define(Alarm_actuator_waiting);
STATE_define(Alarm_actuator_AlarmOFF);
STATE_define(Alarm_actuator_AlarmON);


void Alarm_actuator_init();

//State pointer to function
extern void (*pfAlarm_actuator_state)();

#endif /* ALARM_ACTUATOR_DRIVER_H_ */
