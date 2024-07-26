// ע��ʹ�ñ�����ʱ����λ�������ԣ����͵������βҪ׷��\n����Ƭ�������������յ�
// ���ڱ������壨MSP430G2553 Launch Pad����P1.1��RX��P1.2��TX

#define __MSP430G2553__
#include <msp430.h> 
#include "stdint.h"
#include "string.h" // Ϊ��ʹ�����е�memset����������ַ���
uint8_t receive_cmd[20] = {0};//����Ϊ20��������������ڱ��洮������
uint8_t cmd_end_flag = 0;//���������־λ����Ϊ1��˵��һ�������������Ѿ��ɹ�����

/*
 * @fn:     void InitSystemClock(void)
 * @brief:  ��ʼ��ϵͳʱ��
 * @para:   none
 * @return: none
 * @comment:��ʼ��ϵͳʱ��
 */
void InitSystemClock(void)
{
    /*����DCOΪ1MHz*/
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    /*����SMCLK��ʱ��ԴΪDCO*/
    BCSCTL2 &= ~SELS;
    /*SMCLK�ķ�Ƶϵ����Ϊ1*/
    BCSCTL2 &= ~(DIVS0 | DIVS1);
}
/*
 * @fn:     void InitUART(void)
 * @brief:  ��ʼ�����ڣ����ò����ʡ�����λ��У��λ�ȣ�Ҳ���˴��ڽ����жϣ�
 * @para:   none
 * @return: none
 * @comment:��ʼ�����ڣ����˴��ڽ����ж�
 */
void InitUART(void)
{
    /*��λUSCI_Ax*/
    UCA0CTL1 |= UCSWRST;

    /*ѡ��USCI_AxΪUARTģʽ*/
    UCA0CTL0 &= ~UCSYNC;

    /*����UARTʱ��ԴΪSMCLK*/
    UCA0CTL1 |= UCSSEL1;

    /*���ò�����Ϊ9600@1MHz*/
    UCA0BR0 = 0x68;
    UCA0BR1 = 0x00;
    UCA0MCTL = 1 << 1;
    /*ʹ�ܶ˿ڸ���*/
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;

    /*�����λλ��ʹ��UART*/
    UCA0CTL1 &= ~UCSWRST;

    // ע������������һ��Ҫ���������λλ֮�󣬷�����Ч����
    //�����ж�����
    IE2 |= UCA0RXIE;
    //��ս����жϱ�־
    IFG2 &= ~UCA0RXIFG;
}
/*
 * @fn:     void UARTSendString(uint8_t *pbuff,uint8_t num)
 * @brief:  ͨ�����ڷ����ַ���
 * @para:   pbuff:ָ��Ҫ�����ַ�����ָ��
 *          num:Ҫ���͵��ַ�����
 * @return: none
 * @comment:ͨ�����ڷ����ַ���
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
 * @brief:  ��������ִ�к���
 * @para:   receive_cmd:ָ�򴮿�������ջ�������ָ��
 * @return: none
 * @comment:�жϴ����յ������ִ��
 */
void cmd_judge_execute(uint8_t *receive_cmd)
{
    // ����ĵ�һ���±�ֵ��Ԥ������������˴�Ϊ2��
    // ����ĵڶ����±�ֵ����Ҫ�������Ԥ��������ռ���ֽ���
    // ע���˴���Ԥ������֧�����ġ���Ԥ�������к������ģ�һ��������ռ�����ֽڣ������ж�ʱ��Ҫ�ж�ǰ��λ��
    const uint8_t preset_cmd[2][10] = {"LED1 ON","LED1 OFF"}; // Ԥ����������޸�

    if(receive_cmd[0] == preset_cmd[0][0] && receive_cmd[6] == preset_cmd[0][6])// ���յ�LED1 ON
    {
        UARTSendString("LED1 has been illuminated",26);
        P1OUT |= BIT0;
    }
    else if(receive_cmd[0] == preset_cmd[1][0] && receive_cmd[6] == preset_cmd[1][6])// ���յ�LED1 OFF
    {
        UARTSendString("LED1 has been turned off",25);
        P1OUT &= ~BIT0;
    }
    else
    {
        UARTSendString("Not a preset command",21);
    }
    memset(receive_cmd, 0, 20); // ��������������ֹ�´ν�������ʱ������ʶ��
}
/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    InitSystemClock();//��ʼ��ϵͳʱ��
    InitUART();//��ʼ������
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    __bis_SR_register(GIE);//��ȫ���ж�
    while(1)
    {
        if(cmd_end_flag)
        {
            cmd_end_flag = 0;//�����־λ����ֹ�ظ�ִ��
            cmd_judge_execute(receive_cmd);//�ж����ִ��
        }
    }
    return 0;
}

#pragma vector = USCIAB0RX_VECTOR // �ж�����
__interrupt void UART_Receive_ISR(void) // �жϷ�����
{
    static uint8_t i = 0; // ������������static���Σ��Ǿ�̬�ֲ��������洢�ڽ��̵�ȫ������������ʹ�������أ�����ֵҲ�ᱣ�ֲ��䡣��
    if(IFG2 & UCA0RXIFG) // ����Ƿ���USCI_A0�Ľ����жϣ���ΪUSCI_A0��USIC_B0�Ľ����жϹ���ͬһ����
    {
        IFG2 &= ~UCA0RXIFG;//�����־λ
        receive_cmd[i++] = UCA0RXBUF;//�������UCA0RXBUF�ǽ��ռĴ�����
        i %= 20;//��ֹi����20�����»�����������������ã�cnt<20ʱ��cntֵ���ֲ��䣻cnt=20ʱ��cnt�ͱ���Ϊ0��
        
        if(receive_cmd[i - 1] == '\n')//�����⵽������������Ի�����Ϊ���������
        // ����������Ϊ�涨�ġ����������if��䣬Ҳ���Խ������ַ���Ϊ��������
        {
            i = 0;//��λ������
            cmd_end_flag = 1;//����������
        }
    }
}
