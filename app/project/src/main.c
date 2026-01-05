/* add user code begin Header */
/**
 **************************************************************************
 * @file     main.c
 * @brief    main program
 **************************************************************************
 *                       Copyright notice & Disclaimer
 *
 * The software Board Support Package (BSP) that is made available to
 * download from Artery official website is the copyrighted work of Artery.
 * Artery authorizes customers to use, copy, and distribute the BSP
 * software and its related documentation for the purpose of design and
 * development in conjunction with Artery microcontrollers. Use of the
 * software is governed by this copyright notice and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
 * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
 * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
 * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
 * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 **************************************************************************
 */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "at32f415_wk_config.h"
#include "wk_adc.h"
#include "wk_crc.h"
#include "wk_debug.h"
#include "wk_spi.h"
#include "wk_tmr.h"
#include "wk_usart.h"
#include "wk_wdt.h"
#include "wk_dma.h"
#include "wk_gpio.h"
#include "wk_system.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include "tmt.h"
#include "lcd_handle.h"
#include "key_handle.h"
#include "beep_handle.h"
#include "output_handle.h"
#include "flash_handle.h"
#include "work_handle.h"
#include "at32_spiflash.h"
#include "PID_operation.h"
#include "HA01_handle.h"
#include "ec11_handle.h"
#include "lcd.h"
#include "adc_filter.h"
//#include "perf_counter.h"
//#include "EventRecorder.h"
/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */

/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */
uint8_t beep_flag = 0;

extern uint16_t last_pid_out;
extern uint16_t pid_out;
/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */
void key_task(void);
void beep_task(void);
void lcd_task(void);
void output_task(void);
void debug_task(void);
void flash_task(void);
void work_task(void);
void ec11_task(void);
/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief main function.
  * @param  none
  * @retval none
  */
int main(void)
{
#if 1
  /* add user code begin 1 */
	nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x4000);
  /* add user code end 1 */

  /* system clock config. */
  wk_system_clock_config();

  /* config periph clock. */
  wk_periph_clock_config();

  /* init debug function. */
  wk_debug_config();

  /* nvic config. */
  wk_nvic_config();

  /* timebase config. */
  wk_timebase_init();

  /* init gpio function. */
  wk_gpio_config();

  /* init dma1 channel1 */
  wk_dma1_channel1_init();
  /* config dma channel transfer parameter */
  /* user need to modify define values DMAx_CHANNELy_XXX_BASE_ADDR and DMAx_CHANNELy_BUFFER_SIZE in at32xxx_wk_config.h */
  wk_dma_channel_config(DMA1_CHANNEL1, 
                        DMA1_CHANNEL1_PERIPHERAL_BASE_ADDR, 
                        DMA1_CHANNEL1_MEMORY_BASE_ADDR, 
                        DMA1_CHANNEL1_BUFFER_SIZE);
  dma_channel_enable(DMA1_CHANNEL1, TRUE);

  /* init usart1 function. */
  wk_usart1_init();

  /* init spi1 function. */
  wk_spi1_init();

  /* init adc1 function. */
  wk_adc1_init();

  /* init tmr2 function. */
  wk_tmr2_init();

  /* init tmr5 function. */
  wk_tmr5_init();

  /* init crc function. */
  wk_crc_init();

  /* init wdt function. */
  wk_wdt_init();

  /* add user code begin 2 */
  /* 优化方向：1.提高定时器分辨率 2.更换合适滤波算法 3.让小数点参与到运算中,减少输入误差 */
//  PID_Init(&handle_pid,1000,4,33000, MAX_PWM_OUTPUT);
  PID_Init(&handle_pid,800,3,20000, MAX_PWM_OUTPUT);

  tmt_init();
  
    
  /* 读取W25Q128 ID */
  tmt.create(lcd_task, LCD_HANDLE_TIME);
  tmt.create(output_task, OUTPUT_HANDLE_TIME);
  tmt.create(flash_task, FLASH_HANDLE_TIME);
  tmt.create(work_task, WORK_HANDLE_TIME);
//  tmt.create(ec11_task, EC11_TASK_TIME);
  tmt.create(beep_task, BEEP_TASK_TIME);
  tmt.create(key_task, KEY_HANDLE_TIME);
  filter_init(&handle_temp, ADC_CHANNEL_10);
  FWHA01_Init(&sFWHA01_t);
  LCD_Init(); 
  TranferPicturetoTFT_LCD(0, 0, 480, 320, LOGO);
   TranferPicturetoTFT_LCD(0, 0, 480, 320, LOGO);
  /* 等待系统上电稳定延时 */
  wk_delay_ms(1000);
#endif
  /* add user code end 2 */

  while(1)
  {
    /* add user code begin 3 */
	tmt.run();
    /* add user code end 3 */
  }
}

  /* add user code begin 4 */
void key_task(void)
{
    if (sFWHA01_t.init_flag)
        key_handle();
}


void ec11_task(void)
{
	ec11_handle();
}

void beep_task(void)
{
    static uint8_t warning_time = 0;
    if (sFWHA01_t.speak_state == SPEAKER_OPEN)
    {
        beep_handle();
    }
    else if (sFWHA01_t.speak_state == SPEAKER_CLOSE)
    {
        sbeep.off();
    }
	
	if(sFWHA01_t.handle_error_state != HANDLE_OK)
	{
	     if(warning_time++ == 50)
		 {
		     warning_time = 0;
			 sbeep.cmd = BEEP_LONG;
		 }
	}
}

void lcd_task(void)
{
#if 1
	if (sFWHA01_t.init_flag)
		LcdProc();
#endif
}

void output_task(void)
{
#if 1
    if (sFWHA01_t.init_flag)
		output_handle();
#endif
}

void debug_task(void)
{
    //printf("%d,%d,%d\n", pid_out, actual_temp, set_temp);
}

void flash_task(void)
{
	#if 1
    FlashProc();
	#endif
}

void work_task(void)
{
	#if 0
    WorkProc();
	#endif
}
/* add user code end 4 */
