/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : TasksOs.c
**     CDE edition : Community
**     Project     : Gateway Wifi
**     Processor   : MKL46Z256VLL4
**     Component   : FreeRTOS_Tasks
**     Version     : Component 01.008, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-12-22, 19:07, # CodeGen: 7
**     Abstract    :
**
**     Settings    :
**          Component Name                                 : TasksOs
**          FreeRTOS                                       : FRTOS1
**          Number of tasks                                : 2
**            FreeRTOS task                                : GatewayTask
**              Task name                                  : Gateway
**              Stack size (plus configMINIMAL_STACK_SIZE) : 300
**              Initial Priority                           : 0
**            FreeRTOS task                                : HMITask
**              Task name                                  : HMI
**              Stack size (plus configMINIMAL_STACK_SIZE) : 300
**              Initial Priority                           : 0
**     Contents    :
**         CreateTasks - void TasksOs_CreateTasks(void);
**
**     License   :  Open Source (LGPL)
**     Copyright : (c) Omar Isaí Pinales Ayala, 2014, all rights reserved.
**     http      : http://www.mcuoneclipse.com
**     This an open source software driver for Processor Expert.
**     This is a free software and is opened for education,  research  and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file TasksOs.c
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup TasksOs_module TasksOs module documentation
**  @{
*/         

/* MODULE TasksOs. */

#include "TasksOs.h"
#include "frtos_tasks.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
** ===================================================================
**     Method      :  TasksOs_CreateTasks (component FreeRTOS_Tasks)
**     Description :
**         Creates the tasks.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TasksOs_CreateTasks(void)
{
  CreateTasks();
}


#ifdef __cplusplus
}  /* extern "C" */
#endif
/* END TasksOs. */

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
