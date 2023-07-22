/*
 * AlarmMonitor.h
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah Khater
 */

#ifndef ALARMMONITOR_H_
#define ALARMMONITOR_H_

#include "state.h"

//Define states
enum NUMMonitor{
    Monitor_alarmOFF,
    Monitor_alarmON,
    Monitor_waiting
};

//Declare states functions for Pressure Sensor

STATE_define(AlarmMonitor_alarmOFF);
STATE_define(AlarmMonitor_alarmON);
STATE_define(AlarmMonitor_waiting);

//State pointer to function
extern void (*pfAlarmMonitor_state)();


#endif /* ALARMMONITOR_H_ */
