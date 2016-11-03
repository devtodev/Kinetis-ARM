/*
 * Ultrasonic.c
 *
 *  Created on: Oct 17, 2016
 *      Author: Carlos Miguens
 *      Driver for the US 100 and FRDM-KL25Z board
 */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "WAIT1.h"
#include "TU1.h"
#include "KSDK1.h"
#include "TRIG.h"
#include "UTIL1.h"
#include "BT.h"
#include "ASerialLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "Ultrasonic.h"
#include "BT_actions.h"

int Measure(void) {
  uint16_t us, cm;
  uint8_t buf[8];

  us = US_Measure_us();
  UTIL1_Num16uToStrFormatted(buf, sizeof(buf), us, ' ', 5);

  cm = US_usToCentimeters(us, 22);
  UTIL1_Num16uToStrFormatted(buf, sizeof(buf), cm, ' ', 5);

  return cm;
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  char bufferText[20];
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  US_Init();
  BT_showString("Bienvenido al medidor de distancia \r\n");
  for(;;) {
    UTIL1_Num16uToStr(bufferText, 20, Measure());
    BT_showString(bufferText);
    BT_showString("\r\n");
    WAIT1_Waitms(50); /* wait at least for 50 ms until the next measurement to avoid echos */
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
