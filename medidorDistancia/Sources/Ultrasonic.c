/*
 * Ultrasonic.c
 *
 *  Created on: Dec 30, 2012
 *  Changed on: Oct 19, 2016
 *      Author: Erich Styger
 *      		Carlos Miguens
 *
 *      Driver for two US100 and FRDM-KL25Z board
 */

#include "Ultrasonic.h"
#include "TU_US_back.h"
#include "TU_US_front.h"
#include "WAIT1.h"

typedef enum {
  ECHO_IDLE, /* device not used */
  ECHO_TRIGGERED, /* started trigger pulse */
  ECHO_MEASURE, /* measuring echo pulse */
  ECHO_OVERFLOW, /* measurement too too long */
  ECHO_FINISHED /* measurement finished */
} US_EchoState;

typedef struct {
  LDD_TDeviceData *trigDevice; /* device handle for the Trigger pin */
  LDD_TDeviceData *echoDevice; /* input capture device handle (echo pin) */
  volatile US_EchoState state; /* state */
  TU_US_front_TValueType capture; /* input capture value */
} US_Front_DeviceType;


typedef struct {
  LDD_TDeviceData *trigDevice; /* device handle for the Trigger pin */
  LDD_TDeviceData *echoDevice; /* input capture device handle (echo pin) */
  volatile US_EchoState state; /* state */
  TU_US_back_TValueType capture; /* input capture value */
} US_Back_DeviceType;

static US_Front_DeviceType usDeviceFront;
static US_Back_DeviceType usDeviceBack; /* devices handle for the ultrasonics device */


void US_Front_EventEchoOverflow(LDD_TUserData *UserDataPtr) {
	US_Front_DeviceType *ptr = (US_Front_DeviceType*)UserDataPtr;
  
  ptr->state = ECHO_OVERFLOW;
}

void US_Back_EventEchoOverflow(LDD_TUserData *UserDataPtr) {
	US_Back_DeviceType *ptr = (US_Back_DeviceType*)UserDataPtr;

  ptr->state = ECHO_OVERFLOW;
}


void US_Front_EventEchoCapture(LDD_TUserData *UserDataPtr) {
	US_Front_DeviceType *ptr = (US_Front_DeviceType*)UserDataPtr;

  if (ptr->state==ECHO_TRIGGERED) { /* 1st edge, this is the raising edge, start measurement */
    TU_US_front_ResetCounter(ptr->echoDevice);
    ptr->state = ECHO_MEASURE;
  } else if (ptr->state==ECHO_MEASURE) { /* 2nd edge, this is the falling edge: use measurement */
    (void)TU_US_front_GetCaptureValue(ptr->echoDevice, 0, &ptr->capture);
    ptr->state = ECHO_FINISHED;
  }
}

void US_Back_EventEchoCapture(LDD_TUserData *UserDataPtr) {
	US_Back_DeviceType *ptr = (US_Back_DeviceType*)UserDataPtr;

  if (ptr->state==ECHO_TRIGGERED) { /* 1st edge, this is the raising edge, start measurement */
    TU_US_back_ResetCounter(ptr->echoDevice);
    ptr->state = ECHO_MEASURE;
  } else if (ptr->state==ECHO_MEASURE) { /* 2nd edge, this is the falling edge: use measurement */
    (void)TU_US_back_GetCaptureValue(ptr->echoDevice, 0, &ptr->capture);
    ptr->state = ECHO_FINISHED;
  }
}

static uint16_t calcAirspeed_dms(uint8_t temperatureCelsius) {
  /* Return the airspeed depending on the temperature, in deci-meter per second */
  unsigned int airspeed; /* decimeters per second */

  airspeed = 3313 + (6 * temperatureCelsius); /* dry air, 0% humidity, see http://en.wikipedia.org/wiki/Speed_of_sound */
  airspeed -= (airspeed/100)*15; /* factor in ~15% for a relative humidity of ~40% */ 
  return airspeed;
}

uint16_t US_usToCentimeters(uint16_t microseconds, uint8_t temperatureCelsius) {
  return (microseconds*100UL)/calcAirspeed_dms(temperatureCelsius)/2; /* 2 because because of two way */
}

/* measure and return the microseconds */
uint16_t US_Back_Measure_us(void) {
  uint16_t us;
  
  /* send 10us pulse on TRIG line. */
  TRIG_US_Back_SetVal(usDeviceBack.trigDevice);
  WAIT1_Waitus(10);
  usDeviceBack.state = ECHO_TRIGGERED;
  TRIG_US_Back_ClrVal(usDeviceBack.trigDevice);
  while(usDeviceBack.state!=ECHO_FINISHED) {
    /* measure echo pulse */
    if (usDeviceBack.state==ECHO_OVERFLOW) { /* measurement took too long? */
      usDeviceBack.state = ECHO_IDLE;
      return 0; /* no echo, error case */
    }
  }
  us = (usDeviceBack.capture*1000UL)/(TU_US_back_CNT_INP_FREQ_U_0/1000);
  return us;
}

uint16_t US_Front_Measure_us(void) {
  uint16_t us;

  /* send 10us pulse on TRIG line. */
  TRIG_US_front_SetVal(usDeviceFront.trigDevice);
  WAIT1_Waitus(10);
  usDeviceFront.state = ECHO_TRIGGERED;
  TRIG_US_front_ClrVal(usDeviceFront.trigDevice);
  while(usDeviceFront.state!=ECHO_FINISHED) {
    /* measure echo pulse */
    if (usDeviceFront.state==ECHO_OVERFLOW) { /* measurement took too long? */
      usDeviceFront.state = ECHO_IDLE;
      return 0; /* no echo, error case */
    }
  }
  us = (usDeviceFront.capture*1000UL)/(TU_US_front_CNT_INP_FREQ_U_0/1000);
  return us;
}

void US_Init(void) {
	  usDeviceFront.state = ECHO_IDLE;
	  usDeviceFront.capture = 0;
	  usDeviceFront.trigDevice = TRIG_US_front_Init(NULL);
	  usDeviceFront.echoDevice = TU_US_front_Init(&usDeviceFront);
	  usDeviceBack.state = ECHO_IDLE;
	  usDeviceBack.capture = 0;
	  usDeviceBack.trigDevice = TRIG_US_Back_Init(NULL);
	  usDeviceBack.echoDevice = TU_US_back_Init(&usDeviceBack);
}
