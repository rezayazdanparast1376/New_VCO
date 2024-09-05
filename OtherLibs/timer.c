
#include "time.h"
#include <stdint.h>
#include "stm32h7xx_hal.h"


uint8_t time_factor_1ms   = 0;
uint8_t time_factor_10ms  = 0;
uint8_t time_factor_100ms = 0;
uint8_t time_factor_500ms = 0;
uint8_t time_factor_5s    = 0;


uint64_t time_per_mili_second = 0;//based 1 ms.


/* USER CODE BEGIN 4 */
/**
 * @brief Calling in every 1000us or 1ms.s
 * 
 * @param htim 
 */
void HAL_TIM_PeriodElapsedCallback(
    TIM_HandleTypeDef* htim
) {
    /// TODO: Securing a call for timer 2
    time_per_mili_second++;

    if((time_per_mili_second % 10) == 1) {
        time_factor_10ms = 1;
    }

    if ((time_per_mili_second % 100) == 1) {
        time_factor_100ms = 1;
    }
    
    if ((time_per_mili_second % 500) == 1) {
        time_factor_500ms = 1;
    }
    
    if ((time_per_mili_second % 5000) == 1) {
        time_factor_5s = 1;
    }
}



uint64_t myTime_ms(void) {
    return time_per_mili_second;
}




/**
 * @brief 
 * 
 * @return uint16_t 
 */
uint64_t myTime(void) {
    return (time_per_mili_second / 10);
}



void timing_routine(void) {
  if (time_factor_10ms == 1) {
      routine_10ms();
      time_factor_10ms = 0;
    }
    if (time_factor_100ms == 1) {
      routine_100ms();
      time_factor_100ms = 0;
    }
    if (time_factor_500ms == 1) {
      routine_500ms();
      time_factor_500ms = 0;
    }
    if (time_factor_5s == 1) {
      routine_5s();
      time_factor_5s = 0;
    }
}


