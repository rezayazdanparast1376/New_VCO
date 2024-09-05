#ifndef _TIMER_H_
#define _TIMER_H_


#include <stdint.h>

extern uint8_t time_factor_1ms;
extern uint8_t time_factor_10ms;
extern uint8_t time_factor_100ms;
extern uint8_t time_factor_500ms;
extern uint8_t time_factor_5s;


void timing_routine(void);

uint64_t myTime_ms(void);




/**
 * @brief 
 * 
 * @return uint16_t 
 */
uint64_t myTime(void);



#endif// _TIMER_H_

