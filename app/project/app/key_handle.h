#ifndef _KEY_HANDLE_H
#define _KEY_HANDLE_H
#include "key.h"
#include "lcd_handle.h"
#define KEY_HANDLE_TIME          30
#define HEL_TIME                 90

typedef enum
{
    TEMP_ADD_EVENT = 0,
    TEMP_ADD_FIVE_EVENT,
    TEMP_REDUCE_EVENT,
    TEMP_REDUCE_FIVE_EVENT,
    WIND_TIME_ADD_EVENT,
    WIND_TIME_ADD_FIVE_EVENT,
    WIND_TIME_REDUCE_EVENT,
    WIND_TIME_REDUCE_FIVE_EVENT,
    TIME_COUNTDOWN_EVENT,
    SET_TIME_EVENT,
    SET_CH1_EVENT,
    SET_CH2_EVENT,
    SET_CH3_EVENT,
    SET_CH4_EVENT,
    VALUE_RESET_EVENT,
	SYSTEM_RESET_EVENT,
    END_EVENT,

} handle_event;

void KeyProc(void);
void key_handle(void);
#endif
