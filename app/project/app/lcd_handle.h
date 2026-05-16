#ifndef _LCD_HANDLE_H
#define _LCD_HANDLE_H
#include "lcd.h"

#define LCD_HANDLE_TIME               1
#define TEMP_REFRESH_TIME             300
#define ALARM_REFRESH_TIME            300
#define SET_TEMP_TIME                 300
#define SET_WIND_TIME                 250
#define SET_TIME_TIME                 250


#define CH_SAVE_TIME                  300



#define FIRST_START_TIME              500
#define CH_SET_TIME                   300

#define SET_ON_TIME                   300
#define SET_0FF_TIME                  300

#define SHOW_RESET_TIME               300

#define SUN_FLISH_TIME                500

#define COLD_REFRESH_TIME             600
#define DELAY_ENTER_COLD_MODE_TIME    700

#define FAN_DISPLAY_TIME              50


#define ERROR_FLISH_TIME              400

#define FLASH_COUNT                   4

#define CH_COUNT 3

#define REDUCE_TEMP 0
#define ADD_TEMP 1
#define PID_TEMP 2


// 先定义宏，统一管理刷屏区域，方便修改
#define LCD_FULL_SCREEN_X1      0
#define LCD_FULL_SCREEN_Y1      30
#define LCD_FULL_SCREEN_WIDTH   480
#define LCD_FULL_SCREEN_HEIGHT  290

typedef enum
{
	
    SHOW_INIT,
    SHOW_WIND_FLASH,
    SHOW_TEMP_ACTUAL,
    SHOW_TEMP_ACTUAL_FLOAT,
    SHOW_WIND_SET,
    SHOW_SUN,
    SHOW_ADJUST,
    SHOW_SPEKER,
    SHOW_TIMER,
    SHOW_TIME_SET,
    SHOW_DISPLAY_MODE,
    SHOW_SET_TIME,
} lcd_handle_t;



typedef struct
{
    uint16_t x1;
    uint16_t y1;
    uint16_t length;
    uint16_t winth;
} icon_t;


typedef struct
{
    uint16_t x;
    uint16_t y;
    float *num;
    uint8_t len;
    uint16_t fc;
    uint16_t bc;
    uint8_t sizey;
    uint8_t mode;
} number;

extern uint8_t cold_mode;           
extern uint16_t cold_mode_set_wind;  
extern int16_t set_calibration_temp;
extern uint8_t refresh_set_wind_flag;
extern uint8_t set_temp_flag;
extern uint16_t set_time;
extern uint8_t set_time_flag;
extern uint8_t time_countdown_flag;
extern int16_t countdown_time;
extern uint16_t actual_temp;
extern uint16_t set_temp;
extern uint16_t set_wind;
extern uint16_t set_temp_f;
extern uint8_t lock_mode;

extern uint8_t display_mode;
extern uint8_t speak_mode;
extern  uint8_t show_ch_value_flag;

extern uint8_t save_ch_flag;
extern uint8_t show_on_flag;
extern uint8_t show_off_flag;
extern uint8_t reset_flag;
extern uint16_t last_system_set_temp;
extern uint16_t last_system_set_wind;

extern uint16_t set_temp_ch1;
extern uint16_t set_wind_ch1;
extern uint16_t set_time_ch1;
extern uint16_t set_temp_ch2;
extern uint16_t set_wind_ch2;
extern uint16_t set_time_ch2;
extern uint16_t set_temp_ch3;
extern uint16_t set_wind_ch3;
extern uint16_t set_time_ch3;
extern uint16_t set_temp_ch4;
extern uint16_t set_wind_ch4;
extern uint16_t set_time_ch4;
extern uint8_t ch;

extern uint8_t set_speak_flag;
extern int16_t c;  // 用 -1 确保第一次刷新

extern  uint8_t first_draw;
extern uint8_t lock_temp_flag;
extern int temp_to_display;
extern float wind_to_display;

/* 显示校准温度值 */
extern int16_t external_temp;
extern int16_t external_temp_f;
extern uint8_t set_calibration_temp_flag;
extern uint8_t last_coldwind_state;
extern uint8_t actual_temp_refesh_time;
extern uint8_t actual_wind_refesh_time;
void LcdProc(void);

#endif
