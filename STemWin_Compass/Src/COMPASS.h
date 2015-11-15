#ifndef COMPASS_H
#define COMPASS_H

typedef enum COMPASS_Status_Type
{
	COMPASS_OK,
	COMPASS_ERROR
} COMPASS_Status_T;

void COMPASS_Init(void);

void COMPASS_DeInit(void);

/* @brief This function calculate the heading of board in degrees and saves the result in *heading parameter
 *
 * @param *heading is a variable to save the result to
 *
 * @return COMPASS_Status COMPASS_OK if everything goes well, COMPASS_ERROR if something goes wrong
 */
COMPASS_Status_T COMPASS_GetHeading(double *heading);

#endif 
