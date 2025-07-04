#define __MSP430G2553__
#include <msp430.h> 
#include "stdint.h" // 为了使用uint8_t等变量类型

/*注：等号右边的宏定义皆来自msp430g2553.h*/

/*
 * @fn:		void InitSystemClock(void)
 * @brief:	初始化系统时钟
 * @para:	none
 * @return:	none
 * @comment:初始化系统时钟
 */
void InitSystemClock(void)
{
	/*配置系统时钟 配置DCO为1MHz*/
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;

	/*配置SMCLK的时钟源为DCO*/
	BCSCTL2 &= ~SELS; // 系统复位时此位已为0，实际上不需要配置就已经选择了SMCLK从DCO来。

	/*配置SMCLK的分频系数为1*/
	BCSCTL2 &= ~(DIVS0 | DIVS1); // 将BCSCTL2的第一位和第二位配置为00，即分频系数选择1
}

/*
 * @fn:		void InitUART(void)
 * @brief:	初始化串口，包括设置波特率，数据位，校验位等
 * @para:	none
 * @return:	none
 * @comment:初始化串口
 */
void InitUART(void)
{
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
}

/*
 * @fn:		void UARTSendString(uint8_t *pbuff,uint8_t num)
 * @brief:	通过串口发送字符串
 * @para:	pbuff:指向要发送字符串的指针
 * 			num:要发送的字符个数
 * @return:	none
 * @comment:通过串口发送字符串
 */
void UARTSendString(uint8_t *pbuff,uint8_t num)
{
	uint8_t i = 0;
	for(i = 0; i < num; i++)
	{
		while(UCA0STAT & UCBUSY); // 只要UCBUSY不为0（上一次的数据没发完），就一直在这句等待
		UCA0TXBUF = *(pbuff + i); // 将数据写入发送缓冲器中
	}
}

/*
 * @fn:		void PrintNumber(uint16_t num)
 * @brief:	将变量转换成字符串，通过串口发送
 * @para:	num:变量
 * @return:	none
 * @comment:将变量转换成字符串，通过串口发送
 */
void PrintNumber(uint16_t num)
{
	uint8_t buff[6] = {0,0,0,0,0,'\n'}; // 缓冲区，用来存储待发送的数据转换成的字符串
	uint8_t j = 0;
	for(j = 0; j < 5; j++)
	{
		buff[4 - j] = (uint8_t)(num % 10 + '0'); // 将当前num的最低位取出来放到缓冲区中
		num /= 10; // 将num的最后一位去掉
	}
	UARTSendString(buff,6);
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	InitSystemClock();
	InitUART();

	P1DIR |= BIT0; //初始化LED1所在IO口P1.0为输出模式
	P1OUT |= BIT0; //点亮LED1

	while(1)
	{
		UARTSendString("NUEDC",5);
		__delay_cycles(500000);
		PrintNumber(12345);
		__delay_cycles(500000);
	}
	return 0;
}
