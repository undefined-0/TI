#define __MSP430G2553__
#include <msp430.h> 

int main(void)
{
    volatile unsigned int i;
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
    P1DIR |= 0x01;                            // ��ʼ��LED1����IO��P1.0Ϊ���ģʽ

    while(1)
    {
        P1OUT ^= 0x01;                        // P1.0�ߵ͵�ƽ״̬��ת
        for (i=10000; i>0; i--);
  }
}
