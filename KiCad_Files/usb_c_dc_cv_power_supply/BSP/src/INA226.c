/*
 * INA226.c
 *
 *  Created on: Nov 13, 2025
 *      Author: Ahasas
 */

#include "main.h"
#include "INA226.h"

extern I2C_HandleTypeDef hi2c2;

static void INA226_WriteReg(uint16_t data, uint8_t reg_addr);
static uint16_t INA226_ReadReg(uint8_t reg);

uint16_t config_val = 0x4527; //orig
uint16_t calibration_val = 0x0D1A;// orig


void INA226_WriteReg(uint16_t data, uint8_t reg_addr)
{
	uint8_t buffer[2];
	buffer[1] = data & 0xFF;
	buffer[0] = (data >> 8) & 0xFF;

	HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c2, (INA226_ADDR << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, buffer, 2, HAL_MAX_DELAY);
	if(status == HAL_OK)
	{
		return;
	}
	}

uint16_t INA226_ReadReg(uint8_t reg)
{
    uint8_t data[2];

	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c2, INA226_ADDR << 1, reg, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
	if(status != HAL_OK)
	{
		return 82;
	}
    return (data[0] << 8) | data[1];
}


INA226_Init_Status INA226_Init(void)
{
	INA226_WriteReg(0x8000, CONFIG_REG);
	INA226_WriteReg(config_val, CONFIG_REG);
	HAL_Delay(50);
	INA226_WriteReg(calibration_val, CALIBRATION_REG);
	HAL_Delay(50);
	uint16_t config_val_read = INA226_ReadReg(CONFIG_REG);
	uint16_t calibration_val_read = INA226_ReadReg(CALIBRATION_REG);
	if(config_val_read == config_val && calibration_val_read == calibration_val)
	{
		return InitSuccess;
	}
	return InitFailed;

}

float INA226_ReadBusVoltage(void)
{
	uint16_t raw = INA226_ReadReg(BUS_VOLT_REG);
	return (raw * 0.00125f);
}

float INA226_ReadCurrent(void)
{
	int16_t raw = (int16_t)INA226_ReadReg(CURRENT_REG);
    return (raw * 0.0001526086f);

}

float INA226_ReadPower(void)
{
	uint16_t raw = INA226_ReadReg(POWER_REG);
    return (raw * 0.003815215f);
}



