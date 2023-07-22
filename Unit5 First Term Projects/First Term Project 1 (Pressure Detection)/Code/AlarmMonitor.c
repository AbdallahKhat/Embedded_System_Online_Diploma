/*
 * AlarmMonitor.c
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah Khater
 */


#include "AlarmMonitor.h"

//global ENUM Variable

enum NUMMonitor AlarmMonitor_state_id;

//Variables (Scope: only AlarmMonitor.c)

static int alarm_period = 600000;

//STATE pointer to function

void (*pfAlarmMonitor_state)();

//function definition

void Highpressure_detected()
{
    //Set State pointer to AlarmMonitor_alarmON
    pfAlarmMonitor_state = STATE(AlarmMonitor_alarmON);
}

STATE_define(AlarmMonitor_alarmOFF)
{
    //State Name
    AlarmMonitor_state_id = Monitor_alarmOFF;

    //state action (do nothing)
}

STATE_define(AlarmMonitor_alarmON)
{
    //State Name
    AlarmMonitor_state_id = Monitor_alarmON;

    //state action
    //Start Alarm
    StartAlarm();

    //Set State pointer to AlarmMonitor_waiting
    pfAlarmMonitor_state = STATE(AlarmMonitor_waiting);
    pfAlarmMonitor_state();

}

STATE_define(AlarmMonitor_waiting)
{
    //State Name
    AlarmMonitor_state_id = Monitor_waiting;

    //state action
    //delay
    Delay(alarm_period);

    //Stop Alarm
    StopAlarm();

    //Set State pointer to AlarmMonitor_alarmOFF
    pfAlarmMonitor_state = STATE(AlarmMonitor_alarmOFF);

}
