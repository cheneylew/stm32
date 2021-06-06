
#include "delay.h"

#define AHB_INPUT 72  //请按RCC中设置的AHB时钟频率填写到这里（单位MHz）
void delay_us(int us) { //us微秒级延时程序（参数值就是延时数，72MHz时的最大值是233015）
    if(us == 0) {return ;};
    SysTick->LOAD =AHB_INPUT*us; //重装计数器初值（当主频为72MHz时，72次为1微秒）
    SysTick->VAL = 0x00; //清空定时器的计数器
    SysTick->CTRL = 0x00000005;//时钟源HCLK，打开定时器
    while(!(SysTick->CTRL & 0x00010000));//等待计数到0
    SysTick->CTRL = 0x00000004; //关闭定时器
}

void delay_ms(int ms) {
    while(ms-- != 0) {
        delay_us(1000);
    }
}

void delay_s(int s) {
    while(s-- != 0) {
        delay_ms(1000);
    }
}
