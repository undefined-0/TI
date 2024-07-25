#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	/*ע���Ⱥ��ұߵĺ궨�嶼��msp430g2553.h�б�����*/

	/*����ϵͳʱ�� ����DCOΪ1MHz*/
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;

	/*����SMCLK��ʱ��ԴΪDCO*/
	BCSCTL2 &= ~SELS; // ϵͳ��λʱ��λ��Ϊ0��ʵ���ϲ���Ҫ���þ��Ѿ�ѡ����SMCLK��DCO����

	/*����SMCLK�ķ�Ƶϵ��Ϊ1*/
	BCSCTL2 &= ~(DIVS0 | DIVS1); // ��BCSCTL2�ĵ�һλ�͵ڶ�λ����Ϊ00������Ƶϵ��ѡ��1

	/*��λUSCI_Ax*/
	UCA0CTL1 |= UCSWRST;

	/*��Ϊ��UART��ѡ��USCI_AxΪ�첽ģʽ*/
	UCA0CTL0 &= ~UCSYNC; // ϵͳ��λʱ��λ��Ϊ0��ʵ���ϲ���Ҫ���þ��Ѿ�ѡ�����첽ģʽ��

	/*����UARTʱ��ԴΪSMCLK*/
	UCA0CTL1 |= UCSSEL1;
	
	/*���ò�����Ϊ9600*/
	UCA0BR0 = 0x68; // 16���Ƶ�104�������������û��ֲᲨ�������ñ��
	UCA0BR1 = 0x00;
	UCA0MCTL = 1<<1; // 1����һλ��ʹUCBRS1Ϊ1

	/*ʹ�ܶ˿ڸ���*/
	P1SEL |= BIT1 + BIT2;
	P1SEL2 |= BIT1 + BIT2;

	/*���㸴λλ��ʹ��UART*/
	UCA0CTL1 &= ~UCSWRST;

	P1DIR |= BIT0; //��ʼ��LED1����IO��P1.0Ϊ���ģʽ
	P1OUT |= BIT0; //����LED1

	while(1)
	{
		UCA0TXBUF = 0x55; // ��Ҫ���͵�����д�뷢�ͻ���Ĵ���
		__delay_cycles(500000); // �ӳ�Լ500ms
		P1OUT ^= 0x01;
	}
	return 0;
}
