/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B_1_OP_OnOff_Pin GPIO_PIN_0
#define B_1_OP_OnOff_GPIO_Port GPIOA
#define B_1_OP_OnOff_EXTI_IRQn EXTI0_1_IRQn
#define B_3_Mode_Pin GPIO_PIN_1
#define B_3_Mode_GPIO_Port GPIOA
#define B_3_Mode_EXTI_IRQn EXTI0_1_IRQn
#define B_2_VL_Pin GPIO_PIN_2
#define B_2_VL_GPIO_Port GPIOA
#define B_2_VL_EXTI_IRQn EXTI2_3_IRQn
#define cfg1_Pin GPIO_PIN_8
#define cfg1_GPIO_Port GPIOA
#define cfg2_Pin GPIO_PIN_9
#define cfg2_GPIO_Port GPIOA
#define cfg3_Pin GPIO_PIN_10
#define cfg3_GPIO_Port GPIOA
#define buck_mosfet_Pin GPIO_PIN_11
#define buck_mosfet_GPIO_Port GPIOA
#define pure_mosfet_Pin GPIO_PIN_12
#define pure_mosfet_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

#define ON		1
#define OFF		0

typedef enum{
	OutputOff,
	OutputOn
}output_status;

typedef enum{
	CFGSET = GPIO_PIN_SET,
	CFGRESET = GPIO_PIN_RESET
}decoy_cfg_pin;

typedef enum{
	Mode1,
	Mode2
}mode_type;

typedef enum{
	Five,
	Nine,
	Twelve,
	Fifteen,
	Twenty
}voltage_level;

typedef struct{
	decoy_cfg_pin cfg1;
	decoy_cfg_pin cfg2;
	decoy_cfg_pin cfg3;
}config_pins_state;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
