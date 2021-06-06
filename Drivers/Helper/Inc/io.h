//
// Created by Apple on 2021/6/6.
//

#ifndef STM32_IO_H
#define STM32_IO_H

#include "stm32f1xx_hal.h"

#define uint8 unsigned          char
#define uint16 unsigned short     int
#define u16 unsigned short     int
#define uint32 unsigned           int
#define u32 unsigned           int
#define uint64 unsigned       __INT64

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //Êä³ö
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //ÊäÈë

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //Êä³ö
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //ÊäÈë

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //Êä³ö
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //ÊäÈë

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //Êä³ö
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //ÊäÈë

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //Êä³ö
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //ÊäÈë

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //Êä³ö
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //ÊäÈë

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //Êä³ö
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //ÊäÈë

#endif //STM32_IO_H
