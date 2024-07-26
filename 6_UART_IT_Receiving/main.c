// 注：使用本程序时，上位机（电脑）发送的命令结尾要追加\n，单片机才能正常接收到
// 对于本开发板（MSP430G2553 Launch Pad），P1.1是RX，P1.2是TX

#define __MSP430G2553__
#include <msp430.h> 
#include "stdint.h"
#include "string.h" // 为了使用其中的memset函数来清空字符串
uint8_t receive_cmd[20] = {0};//长度为20的命令缓冲区，用于保存串口命令
uint8_t cmd_end_flag = 0;//命令结束标志位，若为1则说明一句完整的命令已经成功接收

/*
 * @fn:     void InitSystemClock(void)
 * @brief:  初始化系统时钟
 * @para:   none
 * @return: none
 * @comment:初始化系统时钟
 */
void InitSystemClock(void)
{
    /*配置DCO为1MHz*/
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    /*配置SMCLK的时钟源为DCO*/
    BCSCTL2 &= ~SELS;
    /*SMCLK的分频系数置为1*/
    BCSCTL2 &= ~(DIVS0 | DIVS1);
}
/*
 * @fn:     void InitUART(void)
 * @brief:  初始化串口（设置波特率、数据位、校验位等，也打开了串口接收中断）
 * @para:   none
 * @return: none
 * @comment:初始化串口，打开了串口接收中断
 */
void InitUART(void)
{
    /*复位USCI_Ax*/
    UCA0CTL1 |= UCSWRST;

    /*选择USCI_Ax为UART模式*/
    UCA0CTL0 &= ~UCSYNC;

    /*配置UART时钟源为SMCLK*/
    UCA0CTL1 |= UCSSEL1;

    /*配置波特率为9600@1MHz*/
    UCA0BR0 = 0x68;
    UCA0BR1 = 0x00;
    UCA0MCTL = 1 << 1;
    /*使能端口复用*/
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;

    /*清除复位位，使能UART*/
    UCA0CTL1 &= ~UCSWRST;

    // 注：下面这两行一定要放在清除复位位之后，否则无效！！
    //接收中断启用
    IE2 |= UCA0RXIE;
    //清空接收中断标志
    IFG2 &= ~UCA0RXIFG;
}
/*
 * @fn:     void UARTSendString(uint8_t *pbuff,uint8_t num)
 * @brief:  通过串口发送字符串
 * @para:   pbuff:指向要发送字符串的指针
 *          num:要发送的字符个数
 * @return: none
 * @comment:通过串口发送字符串
 */
void UARTSendString(uint8_t *pbuff,uint8_t num)
{
    uint8_t i = 0;
    for(i = 0;i < num;i ++)
    {
        while(UCA0STAT & UCBUSY);
        UCA0TXBUF = *(pbuff + i);
    }
}
/*
 * @fn:     void cmd_judge_execute(uint8_t *receive_cmd)
 * @brief:  串口命令执行函数
 * @para:   receive_cmd:指向串口命令接收缓冲区的指针
 * @return: none
 * @comment:判断串口收到的命令并执行
 */
void cmd_judge_execute(uint8_t *receive_cmd)
{
    // 数组的第一个下标值：预置命令个数（此处为2）
    // 数组的第二个下标值：需要大于最长的预置命令所占的字节数
    // 注：此处的预置命令支持中文。若预置命令中含有中文，一个中文字占两个字节，后续判断时需要判断前两位。
    const uint8_t preset_cmd[2][10] = {"LED1 ON","LED1 OFF"}; // 预置命令，可以修改

    if(receive_cmd[0] == preset_cmd[0][0] && receive_cmd[6] == preset_cmd[0][6])// 接收到LED1 ON
    {
        UARTSendString("LED1 has been illuminated",26);
        P1OUT |= BIT0;
    }
    else if(receive_cmd[0] == preset_cmd[1][0] && receive_cmd[6] == preset_cmd[1][6])// 接收到LED1 OFF
    {
        UARTSendString("LED1 has been turned off",25);
        P1OUT &= ~BIT0;
    }
    else
    {
        UARTSendString("Not a preset command",21);
    }
    memset(receive_cmd, 0, 20); // 清空命令缓存区，防止下次接收命令时产生误识别
}
/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    InitSystemClock();//初始化系统时钟
    InitUART();//初始化串口
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    __bis_SR_register(GIE);//打开全局中断
    while(1)
    {
        if(cmd_end_flag)
        {
            cmd_end_flag = 0;//清除标志位，防止重复执行
            cmd_judge_execute(receive_cmd);//判断命令并执行
        }
    }
    return 0;
}

#pragma vector = USCIAB0RX_VECTOR // 中断向量
__interrupt void UART_Receive_ISR(void) // 中断服务函数
{
    static uint8_t i = 0; // 计数变量（用static修饰，是静态局部变量，存储于进程的全局数据区。即使函数返回，它的值也会保持不变。）
    if(IFG2 & UCA0RXIFG) // 检测是否是USCI_A0的接收中断，因为USCI_A0和USIC_B0的接收中断共用同一向量
    {
        IFG2 &= ~UCA0RXIFG;//清除标志位
        receive_cmd[i++] = UCA0RXBUF;//保存命令。UCA0RXBUF是接收寄存器。
        i %= 20;//防止i大于20，导致缓冲区溢出（本句作用：cnt<20时，cnt值保持不变；cnt=20时，cnt就被置为0）
        
        if(receive_cmd[i - 1] == '\n')//如果检测到命令结束符（以换行作为命令结束）
        // 结束符是人为规定的。更改上面的if语句，也可以将其他字符作为结束符。
        {
            i = 0;//复位计数器
            cmd_end_flag = 1;//命令接收完毕
        }
    }
}
