/*
 * Accelerometro_driver.c
 *
 *  Created on: Mar 25, 2016
 *      Author: Carlos Miguens
 * 		Proyecto Pathfinder
 */

/* Registros para FreeFall Motion */
#define ACCEL_FF_MT_CFG	  0x15
#define ACCEL_FF_MT_SRC   0x16
#define ACCEL_FF_MT_THS   0x17
#define ACCEL_FF_MT_COUNT 0x18
#define ACCEL_REG_1	  	  0x2A
#define ACCEL_REG_2	      0x2B
#define ACCEL_REG_3  	  0x2C
#define ACCEL_REG_4  	  0x2D
#define ACCEL_REG_5  	  0xE2
#define ACCEL_REG_RANGE   0x0E

#define ACCEL_ACTIVE_BIT_MASK 1
#define ACCEL_READ_BIT_MASK   1 << 1
#define ACCEL_NOISE_MASK	  1 << 2
#define ACCEL_DR0_MASK		  1 << 3
#define ACCEL_DR1_MASK		  1 << 4
#define ACCEL_DR2_MASK		  1 << 5
#define ACCEL_ASLP_RATE0	  1 << 6
#define ACCEL_ASLP_RATE1	  1 << 7

#include <acelerometro.h>
#include "MMA1.h"
#include "GI2C1.h"
#include "FreeRTOS.h"

#define ACCEL_LOW_POWER 		0
#define ACCEL_HIGH_RESOLUTION 	1

void Accel_Init(void)
{
	unsigned char ctrl_reg_1 = 0,  ctrl_reg_2 = 0,  ctrl_reg_3 = 0, ctrl_reg_5 = 0,  ctrl_reg_4 = 0, ctrl_reg_range = 0;
	unsigned char ff_mm_cfg = 0;

	uint8_t buf, rbuf;
	static const uint8_t addr = ACCEL_FF_MT_CFG; //ACCEL_FF_MT_SRC;

	ctrl_reg_1 |= ACCEL_ACTIVE_BIT_MASK;
	// Choose Motion to wake the device from sleep
	ctrl_reg_3 |= 1 << 3; //WAKE_FF_MT
	// interrupt enable INT1
	ctrl_reg_4 |= 1 << 7; // INT_EN_ASLP   Auto-SLEEP/WAKE interrupt enabled.
	ctrl_reg_4 |= 1 << 2; // INT_EN_FF_MT  Freefall/Motion interrupt enabled
	ctrl_reg_4 |= 1; 	  // INT_EN_DRDY   Data Ready interrupt enabled

	//  interrupt enable INT2
	ctrl_reg_5 |= 1 << 7; // INT_CFG_ASLP   0: Interrupt is routed to INT2 pin; 1: Interrupt is routed to INT1 pin
	ctrl_reg_5 |= 1 << 2; // INT_CFG_FF_MT  0: Interrupt is routed to INT2 pin; 1: Interrupt is routed to INT1 pin
	ctrl_reg_5 |= 1; 	  // INT_CFG_DRDY   Data Ready interrupt enabled

	/* Mode 3: Motion Detection with ELE = 0, OAE = 1
	In this mode, the EA bit indicates a motion event after the debounce counter time is reached. The ZEFE, YEFE, and XEFE
	control bits determine which axes are taken into consideration for motion detection. Once the EA bit is set, and DBCNTM = 0,
	the EA bit can get cleared only after the delay specified by FF_MT_COUNT. If DBCNTM = 1, the EA bit is cleared as soon as the
	motion high g condition disappears. The event flags ZHE, ZHP, YHE, YHP, XHE, and XHP reflect the motion detection status
	(i.e., high g event) without any debouncing, provided that the corresponding bits ZEFE, YEFE, and/or XEFE are set. Reading the
	FF_MT_SRC does not clear any flags, nor is the debounce counter reset.
	*/
	ff_mm_cfg |= 1 << 3; // x Event flag enable
	ff_mm_cfg |= 1 << 4; // y Event flag enable
	ff_mm_cfg |= 1 << 5; // z Event flag enable
	ff_mm_cfg |= 1 << 6; // motion detection

	// The interrupts
	GI2C1_SelectSlave(MMA1_I2C_ADDR);
	GI2C1_Init();
	MMA1_Init();
	FRTOS1_vTaskDelay(700/portTICK_RATE_MS);
	GI2C1_WriteByteAddress8(MMA1_I2C_ADDR, ACCEL_REG_1, ctrl_reg_1);
	GI2C1_WriteByteAddress8(MMA1_I2C_ADDR, ACCEL_REG_2, ctrl_reg_2);
	GI2C1_WriteByteAddress8(MMA1_I2C_ADDR, ACCEL_REG_4, ctrl_reg_4);
	GI2C1_WriteByteAddress8(MMA1_I2C_ADDR, ACCEL_REG_5, ctrl_reg_5);
	GI2C1_WriteByteAddress8(MMA1_I2C_ADDR, 0x15, ff_mm_cfg); // ACCEL_FF_MT_CFG
	FRTOS1_vTaskDelay(700/portTICK_RATE_MS);
	GI2C1_ReadByteAddress8(MMA1_I2C_ADDR, 0x0D, &buf); // WHO_I_AM = 0x1a
	GI2C1_ReadByteAddress8(MMA1_I2C_ADDR, 0x15, &buf); // ACCEL_FF_MT_CFG = 0 why??? :-(
	return 0;
}

