/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : LEDR.h
**     Project     : medidorDistancia
**     Processor   : MKL25Z128VLK4
**     Component   : LED
**     Version     : Component 01.072, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-20, 18:26, # CodeGen: 21
**     Abstract    :
**          This component implements a universal driver for a single LED.
**     Settings    :
**          Component name                                 : LEDR
**          SDK                                            : KSDK1
**          Turned On with initialization                  : no
**          HW Interface                                   : 
**            Anode on port side, HIGH is ON               : no
**            On/Off                                       : Enabled
**              Pin                                        : LEDpin
**            PWM                                          : Disabled
**          Shell                                          : Disabled
**     Contents    :
**         On         - void LEDR_On(void);
**         Off        - void LEDR_Off(void);
**         Neg        - void LEDR_Neg(void);
**         Get        - uint8_t LEDR_Get(void);
**         Put        - void LEDR_Put(uint8_t val);
**         SetRatio16 - void LEDR_SetRatio16(uint16_t ratio);
**         Deinit     - void LEDR_Deinit(void);
**         Init       - void LEDR_Init(void);
**
**     License   : Open Source (LGPL)
**     Copyright : Erich Styger, 2013-2016, all rights reserved.
**     Web       : www.mcuoneclipse.com
**     This an open source software implementing a driver using Processor Expert.
**     This is a free software and is opened for education, research and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file LEDR.h
** @version 01.00
** @brief
**          This component implements a universal driver for a single LED.
*/         
/*!
**  @addtogroup LEDR_module LEDR module documentation
**  @{
*/         

#ifndef __LEDR_H
#define __LEDR_H

/* MODULE LEDR. */
#ifndef __HIWARE__ /* Hiware compiler (S08, S12) only supports C89 */
  #include <stdint.h>
#endif
/* Include inherited beans */
#include "KSDK1.h"
#include "LEDpin1.h"

#if KSDK1_SDK_VERSION_USED == KSDK1_SDK_VERSION_NONE
  /* Include shared modules, which are used for whole project */
  #include "PE_Types.h"
  #include "PE_Error.h"
  #include "PE_Const.h"
  #include "IO_Map.h"
  #include "Cpu.h"
#endif


#define LEDR_ClrVal()    LEDpin1_ClrVal() /* put the pin on low level */
#define LEDR_SetVal()    LEDpin1_SetVal() /* put the pin on high level */
#define LEDR_SetInput()  LEDpin1_SetInput() /* use the pin as input pin */
#define LEDR_SetOutput() LEDpin1_SetOutput() /* use the pin as output pin */

#define LEDR_PARSE_COMMAND_ENABLED  0 /* set to 1 if method ParseCommand() is present, 0 otherwise */


#define LEDR_On() LEDpin1_ClrVal()
/*
** ===================================================================
**     Method      :  LEDR_On (component LED)
**     Description :
**         This turns the LED on.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define LEDR_Off() LEDpin1_SetVal()
/*
** ===================================================================
**     Method      :  LEDR_Off (component LED)
**     Description :
**         This turns the LED off.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define LEDR_Neg() LEDpin1_NegVal()
/*
** ===================================================================
**     Method      :  LEDR_Neg (component LED)
**     Description :
**         This negates/toggles the LED
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define LEDR_Get() (!(LEDpin1_GetVal()))
/*
** ===================================================================
**     Method      :  LEDR_Get (component LED)
**     Description :
**         This returns logical 1 in case the LED is on, 0 otherwise.
**     Parameters  : None
**     Returns     :
**         ---             - Status of the LED (on or off)
** ===================================================================
*/

void LEDR_Init(void);
/*
** ===================================================================
**     Method      :  LEDR_Init (component LED)
**     Description :
**         Performs the LED driver initialization.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define LEDR_Put(val)  ((val) ? LEDR_On() : LEDR_Off())
/*
** ===================================================================
**     Method      :  LEDR_Put (component LED)
**     Description :
**         Turns the LED on or off.
**     Parameters  :
**         NAME            - DESCRIPTION
**         val             - value to define if the LED has to be on or
**                           off.
**     Returns     : Nothing
** ===================================================================
*/

void LEDR_Deinit(void);
/*
** ===================================================================
**     Method      :  LEDR_Deinit (component LED)
**     Description :
**         Deinitializes the driver
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LEDR_SetRatio16(uint16_t ratio);
/*
** ===================================================================
**     Method      :  LEDR_SetRatio16 (component LED)
**     Description :
**         Method to specify the duty cycle. If using a PWM pin, this
**         means the duty cycle is set. For On/off pins, values smaller
**         0x7FFF means off, while values greater means on.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ratio           - Ratio value, where 0 means 'off' and
**                           0xffff means 'on'
**     Returns     : Nothing
** ===================================================================
*/

/* END LEDR. */

#endif
/* ifndef __LEDR_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
