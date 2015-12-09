#include "COMPASS.h"
#include "MAGNETO.h"
#include "stdint.h"
#include "math.h"
#include "GUI.h"
#include "main.h"

#define UART_DEBUG_MAG

#define COMPASS_PI 3.14159

#define COMPASS_DATA_READY 1

#ifdef UART_DEBUG_MAG
static uint16_t itoa(int16_t value, uint8_t *sp, int16_t radix);
static void appendBlansk(uint8_t *string, uint8_t current_length, uint8_t desired_length);
#endif

void COMPASS_Init(void)
{
	MAGNETO_Init();
}

void COMPASS_DeInit(void)
{
	MAGNETO_DeInit();
}

COMPASS_Status_T COMPASS_GetHeading(double *heading)
{
	COMPASS_Status_T ret_val = COMPASS_OK;
	int16_t mag_reading[3];
	MAG_Status_T statusMAG = MAG_OK;
#ifdef UART_DEBUG_MAG
	uint8_t buffer_x[] = {'x'};
	uint8_t buffer_y[] = {'y'};
	uint8_t buffer_z[] = {'z'};
	uint8_t delimiter[] = {'\n'};
	uint8_t buffer_datax[6], buffer_datay[6], buffer_dataz[6];
	uint8_t size_x, size_y, size_z;
#endif
	
	MAGNETO_StartForcedMeasure();
	
		statusMAG |= MAGNETO_ReadAxis(MAG_X_AXIS, &mag_reading[0]);
		statusMAG |= MAGNETO_ReadAxis(MAG_Y_AXIS, &mag_reading[1]);
		statusMAG |= MAGNETO_ReadAxis(MAG_Z_AXIS, &mag_reading[2]);
	
		if(MAG_ERROR == statusMAG)
			ret_val = COMPASS_ERROR;
		else 
			ret_val = COMPASS_OK;
		
		if(COMPASS_OK == ret_val)
		{
			
			*heading = atan2(mag_reading[0], mag_reading[1])*180/COMPASS_PI;
		
		if(*heading < 0)
			*heading += 360;
		
		if(*heading > 360)
			*heading -= 360;
#ifdef UART_DEBUG_MAG
		size_x = itoa(mag_reading[0], buffer_datax, 10);
		size_y = itoa(mag_reading[1], buffer_datay, 10);
		size_z = itoa(mag_reading[2], buffer_dataz, 10);
	
		appendBlansk(buffer_datax, size_x, 6);
		appendBlansk(buffer_datay, size_y, 6);
		appendBlansk(buffer_dataz, size_z, 6);
			
		UartSend(buffer_x, 1);
		UartSend(buffer_datax, 6);
		UartSend(buffer_y, 1);
		UartSend(buffer_datay, 6);
		UartSend(buffer_z, 1);
		UartSend(buffer_dataz, 6);
		UartSend(delimiter, 1);
#endif
		}
	return ret_val;
}
#ifdef UART_DEBUG_MAG
static uint16_t itoa(int16_t value, uint8_t *sp, int16_t radix)
{
	uint8_t tmp[16];
	uint8_t *tp = tmp;
	int16_t i;
	unsigned v;
	
	int16_t sign = (radix == 10 && value < 0);
	if(sign)
		v = -value;
	else
		v = (unsigned)value;
	
	while (v || tp == tmp)
	{
		i = v % radix;
		v /= radix;
		if(i<10)
			*tp++ = i+'0';
		else 
			*tp++ = i + 'a' - 10;
	}
	
	int16_t len = tp - tmp;
	
	if(sign)
	{
		*sp++ = '-';
		len++;
	}
	
	while(tp > tmp)
		*sp++ = *--tp;
	
	return len;
	
}

static void appendBlansk(uint8_t *string, uint8_t current_length, uint8_t desired_length)
{
	uint8_t ctr;
	
	if(current_length < desired_length)
	{
		for(ctr = current_length; ctr <= desired_length; ctr++)
		{
			string[ctr]=' ';
		}
	}
}
#endif
