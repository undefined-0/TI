#define __MSP430G2553__
#include <msp430.h> 
#include "stdint.h" // Ϊ��ʹ��uint8_t�ȱ�������

/*ע���Ⱥ��ұߵĺ궨�������msp430g2553.h*/

/*
 * @fn:		void InitSystemClock(void)
 * @brief:	��ʼ��ϵͳʱ��
 * @para:	none
 * @return:	none
 * @comment:��ʼ��ϵͳʱ��
 */
void InitSystemClock(void)
{
	/*����ϵͳʱ�� ����DCOΪ1MHz*/
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;

	/*����SMCLK��ʱ��ԴΪDCO*/
	BCSCTL2 &= ~SELS; // ϵͳ��λʱ��λ��Ϊ0��ʵ���ϲ���Ҫ���þ��Ѿ�ѡ����SMCLK��DCO����

	/*����SMCLK�ķ�Ƶϵ��Ϊ1*/
	BCSCTL2 &= ~(DIVS0 | DIVS1); // ��BCSCTL2�ĵ�һλ�͵ڶ�λ����Ϊ00������Ƶϵ��ѡ��1
}

/*
 * @fn:		void InitUART(void)
 * @brief:	��ʼ�����ڣ��������ò����ʣ�����λ��У��λ��
 * @para:	none
 * @return:	none
 * @comment:��ʼ������
 */
void InitUART(void)
{
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
}

/*
 * @fn:		void UARTSendString(uint8_t *pbuff,uint8_t num)
 * @brief:	ͨ�����ڷ����ַ���
 * @para:	pbuff:ָ��Ҫ�����ַ�����ָ��
 * 			num:Ҫ���͵��ַ�����
 * @return:	none
 * @comment:ͨ�����ڷ����ַ���
 */
void UARTSendString(uint8_t *pbuff,uint8_t num)
{
	uint8_t i = 0;
	for(i = 0; i < num; i++)
	{
		while(UCA0STAT & UCBUSY); // ֻҪUCBUSY��Ϊ0����һ�ε�����û���꣩����һֱ�����ȴ�
		UCA0TXBUF = *(pbuff + i); // ������д�뷢�ͻ�������
	}
}

/*
 * @fn:		void PrintNumber(uint16_t num)
 * @brief:	������ת�����ַ�����ͨ�����ڷ���
 * @para:	num:����
 * @return:	none
 * @comment:������ת�����ַ�����ͨ�����ڷ���
 */
void PrintNumber(uint16_t num)
{
	uint8_t buff[6] = {0,0,0,0,0,'\n'}; // �������������洢�����͵�����ת���ɵ��ַ���
	uint8_t j = 0;
	for(j = 0; j < 5; j++)
	{
		buff[4 - j] = (uint8_t)(num % 10 + '0'); // ����ǰnum�����λȡ�����ŵ���������
		num /= 10; // ��num�����һλȥ��
	}
	UARTSendString(buff,6);
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	InitSystemClock();
	InitUART();

	P1DIR |= BIT0; //��ʼ��LED1����IO��P1.0Ϊ���ģʽ
	P1OUT |= BIT0; //����LED1

	while(1)
	{
		UARTSendString("NUEDC",5);
		__delay_cycles(500000);
		PrintNumber(12345);
		__delay_cycles(500000);
	}
	return 0;
}
