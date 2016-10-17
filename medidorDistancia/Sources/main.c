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
#include "TRIG.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LEDB.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "TU1.h"
#include "KSDK1.h"
#include "UTIL1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Ultrasonic.h"

static void getUS100_Front(void) {
  uint16_t us, cm;
  uint8_t buf[8];

  us = US_Measure_us();
  UTIL1_Num16uToStrFormatted(buf, sizeof(buf), us, ' ', 5);

  cm = US_usToCentimeters(us, 22);
  UTIL1_Num16uToStrFormatted(buf, sizeof(buf), cm, ' ', 5);
//  LCD1_WriteString((char*)buf);

  LEDR_Put(cm<10); /* red LED if object closer than 10 cm */
  LEDB_Put(cm>=10&&cm<=100); /* blue LED if object is in 10..100 cm range */
  LEDG_Put(cm>100); /* blue LED if object is in 10..100 cm range */
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  US_Init();
  for(;;) {
	getUS100_Front();
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
