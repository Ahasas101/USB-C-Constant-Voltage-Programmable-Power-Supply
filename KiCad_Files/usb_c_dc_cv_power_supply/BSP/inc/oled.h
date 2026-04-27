/*
 * oled.h
 *
 *  Created on: Nov 15, 2025
 *      Author: Ahasas
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_


#include "main.h"

#define SSD1306_I2C_ADDR   0x3C //Previously it was 0x3c
#define SSD1306_WIDTH      128
#define SSD1306_HEIGHT     64

void SSD1306_Init(void);
void SSD1306_Clear(void);
void SSD1306_Update(void);

void SSD1306_Print(uint8_t x, uint8_t y, char *str);
void SSD1306_PrintNumber(uint8_t x, uint8_t y, int num);
void SSD1306_Print2X(uint8_t x, uint8_t y, char *str);
void SSD1306_Print15X(uint8_t x, uint8_t y, char *str);

#endif




