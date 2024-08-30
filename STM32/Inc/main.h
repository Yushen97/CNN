/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define IWA_Pin GPIO_PIN_6
#define IWA_GPIO_Port GPIOF
#define IWC_Pin GPIO_PIN_7
#define IWC_GPIO_Port GPIOF
#define IWB_Pin GPIO_PIN_8
#define IWB_GPIO_Port GPIOF
#define IWD_Pin GPIO_PIN_9
#define IWD_GPIO_Port GPIOF
#define EIW0_Pin GPIO_PIN_0
#define EIW0_GPIO_Port GPIOC
#define EIW1_Pin GPIO_PIN_2
#define EIW1_GPIO_Port GPIOC
#define ADC_Pin GPIO_PIN_0
#define ADC_GPIO_Port GPIOA
#define EPRD0_Pin GPIO_PIN_1
#define EPRD0_GPIO_Port GPIOA
#define EPRD1_Pin GPIO_PIN_3
#define EPRD1_GPIO_Port GPIOA
#define DAC_Pin GPIO_PIN_4
#define DAC_GPIO_Port GPIOA
#define ENRD0_Pin GPIO_PIN_5
#define ENRD0_GPIO_Port GPIOA
#define ENRD1_Pin GPIO_PIN_7
#define ENRD1_GPIO_Port GPIOA
#define RDA_Pin GPIO_PIN_5
#define RDA_GPIO_Port GPIOC
#define RDB_Pin GPIO_PIN_1
#define RDB_GPIO_Port GPIOB
#define RDC_Pin GPIO_PIN_11
#define RDC_GPIO_Port GPIOF
#define RDD_Pin GPIO_PIN_13
#define RDD_GPIO_Port GPIOF
#define W_DIN_Pin GPIO_PIN_1
#define W_DIN_GPIO_Port GPIOG
#define SP0_Pin GPIO_PIN_7
#define SP0_GPIO_Port GPIOE
#define W_LE_Pin GPIO_PIN_8
#define W_LE_GPIO_Port GPIOE
#define SN0_Pin GPIO_PIN_9
#define SN0_GPIO_Port GPIOE
#define I_DIN_Pin GPIO_PIN_10
#define I_DIN_GPIO_Port GPIOE
#define SP1_Pin GPIO_PIN_11
#define SP1_GPIO_Port GPIOE
#define I_LE_Pin GPIO_PIN_12
#define I_LE_GPIO_Port GPIOE
#define SN1_Pin GPIO_PIN_13
#define SN1_GPIO_Port GPIOE
#define CLK_Pin GPIO_PIN_14
#define CLK_GPIO_Port GPIOE
#define SI0_Pin GPIO_PIN_10
#define SI0_GPIO_Port GPIOB
#define SP2_Pin GPIO_PIN_11
#define SP2_GPIO_Port GPIOB
#define SN2_Pin GPIO_PIN_12
#define SN2_GPIO_Port GPIOB
#define SI1_Pin GPIO_PIN_13
#define SI1_GPIO_Port GPIOB
#define SP3_Pin GPIO_PIN_14
#define SP3_GPIO_Port GPIOB
#define SI2_Pin GPIO_PIN_15
#define SI2_GPIO_Port GPIOB
#define SN3_Pin GPIO_PIN_8
#define SN3_GPIO_Port GPIOD
#define SI3_Pin GPIO_PIN_9
#define SI3_GPIO_Port GPIOD
#define VDDc3_Pin GPIO_PIN_5
#define VDDc3_GPIO_Port GPIOG
#define VDDc2_Pin GPIO_PIN_7
#define VDDc2_GPIO_Port GPIOG
#define VDDc1_Pin GPIO_PIN_6
#define VDDc1_GPIO_Port GPIOC
#define VDDc0_Pin GPIO_PIN_8
#define VDDc0_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
