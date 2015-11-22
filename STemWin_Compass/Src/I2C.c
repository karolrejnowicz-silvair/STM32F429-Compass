#include "I2C.h"
#include "stm32f429i_discovery.h"

#define I2C_TIMEOUT 0x3000

I2C_HandleTypeDef I2C_Handler;

void I2C_Init(void)
{
	if(HAL_I2C_GetState(&I2C_Handler) == HAL_I2C_STATE_RESET)
  {
	I2C_Handler.Instance              = DISCOVERY_I2Cx;
	I2C_Handler.Init.ClockSpeed       = BSP_I2C_SPEED;
	I2C_Handler.Init.DutyCycle        = I2C_DUTYCYCLE_2;
	I2C_Handler.Init.OwnAddress1      = 0;
	I2C_Handler.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
	I2C_Handler.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLED;
	I2C_Handler.Init.OwnAddress2      = 0;
	I2C_Handler.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLED;
	I2C_Handler.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLED; 
	
	HAL_I2C_Init(&I2C_Handler);
		
	}
}

I2C_Status_T I2C_Write(uint8_t Address, uint8_t Register, uint8_t Value)
{	
	I2C_Status_T ret_val = I2C_OK;
	HAL_StatusTypeDef i2c_status = HAL_OK;
	
	i2c_status = HAL_I2C_Mem_Write(&I2C_Handler, Address, Register, 1, &Value, 1, I2C_TIMEOUT);
	if(HAL_OK == i2c_status)
		ret_val = I2C_OK;
	else
		ret_val = I2C_ERROR;
	
	return ret_val;
}

I2C_Status_T I2C_Read(uint8_t Address, uint8_t Register, uint8_t *Value)
{
	I2C_Status_T ret_val = I2C_OK;
	HAL_StatusTypeDef i2c_status = HAL_OK;
	
	i2c_status = HAL_I2C_Mem_Read(&I2C_Handler, Address, Register, 1, Value, 1, I2C_TIMEOUT);
	if(HAL_OK == i2c_status)
		ret_val = I2C_OK;
	else
		ret_val = I2C_ERROR;
	
	return ret_val;
}
