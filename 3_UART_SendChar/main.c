#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	/*注：等号右边的宏定义都在msp430g2553.h中被定义*/

	/*配置系统时钟 配置DCO为1MHz*/
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;

	/*配置SMCLK的时钟源为DCO*/
	BCSCTL2 &= ~SELS; // 系统复位时此位已为0，实际上不需要配置就已经选择了SMCLK从DCO来。

	/*配置SMCLK的分频系数为1*/
	BCSCTL2 &= ~(DIVS0 | DIVS1); // 将BCSCTL2的第一位和第二位配置为00，即分频系数选择1

	/*复位USCI_Ax*/
	UCA0CTL1 |= UCSWRST;

	/*因为是UART，选择USCI_Ax为异步模式*/
	UCA0CTL0 &= ~UCSYNC; // 系统复位时此位已为0，实际上不需要配置就已经选择了异步模式。

	/*配置UART时钟源为SMCLK*/
	UCA0CTL1 |= UCSSEL1;
	
	/*配置波特率为9600*/
	UCA0BR0 = 0x68; // 16进制的104（此数据来自用户手册波特率配置表格）
	UCA0BR1 = 0x00;
	UCA0MCTL = 1<<1; // 1左移一位，使UCBRS1为1

	/*使能端口复用*/
	P1SEL |= BIT1 + BIT2;
	P1SEL2 |= BIT1 + BIT2;

	/*清零复位位，使能UART*/
	UCA0CTL1 &= ~UCSWRST;

	P1DIR |= BIT0; //初始化LED1所在IO口P1.0为输出模式
	P1OUT |= BIT0; //点亮LED1

	while(1)
	{
		UCA0TXBUF = 0x55; // 将要发送的数据写入发送缓冲寄存器
		__delay_cycles(500000); // 延迟约500ms
		P1OUT ^= 0x01;
	}
	return 0;
}
