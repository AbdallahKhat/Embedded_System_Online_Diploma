/*
 * MainAlgo.h
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah Khater
 */

#ifndef MAINALGO_H_
#define MAINALGO_H_

#include "state.h"

//Define states
enum NUMMainAlgo{
    MainAlgo_high_Pressure_detect
};


//Declare states function for MainAlgo

STATE_define(high_Pressure_detect);

//State pointer to function
extern void (*pfMainAlgo_state)();

#endif /* MAINALGO_H_ */
