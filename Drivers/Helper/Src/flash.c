//
// Created by Apple on 2021/6/6.
//

#include "flash.h"
#include "stm32f1xx_hal_flash.h"

/**
 * @brief 编程Flash（需提前擦除Flash）
 *
 * @param Address 地址
 * @param Data 要写入的数据
 * @return 执行结果，成功返回0
 */
HAL_StatusTypeDef FlashWrite(uint32_t Address, uint32_t Data) {
    FlashErase(Address, 1);
    //RCC_HSICmd(ENABLE);
    HAL_StatusTypeDef _status;
    /* 解锁Flash操作寄存器 */
    HAL_FLASH_Unlock();
    /**
    * FLASH_TYPEPROGRAM_WORD表示以字（32bit）为单位进行写入，除此之外，还有HALFWORLD, DOUBLEWORLD
    **/
    _status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data);
    HAL_FLASH_Lock();
    return _status;
}

/**
 * @brief 擦除Flash
 *
 * @param PageAddress Page地址
 * @param NumberPage 要擦除的Page数量
 * @return 擦除失败的地址，成功返回0xFFFFFFFF
 */
uint32_t FlashErase(uint32_t PageAddress, uint32_t NumberPage) {
    FLASH_EraseInitTypeDef herase;
    uint32_t _pageError;

    herase.TypeErase = FLASH_TYPEERASE_PAGES;	// 按页擦除
    herase.NbPages = NumberPage;				// 从起始地址开始，要擦除的页数
    herase.PageAddress = PageAddress;			// 页的起始地址

    HAL_FLASH_Unlock();
    HAL_FLASHEx_Erase(&herase, &_pageError);	// PageError为擦除失败时的地址，成功返回0xFFFFFFFF
    HAL_FLASH_Lock();
    return _pageError;
}

/**
 * @brief 读取lash
 *
 * @param Address 要读取的地址
 * @return uint32_t 读取的数据
 */
uint32_t FlashRead(uint32_t Address) { return *(uint32_t *)Address; }