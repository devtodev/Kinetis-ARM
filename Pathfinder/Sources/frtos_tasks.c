/**
 * Proyecto Pathfinder
 * Autor Carlos Miguens
 *
 */

/* Begin of <includes> initialization, DO NOT MODIFY LINES BELOW */

#include "TSK1.h"
#include "FRTOS1.h"
#include "frtos_tasks.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */

#include "RGB_Blue.h"
#include "RGB_Green.h"
#include "RGB_Red.h"
#include "MMA1.h"
#include "luces.h"
#include "acelerometro.h"

#define ACCEL_ANTIREBOTE	30

static portTASK_FUNCTION(MotorTask, pvParameters) {

  /* Write your task initialization code here ... */
  for(;;) {

  }
  /* Destroy the task */
  vTaskDelete(MotorTask);
}

static portTASK_FUNCTION(SensorUltrasonidoTask, pvParameters) {

  /* Write your task initialization code here ... */

  for(;;) {
	  vTaskDelay(100/portTICK_RATE_MS);

  }
  /* Destroy the task */
  vTaskDelete(SensorUltrasonidoTask);
}


static portTASK_FUNCTION(AcelerometroTask, pvParameters) {
	int16_t xyz[3], xyzold[3], cambioEstado;
	Movimiento movimiento;

	MMA1_Init();

	xyzold[0] = xyz[0];
	xyzold[1] = xyz[1];
	xyzold[2] = xyz[2];
	for(;;)
	{
			xyz[0] = MMA1_GetX();
			xyz[1] = MMA1_GetY();
			xyz[2] = MMA1_GetZ();

			movimiento.x = (xyz[0] > xyzold[0])?xyz[0]-xyzold[0]:xyzold[0]-xyz[0];
			movimiento.y = (xyz[1] > xyzold[1])?xyz[1]-xyzold[1]:xyzold[1]-xyz[1];
			movimiento.z = (xyz[2] > xyzold[2])?xyz[2]-xyzold[2]:xyzold[2]-xyz[2];

			movimiento.x = (movimiento.x<0)?movimiento.x*-1:movimiento.x;
			movimiento.y = (movimiento.y<0)?movimiento.y*-1:movimiento.y;
			movimiento.z = (movimiento.z<0)?movimiento.z*-1:movimiento.z;

			if ((movimiento.x< ACCEL_ANTIREBOTE)&&
				(movimiento.y< ACCEL_ANTIREBOTE)&&
				(movimiento.z< ACCEL_ANTIREBOTE))
			{
				if (cambioEstado == 1)
				{
					// poner en cola mensaje de quieto
					cambioEstado = 0;
					luces_setApagar();
				}
			}
			if ((movimiento.x> ACCEL_ANTIREBOTE)&&
				(movimiento.y> ACCEL_ANTIREBOTE)&&
				(movimiento.z> ACCEL_ANTIREBOTE))
			{
				// en movimiento
				if (cambioEstado == 0)
				{
					cambioEstado = 1;
					luces_setBlanco();
				}
			}

 			FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
			xyzold[0] = xyz[0];
			xyzold[1] = xyz[1];
			xyzold[2] = xyz[2];

	}
	/* Destroy the task */
	vTaskDelete(AcelerometroTask);
}


void CreateTasks(void) {
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
	  SensorUltrasonidoTask,  /* pointer to the task */
      "SensorUltrasonidoTask", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 3,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
     AcelerometroTask,  /* pointer to the task */
      "AcelerometroTask", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE , /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
}

