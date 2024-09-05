#include <stdint.h>
#include "../../configManager/configManager.h"
#include "../../OtherLibs/other_lib.h"
#include "vco.h"
#include "vco_config.h"


/**
 * @brief 
 * 
 *  F(pwm) = (F(cpu)) / (1 + ARR) (1 + Pre_Scaler)
 * 
 *  F(pwm) = 64MHz / (1 + ARR) (1 + 63)     ==>   F(pwm) = 1MHz / (1 + ARR) 
 * 
 */

void initialize_pwm_signal(void) {
    __HAL_TIM_SET_PRESCALER(&htim1, DEFAULT_PRE_SCALER);      //TIM1->PSC   = DEFAULT_PRE_SCALER;
    __HAL_TIM_SET_AUTORELOAD(&htim1, DEFAULT_ARR);            //TIM1->CCR1  = DEFAULT_CRR;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, DEFAULT_CRR);//TIM1->ARR   = DEFAULT_ARR;
}





uint32_t arr_final = 0;
uint32_t max_arr = 0;
uint64_t arr_counter1 = 0;
uint64_t arr_counter2 = 0;
void generate_pulse(void) {
    double arr_factor = rescale(final_adc_value, 0, 65535, 0, 65535);//for auto calibration
    arr_factor = rescale(arr_factor, 0, 65535, 1, 100);

    arr_final  = (10000) / arr_factor;// 10,000 to 100 with 100 step with 100 resulousion.
    if (max_arr < arr_final) {
        max_arr = arr_final;
    }
    

    if(TIM1->ARR != arr_final) {
        if ((arr_final % 2) == 1) {
            arr_final = arr_final + 1;
            if(TIM1->ARR != arr_final) {
                TIM1->ARR = arr_final;
                arr_counter1++;
            }
        }
        else {
            TIM1->ARR = arr_final;
            arr_counter2++;
        }
    }
    
    set_duty_cycle(pwm_factor);
}




uint64_t duty_cnt1 = 0;
uint64_t duty_cnt2 = 0;
uint32_t fainal_ccr1 = 0;
void set_duty_cycle(uint8_t __duty_factor) {
    if (__duty_factor > 100) {
        return;
    }

    uint32_t pre_arr = __HAL_TIM_GET_AUTORELOAD(&htim1);

    if (pre_arr > 2) {
        if ((pre_arr % 2) == 1) {
            TIM1->ARR = pre_arr + 1;
            TIM1->CCR1 = (TIM1->ARR * __duty_factor) / 100;
            duty_cnt1++;
        }
        else {
            fainal_ccr1 = (TIM1->ARR * __duty_factor) / 100;
            if (TIM1->CCR1 != fainal_ccr1) {
                TIM1->CCR1 = fainal_ccr1;
                duty_cnt2++;
            }
            
         
        }
    }
}

