#define __MSP430G2553__
#include <msp430.h> 

int main(void)
{
    volatile unsigned int i;
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
    P1DIR |= 0x01;                            // 初始化LED1所在IO口P1.0为输出模式

    while(1)
    {
        P1OUT ^= 0x01;                        // P1.0高低电平状态翻转
        for (i=10000; i>0; i--);
  }
}
