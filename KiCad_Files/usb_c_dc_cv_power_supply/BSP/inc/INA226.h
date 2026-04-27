/*
 * INA226.h
 *
 *  Created on: Nov 13, 2025
 *      Author: Ahasas
 */

#ifndef INC_INA226_H_
#define INC_INA226_H_


#define INA226_ADDR			0x40
#define CONFIG_REG			0x00
#define SHUNT_VOLT_REG		0x01
#define BUS_VOLT_REG		0x02
#define POWER_REG			0X03
#define CURRENT_REG			0x04
#define CALIBRATION_REG		0x05
#define MASK_ENABLE_REG		0x06
#define ALERT_LIMIT_reg		0x07
#define MANUFACTURE_ID_REG	0xFE
#define DIE_ID_REG			0xFF

typedef enum{
	InitSuccess,
	InitFailed
}INA226_Init_Status;

INA226_Init_Status INA226_Init(void);
float INA226_ReadBusVoltage(void);
float INA226_ReadCurrent(void);
float INA226_ReadPower(void);






#endif /* INC_INA226_H_ */
