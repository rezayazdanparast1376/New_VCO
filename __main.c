
#include "main.h"
#include "stdint.h"
#include "configManager/configManager.h"
#include "io_link.h"
#include "Algoritms/vco/vco.h"



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




/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {

    config_functions();

    while (1) {
      receive_all();
      generate_pulse();
    }

}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}




#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


