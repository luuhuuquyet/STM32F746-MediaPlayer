#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"

#define LCD_FRAME_BUFFER          SDRAM_DEVICE_ADDR
#define RGB565_BYTE_PER_PIXEL     2
#define ARBG8888_BYTE_PER_PIXEL   4

static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);

int main(void)
{
    CPU_CACHE_Enable();
    HAL_Init();
    SystemClock_Config();

    // Set up the LCD
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FRAME_BUFFER);
    BSP_LCD_SetLayerVisible(LTDC_ACTIVE_LAYER, ENABLE);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayOn();

    for(;;)
    {
        char buffer[30] ;
        sprintf(buffer, "Quyet Luu is testing!") ;
        BSP_LCD_DisplayStringAtLine(0, (uint8_t *) buffer) ;
    }
}

/**
* @brief  System Clock Configuration
*         The system Clock is configured as follow :
*            System Clock source            = PLL (HSE)
*            SYSCLK(Hz)                     = 216000000
*            HCLK(Hz)                       = 216000000
*            AHB Prescaler                  = 1
*            APB1 Prescaler                 = 4
*            APB2 Prescaler                 = 2
*            HSE Frequency(Hz)              = 25000000
*            PLL_M                          = 25
*            PLL_N                          = 432
*            PLL_P                          = 2
*            PLL_Q                          = 9
*            VDD(V)                         = 3.3
*            Main regulator output voltage  = Scale1 mode
*            Flash Latency(WS)              = 7
* @param  None
* @retval None
*/
static void SystemClock_Config(void)
{
RCC_ClkInitTypeDef RCC_ClkInitStruct;
RCC_OscInitTypeDef RCC_OscInitStruct;

/* Enable HSE Oscillator and activate PLL with HSE as source */
RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
RCC_OscInitStruct.HSEState = RCC_HSE_ON;
RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
RCC_OscInitStruct.PLL.PLLM = 25;
RCC_OscInitStruct.PLL.PLLN = 432;
RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
RCC_OscInitStruct.PLL.PLLQ = 9;
HAL_RCC_OscConfig(&RCC_OscInitStruct);

/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
clocks dividers */
RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);

}

/**
* @brief  CPU L1-Cache enable.
* @param  None
* @retval None
*/
static void CPU_CACHE_Enable(void)
{
/* Enable I-Cache */
SCB_EnableICache();

/* Enable D-Cache */
SCB_EnableDCache();
}