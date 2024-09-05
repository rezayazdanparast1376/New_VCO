#include "main.h"
#include "io_link.h"
#include "stm32h7b0xx.h"
#include "stm32h7xx_hal.h"
#include "../OtherLibs/RawBuffer.h"
#include "../configManager/configManager.h"

#include "stdbool.h"

void receive_all(void) {
    receive_analog();
    receive_usart();
}

#define MAX_ADC_SAMPLE 250
uint32_t adc_samples[MAX_ADC_SAMPLE] = {0};
// 3.276.750
void receive_analog(void) {
    uint64_t adc_value = 0;
    
    for (int sample_conter = 0; sample_conter < MAX_ADC_SAMPLE; sample_conter++) {
        adc_samples[sample_conter] = HAL_ADC_GetValue(&hadc1);
        if (adc_samples[sample_conter] > 65535) {
            adc_samples[sample_conter] = 65535;
        }
    }
    for (int sample_conter = 0; sample_conter < MAX_ADC_SAMPLE; sample_conter++) {
        adc_value += adc_samples[sample_conter];
    }
    adc_value = adc_value / MAX_ADC_SAMPLE;

    if (final_adc_value != adc_value) {
        final_adc_value = adc_value;
    }
}




bool uart1_recev_cmp = false;

void receive_usart(void) {
    if (uart1_recev_cmp == true) {
        uint32_t receive_number =  (RxData[3] << 0) | (RxData[2] << 8) | (RxData[1] << 16) | (RxData[0] << 24);
        if (receive_number <= 100) {
            pwm_factor = receive_number;
        }
        uart1_recev_cmp = false;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        uart1_recev_cmp = true;
    }
    //TODO: Implementation for other usart interface ...
}
