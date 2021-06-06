//
// Created by Apple on 2021/6/6.
//

#ifndef STM32_FLASH_H
#define STM32_FLASH_H

#include "stm32f1xx_hal.h"

/**
 * @brief 编程Flash（需提前擦除Flash）
 *
 * @param Address 地址
 * @param Data 要写入的数据
 * @return 执行结果，成功返回0
 */
HAL_StatusTypeDef FlashWrite(uint32_t Address, uint32_t Data);

/**
 * @brief 擦除Flash
 *
 * @param PageAddress Page地址
 * @param NumberPage 要擦除的Page数量
 * @return 擦除失败的地址，成功返回0xFFFFFFFF
 */
uint32_t FlashErase(uint32_t PageAddress, uint32_t NumberPage);

/**
 * @brief 读取lash
 *
 * @param Address 要读取的地址
 * @return uint32_t 读取的数据
 */
uint32_t FlashRead(uint32_t Address);

#endif //STM32_FLASH_H
