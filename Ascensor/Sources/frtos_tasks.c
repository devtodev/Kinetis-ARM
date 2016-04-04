/*
 * WIFI_actions.c
 *
 *  Created on: Marzo 2016
 *      Author: Carlos Miguens
 */


#define GATEWAY 	1
#define SENSOR  	1
#define HDMI 		1
#define ZAPATILLA 	0
#define MODO_DEBUG  0
#define ACCEL_ANTIREBOTE	30

/* Begin of <includes> initialization, DO NOT MODIFY LINES BELOW */

#include "TSK1.h"
#include "FRTOS1.h"
#include "frtos_tasks.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */

#include "utils.h"
#include "BT_actions.h"
#include "WIFI_actions.h"
#include "UTIL1.h"
#include "LCD/LCDConfig.h"
#include "SegLCD1.h"
#include "Acelerometro_driver.h"
#include "LED1.h"
#include "LED2.h"
#include "MMA1.h"

#if GATEWAY

static portTASK_FUNCTION(GatewayTask, pvParameters) {

  initGateway();
  for(;;) {
    xSemaphoreTake(xSemaphoreWifiATCommand, portMAX_DELAY);
    readBuffer();
  }
  /* Destroy the task */
  vTaskDelete(GatewayTask);
}

#endif

#if SENSOR

static portTASK_FUNCTION(SensorTask, pvParameters) {
	int16_t xyz[3], xyzold[3], cambioEstado;
	char lcdText[] = "1234293812";
	Movimiento movimiento;

	BT_init();
	MMA1_Init();

	MySegLCDPtr = SegLCD1_Init(NULL);
	//  SymbolON(11,0);
	xyzold[0] = xyz[0];
	xyzold[1] = xyz[1];
	xyzold[2] = xyz[2];
	for(;;)
	{
#if !GATEWAY
		if (1 == 1)
#else
		if (connection.status  == WIFI_CONNECTED)
#endif
		{
			//LED1_Put(movimiento.flag);
			//LED2_Put(movimiento.x);
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
#if GATEWAY
					sendInfo("QUI\0");
#endif
					BT_showString("Quieto\r\n\0");

				}
			}
			if ((movimiento.x> ACCEL_ANTIREBOTE)&&
				(movimiento.y> ACCEL_ANTIREBOTE)&&
				(movimiento.z> ACCEL_ANTIREBOTE))
			{
				// en movimiento
				if (cambioEstado == 0)
				{
					// poner en cola mensaje de movimiento
					cambioEstado = 1;
#if GATEWAY
					sendInfo("MOV\0");
#endif
					BT_showString("Movio\r\n\0");
				}
			}
#if MODO_DEBUG
			itoa(movimiento.x, lcdText);
			BT_showString(lcdText);
			BT_showString("     \0");
			itoa(movimiento.y, lcdText);
			BT_showString(lcdText);
			BT_showString("     \0");
			itoa(movimiento.z, lcdText);
			BT_showString(lcdText);
			BT_showString("     \0");
			BT_showString("\r\n");
#endif

#if GATEWAY
			// desconectar del wifi al apretar la q
			if (getBufferBT()[0] == 'q')
			{
				disconectFromSpot();
			}
#endif
			FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
			xyzold[0] = xyz[0];
			xyzold[1] = xyz[1];
			xyzold[2] = xyz[2];
		} else {
			FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);
		}

	}
	/* Destroy the task */
	vTaskDelete(SensorTask);
}

#endif

