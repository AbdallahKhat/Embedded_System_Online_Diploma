/*
 * Alarm_Actuator_Driver.c
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah Khater
 */


#include "Alarm_Actuator_Driver.h"

//global ENUM Variable

enum NUMAlarm_Act Alarm_actuator_state_id;

//STATE pointer to function

void (*pfAlarm_actuator_state)();

//function definition

void Alarm_actuator_init()
{
    //init Alarm actuator
}

void StopAlarm()
{
    //Set State pointer to Alarm_actuator_AlarmOFF
    pfAlarm_actuator_state = STATE(Alarm_actuator_AlarmOFF);
    pfAlarm_actuator_state();
}

void StartAlarm()
{
    //Set State pointer to Alarm_actuator_AlarmON
    pfAlarm_actuator_state = STATE(Alarm_actuator_AlarmON);
    pfAlarm_actuator_state();
}

STATE_define(Alarm_actuator_waiting)
{
    //State Name
    Alarm_actuator_state_id = Alarm_actuator_waiting;

    //state action (do nothing)
}

STATE_define(Alarm_actuator_AlarmOFF)
{
    //State Name
    Alarm_actuator_state_id = Alarm_actuator_AlarmOFF;

    //state action
    //Turn off alarm
    Set_Alarm_actuator(0);

    //Set State pointer to Alarm_actuator_waiting
    pfAlarm_actuator_state = STATE(Alarm_actuator_waiting);
}

STATE_define(Alarm_actuator_AlarmON)
{
    //State Name
    Alarm_actuator_state_id = Alarm_actuator_AlarmON;

    //state action
    //Turn on alarm
    Set_Alarm_actuator(1);

    //Set State pointer to Alarm_actuator_waiting
    pfAlarm_actuator_state = STATE(Alarm_actuator_waiting);
}


