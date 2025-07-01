/**
 * 程序功能：使用AD采集外部电压（ADC0，channel 0，PA27输入），通过DA输出。
 * MSPM0L1306片内不含DA，故采用PWM（TIMG0，PWM channel 0，PA12输出）模拟DA。
 * 
 * 思路：12位AD输出结果ADC_val范围为0-4095，程序中设置PWM Period Count为4096，
 * 使用DL_TimerG_setCaptureCompareValue(PWM_0_INST, ADC_val, DL_TIMER_CC_0_INDEX); 函数，
 * 将ADC_val直接传入Counter Campare Value。
 * 这样，占空比Counter Campare Value/PWM Period Count即为ADC_val/4096，
 * 如此实现了AD采样电压值于PWM模拟DA原样输出。
 * 
 * 注：从PA27输入正弦波时，PA12处输出为占空比不断变化的PWM波。
 * 经二阶RC低通滤波器滤波后，输出结果为频率与PA27处相同的正弦波。
 * 缺点：超低频（f < 40Hz）时才能满足较小衰减，且相移明显。
 */

#include "ti/driverlib/dl_adc12.h"
#include "ti_msp_dl_config.h"

volatile bool ADC_flag;
volatile uint16_t ADC_val;


int main(void)
{
    SYSCFG_DL_init();

    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN); // 打开AD转换的中断
    DL_TimerG_startCounter(PWM_0_INST); // 打开PWM输出

    while (1) 
    {
        ADC_flag = false;
        DL_ADC12_startConversion(ADC12_0_INST); // 开始转换

        while (ADC_flag==false); // 等待转换完成

        ADC_val = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0); // 读取ADC值
        DL_TimerG_setCaptureCompareValue(PWM_0_INST, ADC_val, DL_TIMER_CC_0_INDEX); // 更改PWM占空比
        DL_ADC12_enableConversions(ADC12_0_INST); // 重新开启转换
    }
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
            ADC_flag = true;
            break;
        default:
            break;
    }
}