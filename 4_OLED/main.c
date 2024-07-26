#define __MSP430G2553__
#include <msp430.h> 

#include "oled.h"
#include "bmp.h"

#define SYS_CLK 8000000
void delayMs(unsigned int mst)
{
    while(mst--)
    {
        __delay_cycles(SYS_CLK/1000);
    }
}
//OLED IIC����
//                P1.5��SCL��
//                P1.4��SDA��
 int main(void)
 {
        WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
        BCSCTL1 = CALBC1_8MHZ; DCOCTL = CALDCO_8MHZ;   //���õ�8Mhz

        _delay_cycles(1000);    //��һ������ȶ�

        OLED_Init();            //��ʼ��OLED
        OLED_Clear();


//        OLED_ShowCHinese(54,0,3);//��
//        OLED_ShowCHinese(72,0,4);//��

        //ѭ����ʾ
        while(1)
        {
            //��ʵ��ʾ���ֶ��������ַ����ķ�ʽ�����sprintf�����ֶ���䣬����Դ����ĵ�Ƭ���������ֱ��sprintf
            /*-------------
             * 1.��ʾ����2024
             *------------*/
            // OLED_Clear();
            // OLED_ShowNum(16, 0, 2024, 4, 16);
            // OLED_ShowNum(16, 2, 2024, 4, 16);
            // OLED_ShowNum(16, 4, 2024, 4, 16);
            // OLED_ShowNum(16, 6, 2024, 4, 16);
            // delayMs(1000);
            // /*-------------
            //  * 2.��ʾ����1.0
            //  *------------*/
            // //��Ҫ�������޸���ʾ���ֺ����ɿ�����ʾС��֧���ʴ�,���ҵ�Ȼ���ʴɵ�����
            // //����������,sometimesռ��Դ��������simple������Ȱ���ǰ�-��-
            // OLED_Clear();
            // char the_floatNum[] = "1.0";
            // OLED_ShowString(60,0,the_floatNum,16);//���Ҫ�޸����֣�eg ��ʾ 9 :the_floatNum[0] = 9+'0';
            // delayMs(1000);
            // /*-------------
            //  * 3.��ʾNUEDC Contest
            //  *------------*/
            // OLED_Clear();
            // OLED_ShowString(0,0,"NUEDC Contest",16);
            // delayMs(1000);
            // /*-------------
            //  * 4.��ʾ���� ȫ����ѧ��������ƾ�����ѵ��
            //  *------------*/
            // //û�ֿ����̫��Ϊ������,��ʵ����,�ǲ��Ƽ�������ʾ��������ĵ�,
            // //��ʵҪ����Դ��,�Ҿʹ��ͼƬ�ˣ���Ϊʲô������Դ��һ��ĵ�Ƭ���أ���Ϊ������
            // OLED_Clear();
            // OLED_ShowCHinese(0,0,0);//ȫ
            // OLED_ShowCHinese(16,0,1);//��
            // OLED_ShowCHinese(32,0,2);//��
            // OLED_ShowCHinese(48,0,3);//ѧ
            // OLED_ShowCHinese(64,0,4);//��
            // OLED_ShowCHinese(80,0,5);//��
            // OLED_ShowCHinese(96,0,9);//��
            // OLED_ShowCHinese(112,0,10);//��
            // //Ŷ������Ϊʲô��ʾ��ȫ��������Ļ���������ʾ��ȫ������ƽ����д��ô�຺�ֵ���
            // delayMs(1000);
             /*-------------
             * 5.��ʾͼƬ �����Ļ���LOGO
             *------------*/
            //д��������ͻȻ������,Ϊʲô�Ҳ����ҵ��ſ��ʵ�LCD����
            //Ŷ��G2 flash̫С��
            //OLED_Clear();
            // ����������Ҫ�ĳ�ͼƬ���
            OLED_DrawBMP(30,0,101,7,longtu);
            // delayMs(1000);
             /*-------------
             * 6.������Ļ��ʾ��ɫ��Ϣ(����Ҿ���Ҳ�Ǻ͵�����صİɣ�
             *------------*/
            // OLED_Clear();
            // OLED_ShowString(0,0,"NUEDC!!",16);
            // delayMs(1000);
        }


}
