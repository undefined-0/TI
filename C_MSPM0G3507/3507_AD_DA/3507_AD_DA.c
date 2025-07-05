/**
 * 本工程功能简介：ADC采样，DAC将AD采样结果原样输出
 * 参数：10kHz采样率。（采样1k的正弦波，一个周期10个点）
 * ADC用信号发生器输入：PA27 channel 0
 * DAC用示波器输出：PA15
 */

#include "ti_msp_dl_config.h"

volatile bool gCheckADC;
volatile uint16_t gAdcResult;
uint32_t DAC_value;

#define DAC12_FULL (4095)

int main(void)
{
    SYSCFG_DL_init();

    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
    gCheckADC = false;
    
    DL_DAC12_output12(DAC0, DAC_value);
    DL_DAC12_enable(DAC0);

    while (1) {
        DL_ADC12_startConversion(ADC12_0_INST);
        DL_DAC12_output12(DAC0, DAC_value);
        while (false == gCheckADC) {
            //__WFE();
        }

        gAdcResult = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);
        //DAC_value = (gAdcResult * 4095) / DAC12_FULL;
        gCheckADC = false;
        DL_ADC12_enableConversions(ADC12_0_INST);
    }
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
            gCheckADC = true;
            //DAC_value = (gAdcResult * 4095) / DAC12_FULL;
            DAC_value = gAdcResult * 4095;
            break;
        default:
            break;
    }
}
