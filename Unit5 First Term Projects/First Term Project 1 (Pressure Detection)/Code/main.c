/*
 *  main.c
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah Khater
 */

#include <stdint.h>
#include <stdio.h>

#include "driver.h"
#include "MainAlgo.h"
#include "AlarmMonitor.h"
#include "Pressure_Sensor_Driver.h"
#include "Alarm_Actuator_Driver.h"

void setup()
{
    //init all drivers
    //înit IRQ ....
    //init HAL Pressure_Sensor_Driver Alarm_Actuator_Driver
    Psensor_init();
    Alarm_actuator_init();


    //Set States pointer for each Block
    pfPsensor_state = STATE(Psensor_reading);
    pfMainAlgo_state = NULL;    /* expected to be set to state high_Pressure_detect after */
    /* set_pressure_val() function is called from Pressure_Sensor_Driver */
    pfAlarmMonitor_state = STATE(AlarmMonitor_alarmOFF);
    pfAlarm_actuator_state = STATE(Alarm_actuator_waiting);

}

int main (){

    GPIO_INITIALIZATION();

    setup();

    StopAlarm();


    while (1)
    {
        pfPsensor_state();
        pfMainAlgo_state();
        pfAlarmMonitor_state();
        pfAlarm_actuator_state();
    }

}
