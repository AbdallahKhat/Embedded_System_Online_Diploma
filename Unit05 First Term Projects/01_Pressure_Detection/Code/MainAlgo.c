/*
 * MainAlgo.c
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah Khater
 */

#include "MainAlgo.h"

//global ENUM Variable

enum NUMMainAlgo MainAlgo_state_id;

//Variables (Scope: only MainAlgo.c)

static int P_value = 0;
static int threshold = 20;

//STATE pointer to function

void (*pfMainAlgo_state)();

//function definition

void set_pressure_val(int Pval)
{
    //Set pressure value received from Pressure_Sensor_Driver
    P_value = Pval;

    //Set State pointer to high_Pressure_detect
    pfMainAlgo_state = STATE(high_Pressure_detect);

}

STATE_define(high_Pressure_detect)
{
    //State Name
    MainAlgo_state_id = MainAlgo_high_Pressure_detect;

    //State Action
    if(P_value > threshold)
    {
        Highpressure_detected();
    }
}



