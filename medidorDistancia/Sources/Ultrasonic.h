/*
 * Ultrasonic.h
 *
 *  Created on: Dec 30, 2012
 *      Author: Erich Styger
 *      	    Carlos Miguens
 *      Driver for two US100 and FRDM-KL25Z board
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "PE_LDD.h"

/* 
 * \brief Called in case of an overflow during input capture. This function is called from an interrupt!
 * \param UserDataPtr Pointer to user structure
 */
void US_Front_EventEchoOverflow(LDD_TUserData *UserDataPtr);
void US_Back_EventEchoOverflow(LDD_TUserData *UserDataPtr);

/*
 * \brief Called by the input capture interrupt for a raising or falling edge of the Echo pin
 * \param UserDataPtr Pointer to user structure
 */
void US_Front_EventEchoCapture(LDD_TUserData *UserDataPtr);
void US_Back_EventEchoCapture(LDD_TUserData *UserDataPtr);

/* 
 * \brief Convert measured microseconds to centimeters.
 * \param[in] temperatureCelsius Air temperature in degree Celsius
 */
uint16_t US_usToCentimeters(uint16_t microseconds, uint8_t temperatureCelsius);

uint16_t US_Front_Measure_us(void);
uint16_t US_Back_Measure_us(void);

/*
 * \brief Driver initialization routine.
 */
void US_Init(void);


#endif /* ULTRASONIC_H_ */
