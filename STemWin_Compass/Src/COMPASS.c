#include "COMPASS.h"
#include "MAGNETO.h"
#include "stdint.h"
#include "math.h"
#include "GUI.h"

#define COMPASS_PI 3.14159

#define COMPASS_DATA_READY 1

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
	int16_t mag_reading[2];
	MAG_Status_T statusMAG = MAG_OK;
	
	MAGNETO_StartForcedMeasure();
	
	//if(COMPASS_DATA_READY & MAGNETO_DataReady())
	//{
		statusMAG |= MAGNETO_ReadAxis(MAG_X_AXIS, &mag_reading[0]);
		statusMAG |= MAGNETO_ReadAxis(MAG_Y_AXIS, &mag_reading[1]);
			
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
		}
	//}
	return ret_val;
}
