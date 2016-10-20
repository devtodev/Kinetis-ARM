/*
 * motor.c
 *
 *  Created on: 18/10/2016
 *      Author: Carlos Miguens
 */

#include "drivers/Ultrasonic.h"

int getDistanceFront()
{
	  uint16_t us, cm;
	  us = US_Measure_us();
	  cm = US_usToCentimeters(us, 22);
	  cm = (cm==0)?500:cm;
	  return cm;
}

int getDistanceBack()
{
}
