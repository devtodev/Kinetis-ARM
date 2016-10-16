
/* Begin of <includes> initialization, DO NOT MODIFY LINES BELOW */

#include "TSK1.h"
#include "FRTOS1.h"
#include "frtos_tasks.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */

#include "RGB_Blue.h"
#include "RGB_Green.h"
#include "RGB_Red.h"

static portTASK_FUNCTION(RadioTask, pvParameters) {

  /* Write your task initialization code here ... */

  for(;;) {

	  RGB_Blue_NegVal();
	  vTaskDelay(1000/portTICK_RATE_MS);

  }
  /* Destroy the task */
  vTaskDelete(RadioTask);
}

static portTASK_FUNCTION(MotorTask, pvParameters) {

  /* Write your task initialization code here ... */

  for(;;) {

	  RGB_Green_NegVal();
	  vTaskDelay(777/portTICK_RATE_MS);

  }
  /* Destroy the task */
  vTaskDelete(MotorTask);
}

static portTASK_FUNCTION(SensorTaskTask, pvParameters) {

  /* Write your task initialization code here ... */

  for(;;) {

	  RGB_Red_NegVal();
	  vTaskDelay(444/portTICK_RATE_MS);

  }
  /* Destroy the task */
  vTaskDelete(SensorTaskTask);
}

void CreateTasks(void) {
  if (FRTOS1_xTaskCreate(
     RadioTask,  /* pointer to the task */
      "RadioTask", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
     MotorTask,  /* pointer to the task */
      "MotorTask", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 2,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
     SensorTaskTask,  /* pointer to the task */
      "SensorTask", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE , /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 3,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
}

