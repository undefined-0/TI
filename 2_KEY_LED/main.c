#include <msp430.h> 

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    P1DIR |= BIT6; //初始化LED2所在IO口P1.6为输出模式
    P1OUT &= ~BIT6; //初始化LED2所在IO口P1.6为低电平（初始状态为熄灭）
    P1DIR &= ~BIT3; //初始化按键所在IO口P1.3为输入
    P1REN |= BIT3; // 使能
    P1OUT |= BIT3; // 上拉
    while(1)
    {
        if(P1IN & BIT3) //如果P1.3口为高电平，证明按键没被按下
        {
            P1OUT &= ~BIT6; //熄灭LED2
        }
        else
        {
            P1OUT |= BIT6; //点亮LED2
        }
    }
    return 0;
}
