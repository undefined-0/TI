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
//OLED IIC接线
//                P1.5（SCL）
//                P1.4（SDA）
 int main(void)
 {
        WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
        BCSCTL1 = CALBC1_8MHZ; DCOCTL = CALDCO_8MHZ;   //设置到8Mhz

        _delay_cycles(1000);    //等待稳定

        OLED_Init();            //初始化OLED
        OLED_Clear();


//        OLED_ShowCHinese(54,0,3);//电
//        OLED_ShowCHinese(72,0,4);//子

        //循环显示
        while(1)
        {
            /*-------------
             * 1.显示数字2024
             *------------*/
            // OLED_Clear();
            // OLED_ShowNum(16, 0, 2024, 4, 16);
            // OLED_ShowNum(16, 2, 2024, 4, 16);
            // OLED_ShowNum(16, 4, 2024, 4, 16);
            // OLED_ShowNum(16, 6, 2024, 4, 16);
            // delayMs(1000);
            // /*-------------
            //  * 2.显示数字1.0
            //  *------------*/
            // OLED_Clear();
            // char the_floatNum[] = "1.0";
            // OLED_ShowString(60,0,the_floatNum,16);//如果要修改数字，eg 显示 9 :the_floatNum[0] = 9+'0';
            // delayMs(1000);
            // /*-------------
            //  * 3.显示NUEDC Contest
            //  *------------*/
            // OLED_Clear();
            // OLED_ShowString(0,0,"NUEDC Contest",16);
            // delayMs(1000);
            // /*-------------
            //  * 4.显示汉字 全国大学生电子设计竞赛培训网
            //  *------------*/
            // OLED_Clear();
            // OLED_ShowCHinese(0,0,0);//全
            // OLED_ShowCHinese(16,0,1);//国
            // OLED_ShowCHinese(32,0,2);//大
            // OLED_ShowCHinese(48,0,3);//学
            // OLED_ShowCHinese(64,0,4);//生
            // OLED_ShowCHinese(80,0,5);//电
            // OLED_ShowCHinese(96,0,9);//…
            // OLED_ShowCHinese(112,0,10);//网
            // 限于屏幕尺寸，显示不全
            // delayMs(1000);
             /*-------------
             * 5.显示图片 电赛的徽章LOGO
             *------------*/
            //OLED_Clear();
            // 第三个参数要改成图片宽度
            OLED_DrawBMP(30,0,101,7,longtu);
            // delayMs(1000);
             /*-------------
             * 6.根据屏幕显示特色信息
             *------------*/
            // OLED_Clear();
            // OLED_ShowString(0,0,"NUEDC!!",16);
            // delayMs(1000);
        }


}
