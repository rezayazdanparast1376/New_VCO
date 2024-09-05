#ifndef _ADC_BUFF_H_
#define _ADC_BUFF_H_
#include <stdint.h>

#define MAX_ADC_FINAL_SAMPLE 250

typedef struct ADC_BUF_t {
    uint32_t    write;
    uint32_t    size;
    uint32_t*   data;
}ADC_BUF;



void adc_b_init(ADC_BUF* adc_buffer, uint32_t* buff_addr, uint32_t size);

void adc_b_push(ADC_BUF* adc_buffer, uint32_t adc_value);

uint32_t adc_b_avr(ADC_BUF* adc_buffer);


#endif //_ADC_BUFF_H_

