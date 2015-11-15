#ifndef I2C_H
#define I2C_H


#include "stdint.h"
#include "stm32f4xx_hal_def.h"

typedef enum I2C_Status_Type
{
	I2C_OK,
	I2C_ERROR
} I2C_Status_T;

void I2C_Init(void);
I2C_Status_T I2C_Write(uint8_t Address, uint8_t Register, uint8_t Value);
I2C_Status_T I2C_Read(uint8_t Address, uint8_t Register, uint8_t *Value);

#endif
