/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "INA226.h"
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

/* USER CODE BEGIN PV */
volatile mode_type Mode = Mode1;
volatile voltage_level Voltage = Five;
volatile output_status Output = OutputOff;
volatile config_pins_state cfg;
volatile uint32_t prev_tick = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */
static void set_pure_mosfet(uint8_t val);
static void set_buck_mosfet(uint8_t val);
static void toggle_output(void);
static void toggle_mode(void);
static void toggle_voltage_level(void);
static void set_decoy_voltage(config_pins_state* conf);

static void print_output(void);
static void print_mode(void);
static void print_voltage_current_power(void);
static void print_data(void);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  cfg.cfg1 = CFGSET;
  cfg.cfg2 = CFGSET;
  cfg.cfg3 = CFGSET;

  set_decoy_voltage((config_pins_state *)&cfg);

  SSD1306_Init();

  SSD1306_Clear();

  //SSD1306_Print15X(0, 0, "MODE-1");
  //SSD1306_Print15X(95, 0, "ON");

  SSD1306_Print2X(0, 0, "PSY");
  SSD1306_Print15X(0, 25, "Designed By:");
  SSD1306_Print15X(0, 45, "Ahasas101");



  //SSD1306_Print2X(0, 32, "10.234 A");
  //SSD1306_Print2X(0, 50, "35.691 W");
  SSD1306_Update();
  INA226_Init_Status status = INA226_Init();
  HAL_Delay(2000);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	//  print_voltage_current_power();
	//  HAL_Delay(10);
	print_data();
	HAL_Delay(10);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00201D2B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00201D2B;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, cfg1_Pin|cfg2_Pin|cfg3_Pin|buck_mosfet_Pin
                          |pure_mosfet_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : B_1_OP_OnOff_Pin B_3_Mode_Pin B_2_VL_Pin */
  GPIO_InitStruct.Pin = B_1_OP_OnOff_Pin|B_3_Mode_Pin|B_2_VL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : cfg1_Pin cfg2_Pin cfg3_Pin buck_mosfet_Pin
                           pure_mosfet_Pin */
  GPIO_InitStruct.Pin = cfg1_Pin|cfg2_Pin|cfg3_Pin|buck_mosfet_Pin
                          |pure_mosfet_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	uint32_t curr_tick = HAL_GetTick();
	if(curr_tick - prev_tick > 500)
	{
		prev_tick = HAL_GetTick();
		if(GPIO_Pin == B_1_OP_OnOff_Pin)
		{
			toggle_output();
			//print_output();
		//print_data();
		}

		else if(GPIO_Pin == B_2_VL_Pin)
		{
			set_pure_mosfet(OFF);
			set_buck_mosfet(OFF);
			Output = OutputOff;
			toggle_voltage_level();
			//print_data();


		}

		else if(GPIO_Pin == B_3_Mode_Pin)
		{
			set_pure_mosfet(OFF);
			set_buck_mosfet(OFF);
			Output = OutputOff;
			toggle_mode();
			//print_mode();
			//print_data();

		}
	}
}