#if HDMI
static portTASK_FUNCTION(HMITask, pvParameters) {
#if ZAPATILLA
  char menuConectado[MENUMAXLENGHT][64] = {"Switch 1", "Switch 2", "Switch 3", "Switch 4", "Switch 5", "Switch 6", "Desconectar"};
#endif
  char opcionHIM[30];
  int i;
  /* Write your task initialization code here ... */
  BT_init();


  for(;;) {
	  xSemaphoreTake(xSemaphoreWifiRefresh, portMAX_DELAY);
	  switch (connection.status)
	  {
	  	  case WIFI_DISCONNECTED:
		    // necesito obtener los spots
	  		BT_sendSaltoLinea();BT_sendSaltoLinea();BT_sendSaltoLinea();BT_sendSaltoLinea();
	  		BT_showString("Sensor de MoViMiEnTo Wifi ~ BT Spot");
	  		BT_sendSaltoLinea();BT_sendSaltoLinea();
	  		refreshWifiSpots();
	  		FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
	  		xSemaphoreTake(xSemaphoreWifiRefresh, portMAX_DELAY);
	  		if (SSIDStoredVisible())
	  		{
	  			strcpy(connection.ssid, storeSSID);
	  			strcpy(connection.password, storePassword);
	  			tryToConnect();
	  		} else {
				// mostrar los SSIDs
				if (BT_showMenu(&spotSSID, &connection.ssid[0]) != -69)
				{
					// setPassword
					BT_sendSaltoLinea();
					BT_showString("Seleccion: ");
					BT_showString(&connection.ssid[0]);
					BT_sendSaltoLinea();
					BT_askValue("Password: ", &connection.password[0]);
					// showDetails
					BT_sendSaltoLinea();BT_sendSaltoLinea();
					BT_showString("Conectando...");
			  		// try to connect
					tryToConnect();
				} else {
					xSemaphoreGive(xSemaphoreWifiRefresh);
					for (i = 0; i < 100; i++) BT_sendSaltoLinea();
				}
	  		}
		  break;
	  	  case WIFI_CONNECTING:
	  		FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);
	  		connectionMode();
			xSemaphoreTake(xSemaphoreWifiRefresh, portMAX_DELAY);
			FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
			connectingToServer();
		  break;
	  	  case WIFI_CONNECTED:
#if ZAPATILLA
	  		switch (BT_showMenu(&menuConectado, &opcionHIM[0]))
	  		{
				case 0:
					SW1_NegVal();
					if (SW1_GetVal())
						sendInfo("1|1");
					else
						sendInfo("1|0");
				break;
				case 1:
					SW2_NegVal();
					if (SW1_GetVal())
						sendInfo("2|1");
					else
						sendInfo("2|0");
				break;
				case 2:
					SW3_NegVal();
					if (SW1_GetVal())
						sendInfo("3|1");
					else
						sendInfo("3|0");
				break;
				case 3:
					SW4_NegVal();
					if (SW1_GetVal())
						sendInfo("4|1");
					else
						sendInfo("4|0");
				break;
				case 4:
					SW5_NegVal();
					if (SW1_GetVal())
						sendInfo("5|1");
					else
						sendInfo("5|0");
				break;
				case 5:
					SW6_NegVal();
					if (SW1_GetVal())
						sendInfo("6|1");
					else
						sendInfo("6|0");
				break;
				case 6:
					disconectFromSpot();
				break;
				case -69:
					xSemaphoreGive(xSemaphoreWifiRefresh);
					for (i = 0; i < 100; i++) BT_sendSaltoLinea();
				break;
	  		}
#endif
		  break;
	  }
  }
  /* Destroy the task */
  vTaskDelete(HMITask);
}
#endif

void CreateTasks(void) {
	BT_init();

#if GATEWAY

	if (FRTOS1_xTaskCreate(
     GatewayTask,  /* pointer to the task */
      "Gateway", /* task name for kernel awareness debugging */
      1200, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }

#endif

#if SENSOR

  if (FRTOS1_xTaskCreate(
	 SensorTask,  /* pointer to the task */
	  "Sensor", /* task name for kernel awareness debugging */
	  1200, /* task stack size */
	  (void*)NULL, /* optional task startup argument */
	  tskIDLE_PRIORITY + 2,  /* initial priority */
	  (xTaskHandle*)NULL /* optional task handle to create */
	) != pdPASS) {
	  /*lint -e527 */
	  for(;;){}; /* error! probably out of memory */
	  /*lint +e527 */
  }

#endif

#if HDMI
  if (FRTOS1_xTaskCreate(
     HMITask,  /* pointer to the task */
      "HMI", /* task name for kernel awareness debugging */
      1200, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 0,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
#endif
}


