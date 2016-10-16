/* ###################################################################
**     Filename    : Events.h
**     Project     : Gateway Wifi
**     Processor   : MKL46Z256VMC4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-12-22, 15:49, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "BT.h"
#include "ASerialLdd2.h"
#include "MMA1.h"
#include "GI2C1.h"
#include "I2C0.h"
#include "I2CSPY1.h"
#include "TMOUT1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd3.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd4.h"
#include "Accel_Int1.h"
#include "BitIoLdd9.h"
#include "Accel_Int2.h"
#include "BitIoLdd10.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "KSDK1.h"
#include "SegLCD1.h"
#include "TI1.h"
#include "ESP8266.h"
#include "ASerialLdd1.h"
#include "FRTOS1.h"
#include "TSK1.h"
#include "UTIL1.h"
#include "CS1.h"
#include "TU1.h"
#include "TimeDate.h"
#include "Flash.h"
#include "IntFlashLdd1.h"
#include "SW4.h"
#include "BitIoLdd1.h"
#include "SW1.h"
#include "BitIoLdd2.h"
#include "SW2.h"
#include "SW3.h"
#include "SW5.h"
#include "BitIoLdd7.h"
#include "SW6.h"
#include "BitIoLdd5.h"
#include "UTIL1.h"
#include "BitIoLdd8.h"
#include "BitIoLdd6.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL46Z256LL4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/*
** ===================================================================
**     Event       :  BT_OnError (module Events)
**
**     Component   :  BT [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BT_OnError(void);

/*
** ===================================================================
**     Event       :  BT_OnRxChar (module Events)
**
**     Component   :  BT [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BT_OnRxChar(void);

/*
** ===================================================================
**     Event       :  BT_OnTxChar (module Events)
**
**     Component   :  BT [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BT_OnTxChar(void);

/*
** ===================================================================
**     Event       :  ESP8266_OnError (module Events)
**
**     Component   :  ESP8266 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESP8266_OnError(void);

/*
** ===================================================================
**     Event       :  ESP8266_OnRxChar (module Events)
**
**     Component   :  ESP8266 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESP8266_OnRxChar(void);

/*
** ===================================================================
**     Event       :  ESP8266_OnTxChar (module Events)
**
**     Component   :  ESP8266 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESP8266_OnTxChar(void);

/*
** ===================================================================
**     Event       :  ESP8266_OnFullRxBuf (module Events)
**
**     Component   :  ESP8266 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESP8266_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  ESP8266_OnFreeTxBuf (module Events)
**
**     Component   :  ESP8266 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESP8266_OnFreeTxBuf(void);

/*
** ===================================================================
**     Event       :  BT_OnFullRxBuf (module Events)
**
**     Component   :  BT [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BT_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  BT_OnFreeTxBuf (module Events)
**
**     Component   :  BT [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BT_OnFreeTxBuf(void);

void FRTOS1_vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationStackOverflowHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         if enabled, this hook will be called in case of a stack
**         overflow.
**     Parameters  :
**         NAME            - DESCRIPTION
**         pxTask          - Task handle
**       * pcTaskName      - Pointer to task name
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationTickHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationTickHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationIdleHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationIdleHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called when the RTOS is idle.
**         This might be a good place to go into low power mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationMallocFailedHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationMallocFailedHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt_LDD]
*/
/*!
**     @brief
**         Called if periodic event occur. Component and OnInterrupt
**         event must be enabled. See [SetEventMask] and [GetEventMask]
**         methods. This event is available only if a [Interrupt
**         service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TI1_OnInterrupt(LDD_TUserData *UserDataPtr);

void MINT1_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  MINT1_OnInterrupt (module Events)
**
**     Component   :  MINT1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
