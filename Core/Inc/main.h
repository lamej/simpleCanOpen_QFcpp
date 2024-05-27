/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define CLK1_Pin GPIO_PIN_13
#define CLK1_GPIO_Port GPIOC
#define STRB1_Pin GPIO_PIN_14
#define STRB1_GPIO_Port GPIOC
#define DATA1_Pin GPIO_PIN_15
#define DATA1_GPIO_Port GPIOC
#define D_OVL_Pin GPIO_PIN_1
#define D_OVL_GPIO_Port GPIOC
#define PULL_UP_Pin GPIO_PIN_2
#define PULL_UP_GPIO_Port GPIOC
#define OVLO_Pin GPIO_PIN_3
#define OVLO_GPIO_Port GPIOC
#define OVLI_Pin GPIO_PIN_0
#define OVLI_GPIO_Port GPIOA
#define FR_Pin GPIO_PIN_1
#define FR_GPIO_Port GPIOA
#define E01_Pin GPIO_PIN_2
#define E01_GPIO_Port GPIOA
#define E02_Pin GPIO_PIN_3
#define E02_GPIO_Port GPIOA
#define E03_Pin GPIO_PIN_4
#define E03_GPIO_Port GPIOC
#define E04_Pin GPIO_PIN_5
#define E04_GPIO_Port GPIOC
#define E05_Pin GPIO_PIN_0
#define E05_GPIO_Port GPIOB
#define E06_Pin GPIO_PIN_1
#define E06_GPIO_Port GPIOB
#define E07_Pin GPIO_PIN_2
#define E07_GPIO_Port GPIOB
#define E08_Pin GPIO_PIN_10
#define E08_GPIO_Port GPIOB
#define E09_Pin GPIO_PIN_11
#define E09_GPIO_Port GPIOB
#define E10_Pin GPIO_PIN_12
#define E10_GPIO_Port GPIOB
#define E11_Pin GPIO_PIN_13
#define E11_GPIO_Port GPIOB
#define E12_Pin GPIO_PIN_14
#define E12_GPIO_Port GPIOB
#define E13_Pin GPIO_PIN_15
#define E13_GPIO_Port GPIOB
#define E14_Pin GPIO_PIN_6
#define E14_GPIO_Port GPIOC
#define E15_Pin GPIO_PIN_7
#define E15_GPIO_Port GPIOC
#define E16_Pin GPIO_PIN_8
#define E16_GPIO_Port GPIOC
#define CLK2_Pin GPIO_PIN_9
#define CLK2_GPIO_Port GPIOC
#define DATA2_Pin GPIO_PIN_8
#define DATA2_GPIO_Port GPIOA
#define STRB2_Pin GPIO_PIN_9
#define STRB2_GPIO_Port GPIOA
#define EC_Pin GPIO_PIN_10
#define EC_GPIO_Port GPIOA
#define SOP2_Pin GPIO_PIN_15
#define SOP2_GPIO_Port GPIOA
#define SOP1_Pin GPIO_PIN_10
#define SOP1_GPIO_Port GPIOC
#define SFP_Pin GPIO_PIN_11
#define SFP_GPIO_Port GPIOC
#define SW1_Pin GPIO_PIN_12
#define SW1_GPIO_Port GPIOC
#define FLI_Pin GPIO_PIN_2
#define FLI_GPIO_Port GPIOD
#define PCL_Pin GPIO_PIN_3
#define PCL_GPIO_Port GPIOB
#define FLO_Pin GPIO_PIN_4
#define FLO_GPIO_Port GPIOB
#define FD_Pin GPIO_PIN_5
#define FD_GPIO_Port GPIOB
#define G2_Pin GPIO_PIN_6
#define G2_GPIO_Port GPIOB
#define GNG_Pin GPIO_PIN_8
#define GNG_GPIO_Port GPIOB
#define FM_Pin GPIO_PIN_9
#define FM_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
