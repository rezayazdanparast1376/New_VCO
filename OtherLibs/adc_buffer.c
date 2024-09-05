#include "adc_buffer.h"
#include <stdint.h>



void adc_b_init(ADC_BUF* adc_buffer, uint32_t* buff_addr, uint32_t size) {
    adc_buffer->size    = size;
    adc_buffer->write   = 1;
    adc_buffer->data    = buff_addr;
}




void adc_b_push(ADC_BUF* adc_buffer, uint32_t adc_value) {
    if (adc_buffer->write <= adc_buffer->size) {
        adc_buffer->data[adc_buffer->write - 1] = adc_value;
        adc_buffer->write++;
    }
    if (adc_buffer->write > adc_buffer->size) {
        adc_buffer->write = 1;
    }
}




uint32_t adc_b_avr(ADC_BUF* adc_buffer) {
    uint64_t sum = 0;
    for (uint32_t counter = 0; counter < adc_buffer->size; counter++) {
        sum = sum + adc_buffer->data[counter];
    }
    uint32_t avrage = sum / adc_buffer->size;
    return avrage;
}

