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
#include "stm32f7xx_hal.h"

#include "stm32f7xx_ll_spi.h"
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_cortex.h"
#include "stm32f7xx_ll_rcc.h"
#include "stm32f7xx_ll_system.h"
#include "stm32f7xx_ll_utils.h"
#include "stm32f7xx_ll_pwr.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_dma.h"

#include "stm32f7xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

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
void WatchDog(void);
void Reset_Add_AlarmLog(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ENCODER_A_Pin GPIO_PIN_0
#define ENCODER_A_GPIO_Port GPIOA
#define ETH_PWR_DOWN_Pin GPIO_PIN_4
#define ETH_PWR_DOWN_GPIO_Port GPIOA
#define ETH_LINK_IN_Pin GPIO_PIN_5
#define ETH_LINK_IN_GPIO_Port GPIOA
#define ETH_RESET_Pin GPIO_PIN_6
#define ETH_RESET_GPIO_Port GPIOA
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define CPU_RUN_LED_Pin GPIO_PIN_11
#define CPU_RUN_LED_GPIO_Port GPIOF
#define SFlash_HOLD_Pin GPIO_PIN_15
#define SFlash_HOLD_GPIO_Port GPIOE
#define SFlash_WP_Pin GPIO_PIN_10
#define SFlash_WP_GPIO_Port GPIOB
#define SFlash_CE_Pin GPIO_PIN_12
#define SFlash_CE_GPIO_Port GPIOB
#define SFlash_SCK_Pin GPIO_PIN_13
#define SFlash_SCK_GPIO_Port GPIOB
#define SFlash_MISO_Pin GPIO_PIN_14
#define SFlash_MISO_GPIO_Port GPIOB
#define SFlash_MOSI_Pin GPIO_PIN_15
#define SFlash_MOSI_GPIO_Port GPIOB
#define USB_OTG_FAULT_Pin GPIO_PIN_8
#define USB_OTG_FAULT_GPIO_Port GPIOA
#define SD_DET_Pin GPIO_PIN_3
#define SD_DET_GPIO_Port GPIOD
#define OUT_ENB_Pin GPIO_PIN_6
#define OUT_ENB_GPIO_Port GPIOD
#define FPGA_RESET_Pin GPIO_PIN_11
#define FPGA_RESET_GPIO_Port GPIOG
#define FPGA_INT_Pin GPIO_PIN_15
#define FPGA_INT_GPIO_Port GPIOG
#define ENCODER_B_Pin GPIO_PIN_3
#define ENCODER_B_GPIO_Port GPIOB
#define CPU_FPGA_GPIO1_Pin GPIO_PIN_7
#define CPU_FPGA_GPIO1_GPIO_Port GPIOB
#define CPU_FPGA_GPIO2_Pin GPIO_PIN_0
#define CPU_FPGA_GPIO2_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