// detecta si hay movimiento
Movimiento getMovimiento()
{
	Movimiento resultado;
	unsigned char lectura;
	uint8_t buf;
	static const uint8_t addr = ACCEL_FF_MT_SRC;

	if(GI2C1_ReadAddress(MMA1_I2C_ADDR, (uint8_t*)&addr, sizeof(addr), &buf, 1)!=ERR_OK) {
		resultado.flag = -1;
		return resultado;
	}
	lectura = buf;
	/*
		resultado.flag = 0;
		return resultado;	* 0x16: FF_MT_SRC Freefall/Motion Source Register
	Bit 7 	Bit 6 	Bit 5 	Bit 4 	Bit 3 	Bit 2 	Bit 1 	Bit 0
	EA 		— 		ZHE 	ZHP 	YHE 	YHP 	XHE 	XHP

	 EA 0 No event flag has been asserted; 1: one or more event flag has been asserted
	 ZHE YHE XHE Motion event detected
	 ZHP YHP XHP Motion Polarity Flag

	 * */

	if (!lectura && (1 << 7))
	{
		resultado.flag = 0;
		resultado.x = 0;
		resultado.y = 0;
		resultado.z = 0;
		return resultado;
	}
	// se detecto movimiento !
	resultado.flag = 1;

	if (lectura && (1 << 1))
	{
		resultado.x = (lectura && 1)?ACCEL_POSITIVO:ACCEL_NEGATIVO;
	} else {
		resultado.x = ACCEL_NEUTRO;
	}

	if (lectura && (1 << 3))
	{
		resultado.y = (lectura && (1<< 2))?ACCEL_POSITIVO:ACCEL_NEGATIVO;
	} else {
		resultado.y = ACCEL_NEUTRO;
	}

	if (lectura && (1 << 5))
	{
		resultado.z = (lectura && (1<< 4))?ACCEL_POSITIVO:ACCEL_NEGATIVO;
	} else {
		resultado.z = ACCEL_NEUTRO;
	}

	return resultado;
}

void Accel_Wake()
{
	MMA1_Enable();
}

void Accel_Sleep()
{
	MMA1_Disable();
}

/*
 * calculo de distancia recorrida
 */


void Calibrate(void)
{
	unsigned int count1;
	count1 = 0;

	do{
		ADC_GetAllAxis();
		sstatex = sstatex + Sample_X; // Accumulate Samples
		sstatey = sstatey + Sample_Y;
		count1++;
	}while(count1!=0x0400); // 1024 times

	sstatex=sstatex>>10; // division between 1024
	sstatey=sstatey>>10;
}

