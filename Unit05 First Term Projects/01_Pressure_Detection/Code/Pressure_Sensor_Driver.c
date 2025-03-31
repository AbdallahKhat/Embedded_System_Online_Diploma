/*
 * Pressure_Sensor_Driver.c
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah Khater
 */

#include "Pressure_Sensor_Driver.h"

//global ENUM Variable

enum NUMPsensor Psensor_state_id;

//Variables (Scope: only Pressure_Sensor_Driver.c)

static int Pressure_value = 0;

//STATE pointer to function

void (*pfPsensor_state)();

//function definition

void Psensor_init()
{
    //init Pressure sensor
}

STATE_define(Psensor_reading)
{
    //State Name
    Psensor_state_id = Psensor_reading;

    //State Action
    //get pressure value from sensor
    Pressure_value = getPressureVal();

    //send pressure value received to MainAlgo
    set_pressure_val(Pressure_value);

    //Set State pointer to Psensor_waiting
    pfPsensor_state = STATE(Psensor_waiting);
}

STATE_define(Psensor_waiting)
{
    //State Name
    Psensor_state_id = Psensor_waiting;

    //state action
    //delay
    Delay(100000);

    //Set State pointer to Psensor_reading
    pfPsensor_state = STATE(Psensor_reading);
    pfPsensor_state();
}

