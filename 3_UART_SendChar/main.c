#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	/*注：等号右边的宏定义都在msp430g2553.h中被定义*/

	/*配置系统时钟 配置DCO为1MHz*/
	DCOCTL = CAL_DCO_1MHZ
	BCSCTL1 = CAL_BC1_1MHZ

	/*配置SMCLK的时钟源为DCO*/
	BCSCTL2 &= ~SELS; // 系统复位时此位已为0，实际上不需要配置就已经选择了SMCLK从DCO来。

	/*配置SMCLK的分频系数为1*/
	BCSCTL2 &= ~(DIVS0 | DIVS1); // 将BCSCTL2的第一位和第二位配置为00，即分频系数选择1

	/*复位USCI_Ax*/
	UCA0CTL1 |= UCSWRST;

	/*因为是UART，选择USCI_Ax为异步模式*/
	UCA0CTL0 &= ~UCSYNC; // 系统复位时此位已为0，实际上不需要配置就已经选择了异步模式。

	/*配置UART时钟源为SMCLK*/
	UCA0CTL1 &= UCSSEL1;
	
	return 0;
}
