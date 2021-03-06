/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "delay.h"
#include "io.h"
#include "flash.h"
#include <string.h>
#include <stdio.h>

#define Key1Pin GPIO_PIN_8
#define Key2Pin GPIO_PIN_9
#define Key3Pin GPIO_PIN_10
#define Led0Pin GPIO_PIN_0
#define Led1Pin GPIO_PIN_1
#define Led2Pin GPIO_PIN_2
#define Led3Pin GPIO_PIN_3
#define Led4Pin GPIO_PIN_4

#define FLashStartAddr 0x08003000

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

uint8_t aTxStartMessages[] = "\r\n******UART commucition using IT******\r\nPlease enter 10 characters:";
uint8_t aRxBuffer[1];
#define MAX_RECV_LEN 1024
uint8_t MSG_BUFF[MAX_RECV_LEN] = {0};
uint16  MSG_LEGHT = 0;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_USART1_UART_Init();
    MX_GPIO_Init();
    uint32_t v = FlashRead(FLashStartAddr);
    HAL_GPIO_WritePin(GPIOA, Led0Pin, v);
    PAout(3) = 0;
    //??????????????????
    uint16_t size = sizeof(aRxBuffer);
    HAL_StatusTypeDef status = HAL_UART_Receive_IT(&huart1,(uint8_t*)aRxBuffer, 1);
    while (1) {
        if (!HAL_GPIO_ReadPin(GPIOB, Key1Pin)) {
            delay_ms(20);
            if (!HAL_GPIO_ReadPin(GPIOB, Key1Pin)) {
                GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, Led0Pin);
                uint32_t newState = 1 - state;
                HAL_GPIO_WritePin(GPIOA, Led0Pin, newState);
                HAL_StatusTypeDef s = FlashWrite(FLashStartAddr, newState);
                while (!HAL_GPIO_ReadPin(GPIOB, Key1Pin));

                //??????????????????
                HAL_UART_Transmit_IT(&huart1, (uint8_t *) aTxStartMessages, sizeof(aTxStartMessages));
            }
        }
    }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void) {
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitTypeDef GPIO_InitStruct_B = {0};
    GPIO_InitStruct_B.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct_B.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct_B.Pull = GPIO_PULLUP;
//    GPIO_InitStruct_B.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct_B);

    GPIO_InitTypeDef GPIO_InitStruct_BI = {0};
    GPIO_InitStruct_BI.Pin = GPIO_PIN_10;
    GPIO_InitStruct_BI.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct_BI.Pull = GPIO_PULLUP;
    GPIO_InitStruct_B.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct_BI);
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,0,0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* USER CODE BEGIN 4 */

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {

}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart) {

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    MSG_LEGHT++;
    MSG_BUFF[MSG_LEGHT-1] = aRxBuffer[0];
    HAL_StatusTypeDef status = HAL_OK;
    do {
        status = HAL_UART_Receive_IT(&huart1,(uint8_t*)aRxBuffer, 1);
    } while (status != HAL_OK);
    if (aRxBuffer[0] == '\r') {
        MSG_BUFF[MSG_LEGHT-1] = '\r';
        MSG_BUFF[MSG_LEGHT] = '\n';
        HAL_UART_Transmit(&huart1,(uint8_t*)MSG_BUFF, MSG_LEGHT,0xFFFF);//(uint8_t*)aRxBuffer?????????????????????10?????????????????????0xFFFF???????????????
        memset(MSG_BUFF, 0, MSG_LEGHT+1);
        MSG_LEGHT = 0;
    }
}

void EXTI15_10_IRQHandler(void)

{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    delay_ms(10);
    switch (GPIO_Pin) {
        case GPIO_PIN_10:
            ;
    };
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}
