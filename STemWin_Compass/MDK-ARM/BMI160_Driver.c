#define BMI160_SLAVE_ADDR		0x68 0x69

#define BMI160_REG_CHIPID		0x00 /* Read Only */
#define BMI160_REG_ERRREG		0x01 /* Read Only */
#define BMI160_REG_PMUSTAT	0x02 /* Read Only */

#define BMI160_REG_MAGXLOW	0x04 /* Read Only */
#define BMI160_REG_MAGXHIG	0x05 /* Read Only */
#define BMI160_REG_MAGYLOW	0x06 /* Read Only */
#define BMI160_REG_MAGYHIG	0x07 /* Read Only */
#define BMI160_REG_MAGZLOW	0x08 /* Read Only */
#define BMI160_REG_MAGZHIG	0x09 /* Read Only */

#define BMI160_REG_ACCXLOW	0x12 /* Read Only */
#define BMI160_REG_ACCXHIG	0x13 /* Read Only */
#define BMI160_REG_ACCYLOW	0x14 /* Read Only */
#define BMI160_REG_ACCYHIG	0x15 /* Read Only */
#define BMI160_REG_ACCZLOW	0x16 /* Read Only */
#define BMI160_REG_ACCZHIG	0x17 /* Read Only */

#define BMI160_REG_STATUS		0x1B /* Read Only */

#define BMI160_REG_ACCCONF	0x40
#define BMI160_REG_ACCRANG  0x41
#define BMI160_REG_MAGCONF	0x44

#define BMI160_REG_MAGIF0		0x4B /* Contains magnetometer address << 1 */

#define BMI160_REG_MAGIF1				0x4C /* Contains manual enable/disable, readout offset and burst read length */
#define BMI160_MAGIF1_BURST1		0x00 /* Read 1 byte from magnetometer */
#define BMI160_MAGIF1_BURST2		0x01 /* Read 2 byte from magnetometer */
#define BMI160_MAGIF1_BURST6		0x02 /* Read 6 byte from magnetometer */
#define BMI160_MAGIF1_BURST8		0x03 /* Read 8 byte from magnetometer */

#define BMI160_MAGIF1_OFFSET		0x00 /* Trigger immediately after readout */
#define BMI160_MAGIF1_MANUAL_EN		(1<<7) /* Enable manual mode magnetometer */
#define BMI160_MAGIF1_MANUAL_DIS	(0<<7) /* Disable manual mode magnetometer */

#define BMI160_REG_MAGIF2		0x4D /* Contains address to read */
#define BMI160_REG_MAGIF3		0x4E /* Contains address to write */
#define BMI160_REG_MAGIF4		0x4F /* Contains data to write */

#define BMI160_REG_IFCONF			0x6B /* Contains digital interface configuration */
#define BMI160_IFCONF_IFMODE	(2<<4) /* Primary interface autoconfig, secondary Magnetometer */

#define BMI160_REG_CMD					0x7E
#define BMI160_CMD_ACCEL_OFF		0x10
#define BMI160_CMD_ACCEL_ON			0x11 
#define BMI160_CMD_ACCEL_LOWPOW	0x12
#define BMI160_CMD_MAG_OFF			0x18
#define BMI160_CMD_MAG_ON				0x19
#define BMI160_CMD_MAG_LOWPOW		0x1A


