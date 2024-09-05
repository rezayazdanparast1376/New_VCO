
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"



void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

void Error_Handler(void);

void routine_10ms(void);
void routine_100ms(void);
void routine_500ms(void);
void routine_5s(void);


/* Private defines -----------------------------------------------------------*/
#define LED_1_PC1_Pin GPIO_PIN_1
#define LED_1_PC1_GPIO_Port GPIOC
#define LED_2_PA2_Pin GPIO_PIN_2
#define LED_2_PA2_GPIO_Port GPIOA



#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
