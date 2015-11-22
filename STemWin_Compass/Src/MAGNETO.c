
#include "MAGNETO.h"
#include "stdint.h"
#include "I2C.h"
#include "GUI.h"
#include "stm32f429i_discovery.h"


#define MAG_SLAVE_ADDR 0x10

#define MAG_ID_REG 	0x40
#define MAG_ID_VAL	0x32

#define MAG_POWER_REG	0x4B /* Register contains power control */
#define MAG_POWER_EN	(1<<0)
#define MAG_POWER_DIS	(0<<0)

#define MAG_CONFIG_REG	0x4C /* Register contains data rate configuration and operation mode setting */
#define MAG_CONFIG_DATARATE_10HZ	(0<<3)
#define MAG_CONFIG_DATARATE_30HZ	(7<<3)
#define MAG_CONFIG_OPMODE_NORMAL	(0<<1)
#define MAG_CONFIG_OPMODE_SLEEP		(3<<1)
#define MAG_CONFIG_OPMODE_FORCED	(1<<1)

#define MAG_DRDY_INT_REG 0x4E
#define MAG_DRDY_PIN_ENABLE				(1<<7)
#define MAG_DRDY_PIN_DISABLE			(0<<7)
#define MAG_DRDY_PIN_ACTIVE_HIGH	(1<<2)
#define MAG_DRDY_PIN_ACTIVE_LOW		(0<<7)
#define MAG_CHAN_X_ENABLE					(1<<3)
#define MAG_CHAN_X_DISABLE			  (0<<3)
#define MAG_CHAN_Y_ENABLE					(1<<4)
#define MAG_CHAN_Y_DISABLE			  (0<<4)
#define MAG_CHAN_Z_ENABLE					(1<<5)
#define MAG_CHAN_Z_DISABLE			  (0<<5)

#define MAG_DRDY_REG 0x48
#define MAG_DATA_READY 0x01

/* Magnetometer data registers */
#define MAG_X_LSB 0x42
#define MAG_X_MSB 0x43
#define MAG_Y_LSB 0x44
#define MAG_Y_MSB 0x45
#define MAG_Z_LSB 0x46
#define MAG_Z_MSB 0x47

#define MAG_XY_REP_REG 0x51
#define MAG_XY_REP_VAL 47
#define MAG_Z_REP_REG	 0x52
#define MAG_Z_REP_VAL	 83

MAG_Status_T MAGNETO_Init(void)
{
	uint8_t readedChipId;
	MAG_Status_T ret_val = MAG_OK;
	MAG_Init();
	MAG_Write(MAG_SLAVE_ADDR<<1, MAG_POWER_REG, MAG_POWER_EN); /* Odblokowanie magnetometru */
	GUI_Delay(2);
	MAG_Read(MAG_SLAVE_ADDR<<1, MAG_ID_REG, &readedChipId);
	
	if(MAG_ID_VAL == readedChipId)
	{
		ret_val = MAG_OK;
		MAG_Write(MAG_SLAVE_ADDR<<1, MAG_CONFIG_REG, MAG_CONFIG_OPMODE_SLEEP);
		MAG_Write(MAG_SLAVE_ADDR<<1, MAG_XY_REP_REG, MAG_XY_REP_VAL);
		MAG_Write(MAG_SLAVE_ADDR<<1, MAG_Z_REP_REG, MAG_Z_REP_VAL);
		
		//I2C_Write(MAG_SLAVE_ADDR<<1, MAG_CONFIG_REG, (MAG_CONFIG_DATARATE_10HZ | MAG_CONFIG_OPMODE_NORMAL)); /* Ustawienie data rate  */
		//I2C_Write(MAG_SLAVE_ADDR<<1, MAG_DRDY_INT_REG, (MAG_DRDY_PIN_ENABLE | MAG_DRDY_PIN_ACTIVE_HIGH));
	}
	else
	{
		ret_val = MAG_ERROR;
	}
	return ret_val;
}

void MAGNETO_DeInit(void)
{
	MAG_Write(MAG_SLAVE_ADDR<<1, MAG_CONFIG_REG, MAG_CONFIG_OPMODE_SLEEP); 
	MAG_Write(MAG_SLAVE_ADDR<<1, MAG_POWER_REG, MAG_POWER_DIS); /* Zablokowanie magnetometru */
}

MAG_Status_T MAGNETO_StartForcedMeasure(void)
{
	MAG_Status_T ret_val = MAG_OK;
	I2C_Status_T statusI2C = I2C_OK;
	statusI2C = MAG_Write(MAG_SLAVE_ADDR<<1, MAG_CONFIG_REG, MAG_CONFIG_OPMODE_FORCED);
	
	if(I2C_OK == statusI2C)
			ret_val = MAG_OK;
	else
		ret_val = MAG_ERROR;
	
	return ret_val;
}

MAG_Status_T MAGNETO_ReadAxis(MAG_Axis_T axis, int16_t *axisValue)
{
	uint8_t axisLSB = 0, axisMSB = 0;
	MAG_Status_T ret_val = MAG_OK;
	I2C_Status_T statusI2C = I2C_OK;
	extern int16_t x_error, y_error;
	if(MAG_X_AXIS == axis)
	{
		statusI2C |= MAG_Read(MAG_SLAVE_ADDR<<1, MAG_X_LSB, &axisLSB); /* LSB X axis */
		statusI2C |= MAG_Read(MAG_SLAVE_ADDR<<1, MAG_X_MSB, &axisMSB); /* MSB X axis */
		
		*axisValue = (int16_t)((((int16_t)((int8_t)axisMSB))<<5) | (axisLSB & 0xF8) >> 3);
		*axisValue = -(*axisValue) - x_error;
		
		if(I2C_OK == statusI2C)
			ret_val = MAG_OK;
		else
			ret_val = MAG_ERROR;
		
	}
	else if(MAG_Y_AXIS == axis)
	{
		statusI2C |= MAG_Read(MAG_SLAVE_ADDR<<1, MAG_Y_LSB, &axisLSB); /* LSB X axis */
		statusI2C |= MAG_Read(MAG_SLAVE_ADDR<<1, MAG_Y_MSB, &axisMSB); /* MSB X axis */
		
		*axisValue = (int16_t)((((int16_t)((int8_t)axisMSB))<<5) | (axisLSB & 0xF8) >> 3);
		*axisValue = -(*axisValue) - y_error;
		
		if(I2C_OK == statusI2C)
			ret_val = MAG_OK;
		else
			ret_val = MAG_ERROR;
		
	}
	else
	{
		statusI2C |= MAG_Read(MAG_SLAVE_ADDR<<1, MAG_Z_LSB, &axisLSB); /* LSB X axis */
		statusI2C |= MAG_Read(MAG_SLAVE_ADDR<<1, MAG_Z_MSB, &axisMSB); /* MSB X axis */
		
		*axisValue = (int16_t)((((int16_t)((int8_t)axisMSB))<<7) | (axisLSB & 0xFE) >> 1);
		
		if(I2C_OK == statusI2C)
			ret_val = MAG_OK;
		else
			ret_val = MAG_ERROR;
		
	}
	return ret_val;
}

uint8_t MAGNETO_DataReady(void)
{
	uint8_t readyStatus = 0;
	MAG_Read(MAG_SLAVE_ADDR<<1, MAG_DRDY_REG, &readyStatus);
	
	return readyStatus;
}
