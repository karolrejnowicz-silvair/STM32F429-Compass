#ifndef MAGNETO_H
#define MAGNETO_H

#include "stdint.h"

typedef enum MAG_Status_Type
{
	MAG_OK,
	MAG_ERROR
} MAG_Status_T;

typedef enum MAG_Axis_Type
{
	MAG_X_AXIS,
	MAG_Y_AXIS,
	MAG_Z_AXIS
} MAG_Axis_T;

/* @brief Ths function initialize magnetometer
 * 
 * @return MAG_Status: MAG_OK if everything goes well, MAG_ERROR if something goes wrong
 */
MAG_Status_T MAGNETO_Init(void);


void MAGNETO_DeInit(void);

MAG_Status_T MAGNETO_StartForcedMeasure(void);

/* @brief This function reads values from chosen magnetometer axis and saves it in variable passed to function as a parameter
 * 
 * @param axis is the chosen axis to read the value from
 *
 * @param *axisValue is a variable to save the value to
 *
 * @return MAG_Status MAG_OK if everything goes well, MAG_ERROR if something goes wrong
 */
MAG_Status_T MAGNETO_ReadAxis(MAG_Axis_T axis, int16_t *axisValue);


uint8_t MAGNETO_DataReady(void);

#endif
