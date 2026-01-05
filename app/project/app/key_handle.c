#include "key_handle.h"
//#include "work_handle.h"
#include "PID_operation.h"
#include "HA01_handle.h"
#include "beep_handle.h"
extern uint8_t beep_flag;

static KEY_VALUE get_key_ch1()
{
    if (READ_CH1_KEY == 0)
    {
        return K_PRESS;
    }
    else
    {
        return K_RELEASE;
    }
}

static KEY_VALUE get_key_ch2()
{
    if (READ_CH2_KEY == 0)
    {
        return K_PRESS;
    }
    else
    {
        return K_RELEASE;
    }
}

static KEY_VALUE get_key_ch3()
{
    if (READ_CH3_KEY == 0)
    {
        return K_PRESS;
    }
    else
    {
        return K_RELEASE;
    }
}




static KEY keys[] =
{
    {KS_RELEASE, 0, KEY_CYCLE_TIME, get_key_ch1},
    {KS_RELEASE, 0, KEY_CYCLE_TIME, get_key_ch2},
    {KS_RELEASE, 0, KEY_CYCLE_TIME, get_key_ch3},
};

KEY_EVENT key_event[KEY_NUMBER] =
{
    KE_PRESS,
    KE_RELEASE,
    KE_LONG_PRESS,
//    KE_LONG_RELEASE,
    KE_NONE,
};


void KeyProc(void)
{
    for (uint8_t i = 0; i < KEY_NUMBER; i++)
    {
        key_event[i] = key_event_check(&keys[i], LONG_PRESS_TIME);
    }
}


void key_handle(void)
{
    static  handle_event event = END_EVENT;
    static uint8_t delay_time = 5;
    static uint16_t hel1_time = HEL_TIME;
    static uint8_t hel1_flag = FALSE;
    static uint8_t hel1_mode = 0;   //0:set temp  1:set wind
    static uint8_t set_done = FALSE;

//	if (    get_key_ch1()         == K_PRESS || \
//			get_key_ch2()         == K_PRESS || \
//			get_key_ch3()         == K_PRESS )
//	{
//		if (sFWHA01_t.Work_handle_state == HANDLE_SLEEP)
//		{
//			sFWHA01_t.Work_handle_state = HANDLE_WAKEN;
//			sFWHA01_t.system_parameter.waken_time_count = WAKEN_TIMES;
//		}
//		 else if (sFWHA01_t.Work_handle_state == HANDLE_WAKEN)
//		{
//			sFWHA01_t.system_parameter.waken_time_count = WAKEN_TIMES;
//		}
//	}

	if(set_done == TRUE)
	{
		set_done = FALSE;
	}
    KeyProc();
	
    /* 长按按键 */
    if (key_event[0] == KE_LONG_PRESS && set_done == FALSE )  //保存档位1数据
    {
		sFWHA01_t.system_parameter.ch1_set_temp = sFWHA01_t.system_parameter.set_temp;
		sFWHA01_t.system_parameter.ch1_set_air = sFWHA01_t.system_parameter.air_data; 
		sFWHA01_t.general_parameter.ch = 1;
		sFWHA01_t.system_parameter.last_ch1_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch2_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch3_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_air_data = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp_f_display = RESET_VALUE;
		sbeep.cmd = BEEP_LONG;
        set_done = TRUE;
		
    }
	if (key_event[1] == KE_LONG_PRESS && set_done == FALSE )  //保存档位2数据
    {
		sFWHA01_t.system_parameter.ch2_set_temp = sFWHA01_t.system_parameter.set_temp;
		sFWHA01_t.system_parameter.ch2_set_air = sFWHA01_t.system_parameter.air_data; 
		sFWHA01_t.general_parameter.ch = 2;
		sFWHA01_t.system_parameter.last_ch1_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch2_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch3_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_air_data = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp_f_display = RESET_VALUE;
		sbeep.cmd = BEEP_LONG;
        set_done = TRUE;
		
    }
	if (key_event[2] == KE_LONG_PRESS && set_done == FALSE )  //保存档位3数据
    {
		sFWHA01_t.system_parameter.ch3_set_temp = sFWHA01_t.system_parameter.set_temp;
		sFWHA01_t.system_parameter.ch3_set_air = sFWHA01_t.system_parameter.air_data; 
		sFWHA01_t.general_parameter.ch = 3;
		sFWHA01_t.system_parameter.last_ch1_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch2_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch3_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_air_data = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp_f_display = RESET_VALUE;
		sbeep.cmd = BEEP_LONG;
        set_done = TRUE;
    }
	
	/* 单击按键 */
	if (key_event[0] == KE_PRESS && set_done == FALSE )  //读取档位1数据
    {
		sFWHA01_t.system_parameter.set_temp = sFWHA01_t.system_parameter.ch1_set_temp;
		sFWHA01_t.system_parameter.air_data = sFWHA01_t.system_parameter.ch1_set_air; 
		sFWHA01_t.system_parameter.last_ch1_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch2_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch3_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_air_data = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp_f_display = RESET_VALUE;
		sFWHA01_t.general_parameter.ch = 1;
		sFWHA01_t.general_parameter.set_temp_time = SET_TEMP_SHOW_TIMES;
        set_done = TRUE;
		sbeep.cmd = BEEP_SHORT;
    }
	if (key_event[1] == KE_PRESS && set_done == FALSE )  //读取档位2数据
    {
		sFWHA01_t.system_parameter.set_temp = sFWHA01_t.system_parameter.ch2_set_temp;
		sFWHA01_t.system_parameter.air_data = sFWHA01_t.system_parameter.ch2_set_air; 
		sFWHA01_t.system_parameter.last_ch1_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch2_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch3_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_air_data = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp_f_display = RESET_VALUE;
		sFWHA01_t.general_parameter.ch = 2;
		sFWHA01_t.general_parameter.set_temp_time = SET_TEMP_SHOW_TIMES;
        set_done = TRUE;
		sbeep.cmd = BEEP_SHORT;
    }
	if (key_event[2] == KE_PRESS && set_done == FALSE )   //读取档位3数据
    {
		sFWHA01_t.system_parameter.set_temp = sFWHA01_t.system_parameter.ch3_set_temp;
		sFWHA01_t.system_parameter.air_data = sFWHA01_t.system_parameter.ch3_set_air; 
		sFWHA01_t.system_parameter.last_ch1_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch2_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch3_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_air_data = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_set_temp_f_display = RESET_VALUE;
		sFWHA01_t.general_parameter.ch = 3;
		sFWHA01_t.general_parameter.set_temp_time = SET_TEMP_SHOW_TIMES;
        set_done = TRUE;
		sbeep.cmd = BEEP_SHORT;
    }
}