#define __MSP430G2553__
#include <msp430.h> 

/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // 关闭看门狗定时器
    /*初始化LED2所在IO口P1.6为输出*/
    P1DIR |= BIT6;

    /*初始化LED2所在IO口P1.6为低电平，LED2初始状态为灭*/
    P1OUT &= ~BIT6;

    /*初始化按键所在IO口P1.3为输入*/
    P1DIR &= ~BIT3;

    /*使能P1.3口的上拉电阻*/
    P1REN |= BIT3;
    P1OUT |= BIT3;

    /*打开P1.3口中断*/
    P1IE |= BIT3;

    /*设定为下降沿触发*/
    P1IES |= BIT3;

    /*清除中断标志位*/
    P1IFG &= ~BIT3;

    /*打开全局中断*/
    __bis_SR_register(GIE);

    while(1);
}

#pragma vector = PORT1_VECTOR // 中断向量，从msp430g2553.h中找。PORT1_VECTOR为P1端口的中断向量。
__interrupt void Port1_ISR(void)  // 中断服务函数
{
    if(P1IFG & BIT3)// 判断是否是P1.3产生中断
    {
        P1IFG &= ~BIT3; // 清除标志位
        P1OUT ^= BIT6; // LED0改变一次亮灭状态
    }
}