static void set_pure_mosfet(uint8_t val)
{
	if(val == ON)
	{
		HAL_GPIO_WritePin(pure_mosfet_GPIO_Port, pure_mosfet_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(pure_mosfet_GPIO_Port, pure_mosfet_Pin, GPIO_PIN_RESET);
	}
}

static void set_buck_mosfet(uint8_t val)
{
	if(val == ON)
	{
		HAL_GPIO_WritePin(buck_mosfet_GPIO_Port, buck_mosfet_Pin, GPIO_PIN_SET);

	}
	else
	{
		HAL_GPIO_WritePin(buck_mosfet_GPIO_Port, buck_mosfet_Pin, GPIO_PIN_RESET);
	}
}

static void toggle_output(void)
{

	switch(Output)
	{
	case OutputOff:
		Output = OutputOn;
		break;
	default:
		Output = OutputOff;
		break;
	}


	if(Output == OutputOn)
	{
		if(Mode == Mode2)
		{
			set_pure_mosfet(OFF);
			set_buck_mosfet(ON);
		}
		else
		{
			set_buck_mosfet(OFF);
			set_pure_mosfet(ON);
		}

	}
	else
	{
		set_buck_mosfet(OFF);
		set_pure_mosfet(OFF);
	}
}

static void toggle_mode(void)
{
	if(Mode == Mode1)
	{
		Mode = Mode2;
	}
	else
	{
		Mode = Mode1;
	}
}

static void toggle_voltage_level(void)
{
	switch(Voltage)
	{
	case Five:
		Voltage = Nine;
		cfg.cfg1 = CFGRESET;
		cfg.cfg2 = CFGRESET;
		cfg.cfg3 = CFGRESET;
		break;

	case Nine:
		Voltage = Twelve;
		cfg.cfg1 = CFGRESET;
		cfg.cfg2 = CFGRESET;
		cfg.cfg3 = CFGSET;
		break;

	case Twelve:
		Voltage = Fifteen;
		cfg.cfg1 = CFGRESET;
		cfg.cfg2 = CFGSET;
		cfg.cfg3 = CFGSET;
		break;

	case Fifteen:
		Voltage = Twenty;
		cfg.cfg1 = CFGRESET;
		cfg.cfg2 = CFGSET;
		cfg.cfg3 = CFGRESET;
		break;

	case Twenty:
		Voltage = Five;
		cfg.cfg1 = CFGSET;
		cfg.cfg2 = CFGSET;
		cfg.cfg3 = CFGSET;
		break;
	}
	set_decoy_voltage((config_pins_state *)&cfg);

}

static void set_decoy_voltage(config_pins_state *conf)
{
	HAL_GPIO_WritePin(cfg1_GPIO_Port, cfg1_Pin, (conf->cfg1));
	HAL_GPIO_WritePin(cfg2_GPIO_Port, cfg2_Pin, (conf->cfg2));
	HAL_GPIO_WritePin(cfg3_GPIO_Port, cfg3_Pin, (conf->cfg3));
}

static void print_data(void)
{
	SSD1306_Clear();
	char *output_pbuff;
	if(Output == OutputOn) {output_pbuff = "ON";}
	else {output_pbuff = "OFF";}
	SSD1306_Print15X(95, 0, output_pbuff);

	char *mode_pbuff;
	if(Mode == Mode1) {mode_pbuff = "MODE1";}
	else if(Mode == Mode2) {mode_pbuff = "Mode2";}
	SSD1306_Print15X(0, 0, mode_pbuff);

	char vbuff[16];
	char cbuff[16];
	char powbuff[16];
	float voltage = INA226_ReadBusVoltage();

	float current = (INA226_ReadCurrent());

	float power   = (INA226_ReadPower());

	sprintf(vbuff, "%.4f V", voltage);
	sprintf(cbuff, "%.4f A", current);
	sprintf(powbuff, "%.4f W", power);
	SSD1306_Print2X(0, 14, vbuff);
	SSD1306_Print2X(0, 32, cbuff);
	SSD1306_Print2X(0, 50, powbuff);
	SSD1306_Update();

}

static void print_output(void)
{
	char *output_pbuff;
	if(Output == OutputOn) output_pbuff = "ON"; output_pbuff = "OFF";
	SSD1306_Print15X(95, 0, output_pbuff);
	SSD1306_Update();
}

static void print_mode(void)
{
	char *mode_pbuff;
	if(Mode == Mode1) {mode_pbuff = "MODE1";}
	else if(Mode == Mode2) {mode_pbuff = "Mode2";}
	SSD1306_Print15X(0, 0, mode_pbuff);
	SSD1306_Update();
}

static void print_voltage_current_power(void)
{
	char vbuff[16];
	char cbuff[16];
	char powbuff[16];
	INA226_Init();
	float voltage = INA226_ReadBusVoltage();
	float current = INA226_ReadCurrent();
	float power   = INA226_ReadPower();

	sprintf(vbuff, "%.3f V", voltage);
	sprintf(cbuff, "%.3f A", current);
	sprintf(powbuff,"%.3f W", power);
	SSD1306_Print2X(0, 14, vbuff);
	SSD1306_Print2X(0, 32, vbuff);
	SSD1306_Print2X(0, 50, powbuff);
	SSD1306_Update();
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
