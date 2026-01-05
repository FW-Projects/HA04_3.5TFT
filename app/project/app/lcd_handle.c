#include "lcd_handle.h"
#include "work_handle.h"
#include "HA01_handle.h"
#include "wk_system.h"

void page_switch(void);
void show_navigation_bar(void);
static void show_channel_state(void);
static void show_channel_value(void);
static void show_temp(void);
static void show_output(HA01_Handle *this);
void show_curve(HA01_Handle *this);
void show_cal_temp(void);
void show_icon(void);
static void number_change(void);
static void show_fan(HA01_Handle *this);
static uint8_t actual_refesh_time = 0;
static float display_air = 0;
static float display_temp = 0;
static float display_value = 0;
static number temp_actual =
	{
		.x = 85,
		.y = 20,
		.sizey = 128,
		.num = &sFWHA01_t.system_parameter.actual_temp,
		.fc = WHITE,
		.bc = BLACK,
		.len = 3,
		.mode = 0,
};

static number temp_set =
	{
		.x = 85,
		.y = 20,
		.sizey = 128,
		.num = &sFWHA01_t.system_parameter.set_temp,
		.fc = WHITE,
		.bc = BLACK,
		.len = 3,
		.mode = 0,

};

static number wind_set =
	{
		.x = 110,
		.y = 180,
		.sizey = 64,
		.num = &sFWHA01_t.system_parameter.air_data,
		.fc = WHITE,
		.bc = BLACK,
		.len = 3,
		.mode = 0,

};

static number vision_2 =
	{
		.x = 415,
		.y = 8,
		//	.num = 'v:1.10',
		.len = 7,
		.fc = WHITE,
		.bc = 0x3186,
		.sizey = 16,
		.mode = 0,
};

static number vision_1 =
	{
		.x = 236,
		.y = 128,
		//	.num = 'v:1.10',
		.len = 7,
		.fc = WHITE,
		.bc = 0x3166,
		.sizey = 32,
		.mode = 0,
};

static icon_t beep =
	{
		.x1 = 398,
		.y1 = 6,
		.length = 21,
		.winth = 21,

};
static icon_t ch1_frame =
	{
		.x1 = 90,
		.y1 = 258,
		.length = 93,
		.winth = 48,
};
static icon_t ch2_frame =
	{
		.x1 = 193,
		.y1 = 258,
		.length = 93,
		.winth = 48,
};
static icon_t ch3_frame =
	{
		.x1 = 296,
		.y1 = 258,
		.length = 93,
		.winth = 48,
};

static icon_t ch1_frame_select =
	{
		.x1 = 90,
		.y1 = 258,
		.length = 93,
		.winth = 48,
};
static icon_t ch2_frame_select =
	{
		.x1 = 193,
		.y1 = 258,
		.length = 93,
		.winth = 48,
};
static icon_t ch3_frame_select =
	{
		.x1 = 296,
		.y1 = 258,
		.length = 93,
		.winth = 48,
};

static number ch1_set_temp_1 =
	{
		.x = 97,
		.y = 280,
		.num = &sFWHA01_t.system_parameter.ch1_set_temp,
		.len = 3,
		.fc = WHITE,
		.bc = 0x3186,
		.sizey = 24,
		.mode = 0,
};

static number ch2_set_temp_1 =
	{
		.x = 200,
		.y = 280,
		.num = &sFWHA01_t.system_parameter.ch2_set_temp,
		.len = 3,
		.fc = WHITE,
		.bc = 0x3186,
		.sizey = 24,
		.mode = 0,
};

static number ch3_set_temp_1 =
	{
		.x = 303,
		.y = 280,
		.num = &sFWHA01_t.system_parameter.ch3_set_temp,
		.len = 3,
		.fc = WHITE,
		.bc = 0x3186,
		.sizey = 24,
		.mode = 0,
};
static number ch1_set_air_1 =
	{
		.x = 142,
		.y = 280,
		.num = &sFWHA01_t.system_parameter.ch1_set_air,
		.len = 3,
		.fc = WHITE,
		.bc = 0x3186,
		.sizey = 24,
		.mode = 0,
};

static number ch2_set_air_1 =
	{
		.x = 245,
		.y = 280,
		.num = &sFWHA01_t.system_parameter.ch2_set_air,
		.len = 3,
		.fc = WHITE,
		.bc = 0x3186,
		.sizey = 24,
		.mode = 0,
};
static number ch3_set_air_1 =
	{
		.x = 348,
		.y = 280,
		.num = &sFWHA01_t.system_parameter.ch3_set_air,
		.len = 3,
		.fc = WHITE,
		.bc = 0x3186,
		.sizey = 24,
		.mode = 0,
};

static icon_t set_temp_icon =
	{
		.x1 = 90,
		.y1 = 210,
		.length = 123,
		.winth = 28,
};
static icon_t actual_temp_icon =
	{
		.x1 = 90,
		.y1 = 210,
		.length = 123,
		.winth = 28,
};
static icon_t set_air_icon =
	{
		.x1 = 270,
		.y1 = 212,
		.length = 123,
		.winth = 25,
};
static icon_t actual_air_icon =
	{
		.x1 = 270,
		.y1 = 212,
		.length = 123,
		.winth = 25,
};
static number temp_main =
	{
		.x = 80,
		.y = 120,
		.len = 3,
		.fc = WHITE,
		.bc = 0x18a3,
		.sizey = 80,
		.mode = 0,
};

static number air_main =
	{
		.x = 270,
		.y = 120,
		.len = 3,
		.fc = WHITE,
		.bc = 0x18a3,
		.sizey = 80,
		.mode = 0,
};
static number temp_main_curve =
	{
		.x = 393,
		.y = 80,
		.len = 3,
		.fc = WHITE,
		.bc = 0x3186,
		.sizey = 32,
		.mode = 0,
};

static number air_main_curve =
	{
		.x = 405,
		.y = 205,
		.len = 3,
		.fc = WHITE,
		.bc = 0x3186,
		.sizey = 32,
		.mode = 0,
};

static icon_t return_icon =
	{
		.x1 = 196,
		.y1 = 250,
		.length = 88,
		.winth = 45,
};

static icon_t exit_icon =
	{
		.x1 = 90,
		.y1 = 210,
		.length = 119,
		.winth = 43,
};

static icon_t confirm_icon =
{
	.x1 = 205,
	.y1 = 190,
	.length = 70,
	.winth = 32,

};
	
static icon_t sleep_icon = 
{
	.x1 = 165,
	.y1 = 40,
	.length = 150,
	.winth = 75,
};

static icon_t over_hot_icon = 
{
	.x1 = 205,
	.y1 = 190,
	.length = 235,
	.winth = 103,
};

static icon_t low_hot_icon = 
{
	.x1 = 205,
	.y1 = 190,
	.length = 235,
	.winth = 103,
};

static icon_t error_fan_icon = 
{
	.x1 = 205,
	.y1 = 190,
	.length = 235,
	.winth = 103,
};

static icon_t power_icon = 
{
	.x1 = 355,
	.y1 = 3,
	.length = 42,
	.winth = 24,
	
};

void LcdProc(void)
{
	show_temp();
	show_output(&sFWHA01_t);
	show_cal_temp();
	show_curve(&sFWHA01_t);
	number_change();
	show_channel_state();
	show_channel_value();
	page_switch();
	show_icon();
	show_navigation_bar();
	show_fan(&sFWHA01_t);
}

void show_icon(void)
{
	static uint8_t display_number = 0;
	/*  ¡æ ¨H */
	if (sFWHA01_t.last_temp_unit != sFWHA01_t.temp_unit)
	{
		/* main uint */
		if (sFWHA01_t.page == WORK_PAGE)
		{
			if (sFWHA01_t.temp_unit == CELSIUS)
				TranferPicturetoTFT_LCD(200, 170, 20, 21, WORK_CELSIUS_ICON);
			else if (sFWHA01_t.temp_unit == FAHRENHEIT)
				TranferPicturetoTFT_LCD(200, 170, 20, 21, WORK_FAHRENHEIT_ICON);
		}
		else if (sFWHA01_t.page == CURVE_PAGE)
		{
			if (sFWHA01_t.temp_unit == CELSIUS)
				TranferPicturetoTFT_LCD(440, 84, 26, 24, CURVE_CELSIUS_ICON);
			else if (sFWHA01_t.temp_unit == FAHRENHEIT)
				TranferPicturetoTFT_LCD(440, 84, 26, 24, CURVE_FAHRENHEIT_ICON);
		}
		else if (sFWHA01_t.page == SET_SELECT_TEMP_CAL_PAGE_CN || sFWHA01_t.page == SET_TEMP_CAL_PAGE_CN)
		{
			if (sFWHA01_t.temp_unit == CELSIUS)
				TranferPicturetoTFT_LCD(320, 153, 28, 27, CAL_CELSIUS_ICON);
			else if (sFWHA01_t.temp_unit == FAHRENHEIT)
				TranferPicturetoTFT_LCD(320, 153, 28, 27, CAL_FAHRENHEIT_ICON);
		}
	}

	/* select icon */
	if (sFWHA01_t.page == SET_RUN_PAGE_CN ||
		sFWHA01_t.page == SET_UNIT_PAGE_CN ||
		sFWHA01_t.page == SET_SPEAK_PAGE_CN ||
		sFWHA01_t.page == SET_TEMP_LOCK_PAGE_CN ||
		sFWHA01_t.page == SET_SLEEP_PAGE_CN)
	{
		if (sFWHA01_t.page == SET_RUN_PAGE_CN)
		{
			if (sFWHA01_t.set_run_mode == Standard_Mode)
			{
				TranferPicturetoTFT_LCD(340, 137, 37, 30, MENU_SELECT_ICON);
				TranferPicturetoTFT_LCD(340, 177, 37, 30, MENU_UNSELECT_ICON);
			}
			else if (sFWHA01_t.set_run_mode == Power_Mode)
			{
				TranferPicturetoTFT_LCD(340, 177, 37, 30, MENU_SELECT_ICON);
				TranferPicturetoTFT_LCD(340, 137, 37, 30, MENU_UNSELECT_ICON);
			}
		}

		if (sFWHA01_t.page == SET_UNIT_PAGE_CN)
		{
			if (sFWHA01_t.set_temp_unit == FAHRENHEIT)
			{
				TranferPicturetoTFT_LCD(340, 137, 37, 30, MENU_SELECT_ICON);
				TranferPicturetoTFT_LCD(340, 177, 37, 30, MENU_UNSELECT_ICON);
			}
			else if (sFWHA01_t.set_temp_unit == CELSIUS)
			{
				TranferPicturetoTFT_LCD(340, 177, 37, 30, MENU_SELECT_ICON);
				TranferPicturetoTFT_LCD(340, 137, 37, 30, MENU_UNSELECT_ICON);
			}
		}

		if (sFWHA01_t.page == SET_SPEAK_PAGE_CN)
		{
			if (sFWHA01_t.set_speak_state == SPEAKER_CLOSE)
			{
				TranferPicturetoTFT_LCD(340, 137, 37, 30, MENU_SELECT_ICON);
				TranferPicturetoTFT_LCD(340, 177, 37, 30, MENU_UNSELECT_ICON);
			}
			else if (sFWHA01_t.set_speak_state == SPEAKER_OPEN)
			{
				TranferPicturetoTFT_LCD(340, 177, 37, 30, MENU_SELECT_ICON);
				TranferPicturetoTFT_LCD(340, 137, 37, 30, MENU_UNSELECT_ICON);
			}
		}

		if (sFWHA01_t.page == SET_TEMP_LOCK_PAGE_CN)
		{
			if (sFWHA01_t.set_display_lock_state == LOCK)
			{
				TranferPicturetoTFT_LCD(340, 137, 37, 30, MENU_SELECT_ICON);
				TranferPicturetoTFT_LCD(340, 177, 37, 30, MENU_UNSELECT_ICON);
			}
			else if (sFWHA01_t.set_display_lock_state == UNLOCK)
			{
				TranferPicturetoTFT_LCD(340, 177, 37, 30, MENU_SELECT_ICON);
				TranferPicturetoTFT_LCD(340, 137, 37, 30, MENU_UNSELECT_ICON);
			}
		}

		if (sFWHA01_t.page == SET_SLEEP_PAGE_CN)
		{
			if (sFWHA01_t.set_sleep_state == SLEEP_CLOSE)
			{
				TranferPicturetoTFT_LCD(340, 137, 37, 30, MENU_SELECT_ICON);
				TranferPicturetoTFT_LCD(340, 177, 37, 30, MENU_UNSELECT_ICON);
			}
			else if (sFWHA01_t.set_sleep_state == SLEEP_OPEN)
			{
				TranferPicturetoTFT_LCD(340, 177, 37, 30, MENU_SELECT_ICON);
				TranferPicturetoTFT_LCD(340, 137, 37, 30, MENU_UNSELECT_ICON);
			}
		}
	}

	/* return icon */
	if (sFWHA01_t.page == SET_TEMP_CAL_PAGE_CN ||
		sFWHA01_t.page == SET_SELECT_TEMP_CAL_PAGE_CN ||
		sFWHA01_t.page == SET_VERSION_PAGE_CN ||
		sFWHA01_t.page == SET_RESET_PAGE_CN ||
		sFWHA01_t.page == SET_RESET_DONE_PAGE_CN)
	{
		/* RETU																																																																																																																																																																																											RN_ICON */
		if (sFWHA01_t.page == SET_TEMP_CAL_PAGE_CN ||
			sFWHA01_t.page == SET_VERSION_PAGE_CN ||
			(sFWHA01_t.page == SET_RESET_PAGE_CN && sFWHA01_t.set_reset1 == RESET_RETURN) ||
			sFWHA01_t.page == SET_RESET_DONE_PAGE_CN)
		{
			TranferPicturetoTFT_LCD(return_icon.x1, return_icon.y1, return_icon.length, return_icon.winth, RETURN_ICON_CN);
		}

		/* UN_RETURN_ICON */
		if (sFWHA01_t.page == SET_SELECT_TEMP_CAL_PAGE_CN ||
			(sFWHA01_t.page == SET_RESET_PAGE_CN && sFWHA01_t.set_reset1 == RESET_CONFIRN))
		{
			TranferPicturetoTFT_LCD(return_icon.x1, return_icon.y1, return_icon.length, return_icon.winth, UN_RETURN_ICON_CN);
		}
	}
	/*confirm icon */
	if (sFWHA01_t.page == SET_RESET_PAGE_CN)
	{
		if (sFWHA01_t.set_reset1 == RESET_CONFIRN)
			TranferPicturetoTFT_LCD(confirm_icon.x1, confirm_icon.y1, confirm_icon.length, confirm_icon.winth, CONFIRM_ICON_CN);
		else if (sFWHA01_t.set_reset1 == RESET_RETURN)
			TranferPicturetoTFT_LCD(confirm_icon.x1, confirm_icon.y1, confirm_icon.length, confirm_icon.winth, UNCONFIRM_ICON_CN);
	}

	/* vision */
	if (sFWHA01_t.page == SET_VERSION_PAGE_CN)
	{
		/* software vision*/
		LCD_VISION(vision_1.x, vision_1.y, vision_1.len, vision_1.fc, vision_1.bc, vision_1.sizey);

		/* hardware vision*/
		LCD_VISION_1(vision_1.x, vision_1.y + 50, vision_1.len, vision_1.fc, vision_1.bc, vision_1.sizey);
	}
	
	/* sleep icon */
	if(sFWHA01_t.Work_handle_state == HANDLE_SLEEP && sFWHA01_t.page == WORK_PAGE)
	{
		TranferPicturetoTFT_LCD(sleep_icon.x1,sleep_icon.y1,sleep_icon.length,sleep_icon.winth,SLEEP_STATE_CN);
	}
	
	
	
//	if(sFWHA01_t.last_Work_handle_state != sFWHA01_t.Work_handle_state)
//	{
//		if(sFWHA01_t.Work_handle_state == HANDLE_SLEEP)
//		{
//			TranferPicturetoTFT_LCD(sleep_icon.x1,sleep_icon.y1,sleep_icon.length,sleep_icon.winth,SLEEP_STATE_CN);
//			display_number++;
//			if(display_number > 2)
//			{
//				display_number = 0;
//				sFWHA01_t.last_Work_handle_state = sFWHA01_t.Work_handle_state;
//			}
//		}
//		
//	}
	
}

void show_cal_temp(void)
{
	if (sFWHA01_t.page != SET_SELECT_TEMP_CAL_PAGE_CN && sFWHA01_t.page != SET_TEMP_CAL_PAGE_CN)
	{
		sFWHA01_t.system_parameter.cal_temp_c_display = sFWHA01_t.system_parameter.set_temp;
		sFWHA01_t.system_parameter.cal_temp_f_display = sFWHA01_t.system_parameter.set_temp_f_display;
	}

	if ((sFWHA01_t.system_parameter.last_cal_temp_c_display != sFWHA01_t.system_parameter.cal_temp_c_display) ||
		sFWHA01_t.system_parameter.last_cal_temp_f_display != sFWHA01_t.system_parameter.cal_temp_f_display)
	{
		sFWHA01_t.system_parameter.last_cal_temp_c_display = sFWHA01_t.system_parameter.cal_temp_c_display;
		sFWHA01_t.system_parameter.last_cal_temp_f_display = sFWHA01_t.system_parameter.cal_temp_f_display;

		if (sFWHA01_t.page == SET_TEMP_CAL_PAGE_CN)
		{
			if (sFWHA01_t.temp_unit == CELSIUS)
			{
				LCD_ShowIntNum(270, 150, sFWHA01_t.system_parameter.cal_temp_c_display, 3, WHITE, 0x3166, 32, 0);
			}
			else if (sFWHA01_t.temp_unit == FAHRENHEIT)
			{
				LCD_ShowIntNum(270, 150, sFWHA01_t.system_parameter.cal_temp_f_display, 3, WHITE, 0x3166, 32, 0);
			}
		}
		else if (sFWHA01_t.page == SET_SELECT_TEMP_CAL_PAGE_CN)
		{
			if (sFWHA01_t.set_cal == SET_SELECT_CAL)
			{ 
				if (sFWHA01_t.temp_unit == CELSIUS)
				{
					LCD_ShowIntNum(270, 150, sFWHA01_t.system_parameter.cal_temp_c_display, 3, WHITE, 0x3166, 32, 0);
				}
				else if (sFWHA01_t.temp_unit == FAHRENHEIT)
				{
					LCD_ShowIntNum(270, 150, sFWHA01_t.system_parameter.cal_temp_f_display, 3, WHITE, 0x3166, 32, 0);
				}
			}
			else if (sFWHA01_t.set_cal == SET_CAL)
			{
				if (sFWHA01_t.temp_unit == CELSIUS)
				{
					LCD_ShowIntNum(270, 150, sFWHA01_t.system_parameter.cal_temp_c_display, 3, GREEN, 0x3166, 32, 0);
				}
				else if (sFWHA01_t.temp_unit == FAHRENHEIT)
				{
					LCD_ShowIntNum(270, 150, sFWHA01_t.system_parameter.cal_temp_f_display, 3, GREEN, 0x3166, 32, 0);
				}
			}
		}
	}
}
void show_curve(HA01_Handle *this)
{
	static bool first_in = false;
	static uint8_t bar_value = 0;
	static uint8_t air_value = 0;

	switch (this->page)
	{
	case CURVE_PAGE:
		if (first_in == false)
		{
			/* curve grid*/
			LCD_Fill(18, 41, 376, 250, BLACK);
			first_in = true;
		}

 		if (this->Work_handle_state == HANDLE_SLEEP || this->system_parameter.actual_air < 30)
		{ 
			display_air = 0;
		} 
		if (this->temp_unit == FAHRENHEIT)
		{
			display_temp = (sFWHA01_t.system_parameter.actual_temp - 32) * 5 / 9;
		}
		else
			display_temp = sFWHA01_t.system_parameter.actual_temp ;

		LCD_Show_Curve(18, 40, 376, 250, display_temp, display_air,
					   this->system_parameter.temp_buff, this->system_parameter.air_buff);
		LCD_Show_Grid(18, 40, 376, 250, 0x840f, this->temp_unit);
		break;
	case WORK_PAGE:
#if 1
		if ((sFWHA01_t.system_parameter.last_curve_actual_temp != sFWHA01_t.system_parameter.actual_temp) ||
			(sFWHA01_t.system_parameter.last_curve_actual_temp_f_display != sFWHA01_t.system_parameter.actual_temp_f_display))	
		{
			sFWHA01_t.system_parameter.last_curve_actual_temp = sFWHA01_t.system_parameter.actual_temp;
			sFWHA01_t.system_parameter.last_curve_actual_temp_f_display = sFWHA01_t.system_parameter.actual_temp_f_display;
			if (this->temp_unit == CELSIUS)
			{
				bar_value = this->system_parameter.actual_temp * 0.2;
			}
			else if (this->temp_unit == FAHRENHEIT)
			{
				bar_value = this->system_parameter.actual_temp_f_display * 0.108;
			}
			DrawProgressBar(26, 90, 39, 256, 15, 15, bar_value, 0xfca0, 0x18a3, TEMP_BAR_ICON);
		}
		if (sFWHA01_t.system_parameter.last_curve_air_data != sFWHA01_t.system_parameter.air_data ||
			sFWHA01_t.system_parameter.last_curve_sleep_air_data != sFWHA01_t.system_parameter.sleep_air_data)
		{
			sFWHA01_t.system_parameter.last_curve_air_data = sFWHA01_t.system_parameter.air_data;
			sFWHA01_t.system_parameter.last_curve_sleep_air_data = sFWHA01_t.system_parameter.sleep_air_data;
			if (sFWHA01_t.Work_handle_state == HANDLE_WORKING &&
				 sFWHA01_t.handle_position == IN_POSSITION &&
				 sFWHA01_t.sleep_state== SLEEP_OPEN)
			{
				air_value = sFWHA01_t.system_parameter.sleep_air_data;
			}
			else
				air_value = sFWHA01_t.system_parameter.air_data;
			DrawProgressBar(441, 90, 454, 256, 15, 15, air_value * 0.5 , 0x4c38, 0x18a3, AIR_BAR_ICON);
		}
		break;
#endif
	default:
		first_in = false;

		break;
	}
}

static void show_fan(HA01_Handle *this)
{
	static uint8_t fan_count = 0;
	static bool show_fan_flag = true;
	if (this->system_parameter.actual_air >= MIN_ACTUAL_AIR && this->page == WORK_PAGE)
		{
			fan_count++;
			show_fan_flag = true;

			if (1 == fan_count)
			{
				TranferPicturetoTFT_LCD(430, 40, 36, 34, FAN_ICON_1);
			}
			else if (2 == fan_count)
			{
				TranferPicturetoTFT_LCD(430, 40, 36, 34, FAN_ICON_2);
			}
			else if (3 == fan_count)
			{
				TranferPicturetoTFT_LCD(430, 40, 36, 34, FAN_ICON_3);
			}
			if (4 == fan_count)
			{
				TranferPicturetoTFT_LCD(430, 40, 36, 34, FAN_ICON_4);
				fan_count = 0;
			}
		}
		else if (this->system_parameter.actual_air < MIN_ACTUAL_AIR && this->page == WORK_PAGE)
		{
			if (show_fan_flag)
			{
				show_fan_flag = false;
				TranferPicturetoTFT_LCD(430, 40, 36, 34, FAN_ICON_1);
			}
		}
		else if (this->page != WORK_PAGE)
		{
			show_fan_flag = true;
		}
}

static void show_output(HA01_Handle *this)
{
	static uint8_t show_step = 0;
	
	static bool first_in = false;
	static uint8_t output_value = 0;
	static int16_t delay_time = 0;
#if 1
	switch (show_step)
	{
	/* show out bar and value */
	case 0:
		delay_time--;

		if (this->page == WORK_PAGE &&
			this->Work_handle_state == HANDLE_WORKING)
		{
			if (delay_time <= 0)
			{
				delay_time = 50;
				output_value = this->system_parameter.pwm_out / 479;
				first_in = false;
				if (this->system_parameter.last_pwm_out != this->system_parameter.pwm_out)
				{
					/* show set output bar */
					DrawProgressBar_2(207, 63, 270, 67, output_value, 0x4750, 0x18a3);
					/* show set output value with white color */
					LCD_ShowIntNum(325, 52, output_value, 3, WHITE, BLACK, 24, 0);
//					this->system_parameter.last_pwm_out = this->system_parameter.pwm_out;
				}
			}
		}
		else if(this->page == WORK_PAGE && (this->Work_handle_state == HANDLE_SLEEP || this->Work_handle_state == HANDLE_WAKEN))
		{
			LCD_ShowIntNum(325, 52, 0x00, 3, WHITE, BLACK, 24, 0);
		}
		show_step++;
		break;

		/* show fan flash icon */
	case 1:
		
#if 0
		if (this->system_parameter.actual_air >= MIN_ACTUAL_AIR && this->page == WORK_PAGE)
		{
			fan_count++;
			show_fan_flag = true;

			if (1 == fan_count)
			{
				TranferPicturetoTFT_LCD(430, 40, 36, 34, FAN_ICON_1);
			}
			else if (2 == fan_count)
			{
				TranferPicturetoTFT_LCD(430, 40, 36, 34, FAN_ICON_2);
			}
			else if (3 == fan_count)
			{
				TranferPicturetoTFT_LCD(430, 40, 36, 34, FAN_ICON_3);
			}
			if (4 == fan_count)
			{
				TranferPicturetoTFT_LCD(430, 40, 36, 34, FAN_ICON_4);
				fan_count = 0;
			}
		}
		else if (this->system_parameter.actual_air < MIN_ACTUAL_AIR && this->page == WORK_PAGE)
		{
			if (show_fan_flag)
			{
				show_fan_flag = false;
				TranferPicturetoTFT_LCD(430, 40, 36, 34, FAN_ICON_1);
			}
		}
		else if (this->page != WORK_PAGE)
		{
			show_fan_flag = true;
		}
#endif
		show_step = 0;
		break;
	}
#endif
}
static void show_temp(void)
{
	static uint8_t cal = 0;
	static uint8_t first_in = 0;
	if (sFWHA01_t.general_parameter.set_temp_time != 0x00)
	{
		if(sFWHA01_t.page == CURVE_PAGE)
		{
			sFWHA01_t.general_parameter.set_temp_time -= 50;
			if(sFWHA01_t.general_parameter.set_temp_time <= 0)
				sFWHA01_t.general_parameter.set_temp_time = 0;
		}
		else if(sFWHA01_t.page == WORK_PAGE)
			sFWHA01_t.general_parameter.set_temp_time--;
	}
	else
	{
		if(actual_refesh_time != 0x00)
			actual_refesh_time--;
	}

	if (sFWHA01_t.general_parameter.set_temp_time != 0x00)
	{
		if (sFWHA01_t.general_parameter.set_temp_time == 1)
		{
			first_in = false;
		}
		/* show set_temp */
//		if (sFWHA01_t.Work_handle_state == HANDLE_SLEEP && sFWHA01_t.page != CURVE_PAGE)
//		{
//			sFWHA01_t.system_parameter.last_set_temp = sFWHA01_t.system_parameter.set_temp;
//			sFWHA01_t.system_parameter.last_set_temp_f_display = sFWHA01_t.system_parameter.set_temp_f_display;
//			sFWHA01_t.system_parameter.last_air_data = sFWHA01_t.system_parameter.air_data;
//		}
		if ((sFWHA01_t.system_parameter.last_set_temp != sFWHA01_t.system_parameter.set_temp) ||
			(sFWHA01_t.system_parameter.last_set_temp_f_display != sFWHA01_t.system_parameter.set_temp_f_display))
		{
			sFWHA01_t.system_parameter.last_set_temp = sFWHA01_t.system_parameter.set_temp;
			sFWHA01_t.system_parameter.last_set_temp_f_display = sFWHA01_t.system_parameter.set_temp_f_display;

			if (sFWHA01_t.page == CURVE_PAGE)
			{
				if (sFWHA01_t.temp_unit == CELSIUS)
				{
					LCD_ShowIntNum(temp_main_curve.x, temp_main_curve.y, sFWHA01_t.system_parameter.set_temp,
								   temp_main_curve.len, 0xfc61, temp_main_curve.bc, temp_main_curve.sizey, 0);
				}
				else if (sFWHA01_t.temp_unit == FAHRENHEIT)
				{
					LCD_ShowIntNum(temp_main_curve.x, temp_main_curve.y, sFWHA01_t.system_parameter.set_temp_f_display,
								   temp_main_curve.len, 0xfc61, temp_main_curve.bc, temp_main_curve.sizey, 0);
				}
			}

			else if (sFWHA01_t.page == WORK_PAGE)
			{
				TranferPicturetoTFT_LCD(set_temp_icon.x1, set_temp_icon.y1, set_temp_icon.length, set_temp_icon.winth, SET_TEMP_ICON_CN);

				if (sFWHA01_t.temp_unit == CELSIUS)
				{
					LCD_ShowIntNum(temp_main.x, temp_main.y, sFWHA01_t.system_parameter.set_temp,
								   temp_main.len, 0xfc61, temp_main.bc, temp_main.sizey, 0);
				}
				else if (sFWHA01_t.temp_unit == FAHRENHEIT)
				{
					LCD_ShowIntNum(temp_main.x, temp_main.y, sFWHA01_t.system_parameter.set_temp_f_display,
								   temp_main.len, 0xfc61, temp_main.bc, temp_main.sizey, 0);
				}
			}
		}

		if (sFWHA01_t.system_parameter.last_air_data != sFWHA01_t.system_parameter.air_data)
		{
			sFWHA01_t.system_parameter.last_air_data = sFWHA01_t.system_parameter.air_data;
			display_air = sFWHA01_t.system_parameter.air_data;
			if (sFWHA01_t.page == CURVE_PAGE)
			{
				LCD_ShowIntNum(air_main_curve.x, air_main_curve.y, sFWHA01_t.system_parameter.air_data,
							   air_main_curve.len, 0x3c7f, air_main_curve.bc, air_main_curve.sizey, 0);
			}

			else if (sFWHA01_t.page == WORK_PAGE)
			{
				TranferPicturetoTFT_LCD(set_air_icon.x1, set_air_icon.y1, set_air_icon.length, set_air_icon.winth, SELECT_OUTPUT_FAN_ICON_CN);

				LCD_ShowIntNum(air_main.x, air_main.y, sFWHA01_t.system_parameter.air_data,
							   air_main.len, 0x3c7f, air_main.bc, air_main.sizey, 0);
			}
		}
	}
	else
	{
		/* show actual_temp */
		if (actual_refesh_time <= 0)
		{
			if (sFWHA01_t.temp_unit == FAHRENHEIT)
			{
				sFWHA01_t.system_parameter.actual_temp_f_display = 9 * sFWHA01_t.system_parameter.actual_temp / 5 + 32;

				if (sFWHA01_t.system_parameter.cal_data != 0)
				{
					cal = 9 * sFWHA01_t.system_parameter.cal_data / 5 + 32;
				}
			}
			else
			{
				cal = -sFWHA01_t.system_parameter.cal_data;
			}

			if (sFWHA01_t.page == CURVE_PAGE || sFWHA01_t.page == LOGO )
				actual_refesh_time = 20;
			else if(sFWHA01_t.Work_handle_state == HANDLE_SLEEP)
				actual_refesh_time = 0;
			else
				actual_refesh_time = ACTUAL_TEMP_REFRESH_TIME;



//			if ((sFWHA01_t.system_parameter.last_actual_temp != sFWHA01_t.system_parameter.actual_temp) ||
//				 (sFWHA01_t.system_parameter.last_actual_temp_f_display != sFWHA01_t.system_parameter.actual_temp_f_display))
//			{
				sFWHA01_t.system_parameter.last_actual_temp = sFWHA01_t.system_parameter.actual_temp;
				sFWHA01_t.system_parameter.last_actual_temp_f_display = sFWHA01_t.system_parameter.actual_temp_f_display;

				/* show system_parameter actual temp in page single */
				if (sFWHA01_t.page == WORK_PAGE)
				{
					TranferPicturetoTFT_LCD(actual_temp_icon.x1, actual_temp_icon.y1, actual_temp_icon.length, actual_temp_icon.winth, ACTUAL_TEMP_ICON_CN);
					if (sFWHA01_t.Work_handle_state == HANDLE_WORKING)
					{
						if (sFWHA01_t.display_lock_state == LOCK)
						{
							if ((sFWHA01_t.system_parameter.actual_temp - sFWHA01_t.system_parameter.cal_data) < (sFWHA01_t.system_parameter.set_temp + LOCK_RANGE) &&
								(sFWHA01_t.system_parameter.actual_temp - sFWHA01_t.system_parameter.cal_data) > (sFWHA01_t.system_parameter.set_temp - LOCK_RANGE))
							{
								if (sFWHA01_t.temp_unit == FAHRENHEIT)
									LCD_ShowIntNum(temp_main.x, temp_main.y, sFWHA01_t.system_parameter.set_temp_f_display,
												   temp_main.len, temp_main.fc, temp_main.bc, temp_main.sizey, 0);
								else if (sFWHA01_t.temp_unit == CELSIUS)
									LCD_ShowIntNum(temp_main.x, temp_main.y, sFWHA01_t.system_parameter.set_temp,
												   temp_main.len, temp_main.fc, temp_main.bc, temp_main.sizey, 0);
							}
							else
							{
								if (sFWHA01_t.temp_unit == FAHRENHEIT)
									LCD_ShowIntNum(temp_main.x, temp_main.y, sFWHA01_t.system_parameter.actual_temp_f_display + cal,
												   temp_main.len, temp_main.fc, temp_main.bc, temp_main.sizey, 0);
								else if (sFWHA01_t.temp_unit == CELSIUS)
									LCD_ShowIntNum(temp_main.x, temp_main.y, sFWHA01_t.system_parameter.actual_temp + cal,
												   temp_main.len, temp_main.fc, temp_main.bc, temp_main.sizey, 0);
							}
						}
						else if (sFWHA01_t.display_lock_state == UNLOCK)
						{
							if (sFWHA01_t.temp_unit == FAHRENHEIT)
								LCD_ShowIntNum(temp_main.x, temp_main.y, sFWHA01_t.system_parameter.actual_temp_f_display + cal,
											   temp_main.len, temp_main.fc, temp_main.bc, temp_main.sizey, 0);
							else if (sFWHA01_t.temp_unit == CELSIUS)
								LCD_ShowIntNum(temp_main.x, temp_main.y, sFWHA01_t.system_parameter.actual_temp + cal,
											   temp_main.len, temp_main.fc, temp_main.bc, temp_main.sizey, 0);
						}
					}
					else
					{
	#if 1
						if (sFWHA01_t.temp_unit == FAHRENHEIT)
							LCD_ShowIntNum(temp_main.x, temp_main.y, sFWHA01_t.system_parameter.actual_temp_f_display + cal,
										   temp_main.len, temp_main.fc, temp_main.bc, temp_main.sizey, 0);
						else if (sFWHA01_t.temp_unit == CELSIUS)
							LCD_ShowIntNum(temp_main.x, temp_main.y, sFWHA01_t.system_parameter.actual_temp + cal,
										   temp_main.len, temp_main.fc, temp_main.bc, temp_main.sizey, 0);
	#endif
					}
				}
				/* show system_parameter actual temp in page curve */
				else if (sFWHA01_t.page == CURVE_PAGE)
				{
					if (sFWHA01_t.handle_position == IN_POSSITION)
					{
						if (sFWHA01_t.temp_unit == FAHRENHEIT)
							LCD_ShowIntNum(temp_main_curve.x, temp_main_curve.y, sFWHA01_t.system_parameter.actual_temp_f_display + cal,
										   temp_main_curve.len, temp_main_curve.fc, temp_main_curve.bc, temp_main_curve.sizey, 0);
						else if (sFWHA01_t.temp_unit == CELSIUS)
							LCD_ShowIntNum(temp_main_curve.x, temp_main_curve.y, sFWHA01_t.system_parameter.actual_temp + cal,
										   temp_main_curve.len, temp_main_curve.fc, temp_main_curve.bc, temp_main_curve.sizey, 0);
					}
					else
					{
						if (sFWHA01_t.display_lock_state == LOCK)
						{
							if ((sFWHA01_t.system_parameter.actual_temp - sFWHA01_t.system_parameter.cal_data) < (sFWHA01_t.system_parameter.set_temp + LOCK_RANGE) &&
								(sFWHA01_t.system_parameter.actual_temp - sFWHA01_t.system_parameter.cal_data) > (sFWHA01_t.system_parameter.set_temp - LOCK_RANGE))
							{
								if (sFWHA01_t.temp_unit == CELSIUS)
									LCD_ShowIntNum(temp_main_curve.x, temp_main_curve.y, sFWHA01_t.system_parameter.set_temp,
												   temp_main_curve.len, temp_main_curve.fc, temp_main_curve.bc,
												   temp_main_curve.sizey, 0);
								else if (sFWHA01_t.temp_unit == FAHRENHEIT)
									LCD_ShowIntNum(temp_main_curve.x, temp_main_curve.y, sFWHA01_t.system_parameter.set_temp_f_display,
												   temp_main_curve.len, temp_main_curve.fc, temp_main_curve.bc,
												   temp_main_curve.sizey, 0);
								else
								{
									if (sFWHA01_t.temp_unit == FAHRENHEIT)
										LCD_ShowIntNum(temp_main_curve.x, temp_main_curve.y, sFWHA01_t.system_parameter.actual_temp_f_display + cal,
													   temp_main_curve.len, temp_main_curve.fc, temp_main_curve.bc, temp_main_curve.sizey, 0);
									else if (sFWHA01_t.temp_unit == CELSIUS)
										LCD_ShowIntNum(temp_main_curve.x, temp_main_curve.y, sFWHA01_t.system_parameter.actual_temp + cal,
													   temp_main_curve.len, temp_main_curve.fc, temp_main_curve.bc, temp_main_curve.sizey, 0);
								}
							}
						}
						else if (sFWHA01_t.display_lock_state == UNLOCK)
						{
							if (sFWHA01_t.temp_unit == FAHRENHEIT)
								LCD_ShowIntNum(temp_main_curve.x, temp_main_curve.y, sFWHA01_t.system_parameter.actual_temp_f_display + cal,
											   temp_main_curve.len, temp_main_curve.fc, temp_main_curve.bc, temp_main_curve.sizey, 0);
							else if (sFWHA01_t.temp_unit == CELSIUS)
								LCD_ShowIntNum(temp_main_curve.x, temp_main_curve.y, sFWHA01_t.system_parameter.actual_temp + cal,
											   temp_main_curve.len, temp_main_curve.fc, temp_main_curve.bc, temp_main_curve.sizey, 0);
						}
					}
				}
//			}
			if (sFWHA01_t.system_parameter.last_air_data != sFWHA01_t.system_parameter.air_data || first_in == false
				|| (sFWHA01_t.system_parameter.last_sleep_air_data != sFWHA01_t.system_parameter.sleep_air_data))
//			if (first_in == false || (sFWHA01_t.system_parameter.last_sleep_air_data != sFWHA01_t.system_parameter.sleep_air_data))
			{
				first_in = true;
				sFWHA01_t.system_parameter.last_air_data = sFWHA01_t.system_parameter.air_data;
				sFWHA01_t.system_parameter.last_sleep_air_data = sFWHA01_t.system_parameter.sleep_air_data;
				if (sFWHA01_t.Work_handle_state == HANDLE_WORKING &&
				 sFWHA01_t.handle_position == IN_POSSITION &&
				 sFWHA01_t.sleep_state== SLEEP_OPEN)
				{
					display_value = sFWHA01_t.system_parameter.sleep_air_data;
				}
				else
					display_value = sFWHA01_t.system_parameter.air_data;
				if (sFWHA01_t.page == CURVE_PAGE)
				{
					LCD_ShowIntNum(air_main_curve.x, air_main_curve.y, display_value,
								   air_main_curve.len, air_main.fc, air_main_curve.bc, air_main_curve.sizey, 0);
				}
				else if (sFWHA01_t.page == WORK_PAGE)
				{
					TranferPicturetoTFT_LCD(set_air_icon.x1, set_air_icon.y1, set_air_icon.length, set_air_icon.winth, UNSELECT_OUTPUT_FAN_ICON_CN);

					LCD_ShowIntNum(air_main.x, air_main.y, display_value,
								   air_main.len, air_main.fc, air_main.bc, air_main.sizey, 0);
				}
			}
		}
	}
}

static void show_channel_state(void)
{
	static uint8_t clean_state = false;

	if ((sFWHA01_t.page == WORK_PAGE || sFWHA01_t.page == CURVE_PAGE))
	{
		if (sFWHA01_t.general_parameter.last_ch != sFWHA01_t.general_parameter.ch)
		{
			if (sFWHA01_t.general_parameter.last_ch == 1)
			{
				TranferPicturetoTFT_LCD(ch1_frame.x1, ch1_frame.y1, ch1_frame.length, ch1_frame.winth, UNSELECT_CH1);
			}
			else if (sFWHA01_t.general_parameter.last_ch == 2)
			{
				TranferPicturetoTFT_LCD(ch2_frame.x1, ch2_frame.y1, ch2_frame.length, ch2_frame.winth, UNSELECT_CH2);
			}
			else if (sFWHA01_t.general_parameter.last_ch == 3)
			{
				TranferPicturetoTFT_LCD(ch3_frame.x1, ch3_frame.y1, ch3_frame.length, ch3_frame.winth, UNSELECT_CH3);
			}
			else
			{
				TranferPicturetoTFT_LCD(ch1_frame.x1, ch1_frame.y1, ch1_frame.length, ch1_frame.winth, UNSELECT_CH1);
				TranferPicturetoTFT_LCD(ch2_frame.x1, ch2_frame.y1, ch2_frame.length, ch2_frame.winth, UNSELECT_CH2);
				TranferPicturetoTFT_LCD(ch3_frame.x1, ch3_frame.y1, ch3_frame.length, ch3_frame.winth, UNSELECT_CH3);
			}

			if (sFWHA01_t.general_parameter.ch == 1)
			{
				TranferPicturetoTFT_LCD(ch1_frame_select.x1, ch1_frame_select.y1, ch1_frame_select.length, ch1_frame_select.winth, SELECT_CH1);
			}
			else if (sFWHA01_t.general_parameter.ch == 2)
			{
				TranferPicturetoTFT_LCD(ch2_frame_select.x1, ch2_frame_select.y1, ch2_frame_select.length, ch2_frame_select.winth, SELECT_CH2);
			}
			else if (sFWHA01_t.general_parameter.ch == 3)
			{
				TranferPicturetoTFT_LCD(ch3_frame_select.x1, ch3_frame_select.y1, ch3_frame_select.length, ch3_frame_select.winth, SELECT_CH3);
			}
			clean_state = false;
			sFWHA01_t.system_parameter.last_ch1_set_temp = RESET_VALUE;
			sFWHA01_t.system_parameter.last_ch2_set_temp = RESET_VALUE;
			sFWHA01_t.system_parameter.last_ch3_set_temp = RESET_VALUE;
			sFWHA01_t.system_parameter.last_ch1_set_temp_f_display = RESET_VALUE;
			sFWHA01_t.system_parameter.last_ch2_set_temp_f_display = RESET_VALUE;
			sFWHA01_t.system_parameter.last_ch3_set_temp_f_display = RESET_VALUE;
			sFWHA01_t.general_parameter.last_ch = sFWHA01_t.general_parameter.ch;
		}

		if (sFWHA01_t.general_parameter.ch != 0)
		{
			if ((((uint16_t)sFWHA01_t.system_parameter.set_temp != (uint16_t)sFWHA01_t.system_parameter.ch1_set_temp &&
				  (uint16_t)sFWHA01_t.system_parameter.set_temp != (uint16_t)sFWHA01_t.system_parameter.ch2_set_temp &&
				  (uint16_t)sFWHA01_t.system_parameter.set_temp != (uint16_t)sFWHA01_t.system_parameter.ch3_set_temp) ||
				 ((uint16_t)sFWHA01_t.system_parameter.set_temp_f_display != (uint16_t)sFWHA01_t.system_parameter.ch1_set_temp_f_display &&
				  (uint16_t)sFWHA01_t.system_parameter.set_temp_f_display != (uint16_t)sFWHA01_t.system_parameter.ch2_set_temp_f_display &&
				  (uint16_t)sFWHA01_t.system_parameter.set_temp_f_display != (uint16_t)sFWHA01_t.system_parameter.ch3_set_temp_f_display)) &&
				clean_state == false)
			{
				sFWHA01_t.system_parameter.last_ch1_set_temp = RESET_VALUE;
				sFWHA01_t.system_parameter.last_ch2_set_temp = RESET_VALUE;
				sFWHA01_t.system_parameter.last_ch3_set_temp = RESET_VALUE;
				sFWHA01_t.system_parameter.last_ch1_set_temp_f_display = RESET_VALUE;
				sFWHA01_t.system_parameter.last_ch2_set_temp_f_display = RESET_VALUE;
				sFWHA01_t.system_parameter.last_ch3_set_temp_f_display = RESET_VALUE;
				//                sFWHA01_t.general_parameter.ch = 0;
				clean_state = true;
			}
		}
	}
}

static void number_change(void)
{
	static bool first_in = false;

	if (first_in == false)
	{

		sFWHA01_t.system_parameter.actual_temp_f_display = 9 * sFWHA01_t.system_parameter.actual_temp / 5 + 32;
		sFWHA01_t.system_parameter.set_temp_f_display = 9 * sFWHA01_t.system_parameter.set_temp / 5 + 32;

		sFWHA01_t.system_parameter.ch1_set_temp_f_display = 9 * sFWHA01_t.system_parameter.ch1_set_temp / 5 + 32;
		sFWHA01_t.system_parameter.ch2_set_temp_f_display = 9 * sFWHA01_t.system_parameter.ch2_set_temp / 5 + 32;
		sFWHA01_t.system_parameter.ch3_set_temp_f_display = 9 * sFWHA01_t.system_parameter.ch3_set_temp / 5 + 32;

		first_in = true;
	}

	/* change show number */
	if (sFWHA01_t.last_temp_unit != sFWHA01_t.temp_unit)
	{
		if (sFWHA01_t.temp_unit == CELSIUS)
		{
			sFWHA01_t.system_parameter.actual_temp_f_display = 9 * sFWHA01_t.system_parameter.actual_temp / 5 + 32;
			sFWHA01_t.system_parameter.set_temp_f_display = 9 * sFWHA01_t.system_parameter.set_temp / 5 + 32;

			sFWHA01_t.system_parameter.ch1_set_temp_f_display = 9 * sFWHA01_t.system_parameter.ch1_set_temp / 5 + 32;
			sFWHA01_t.system_parameter.ch2_set_temp_f_display = 9 * sFWHA01_t.system_parameter.ch2_set_temp / 5 + 32;
			sFWHA01_t.system_parameter.ch3_set_temp_f_display = 9 * sFWHA01_t.system_parameter.ch3_set_temp / 5 + 32;

			ch1_set_temp_1.num = &sFWHA01_t.system_parameter.ch1_set_temp;
			ch2_set_temp_1.num = &sFWHA01_t.system_parameter.ch2_set_temp;
			ch3_set_temp_1.num = &sFWHA01_t.system_parameter.ch3_set_temp;
		}
		else if (sFWHA01_t.temp_unit == FAHRENHEIT)
		{
			sFWHA01_t.system_parameter.set_temp_f_display = 9 * sFWHA01_t.system_parameter.set_temp / 5 + 32;
			sFWHA01_t.system_parameter.actual_temp_f_display = 9 * sFWHA01_t.system_parameter.actual_temp / 5 + 32;
			
			ch1_set_temp_1.num = &sFWHA01_t.system_parameter.ch1_set_temp_f_display;
			ch2_set_temp_1.num = &sFWHA01_t.system_parameter.ch2_set_temp_f_display;
			ch3_set_temp_1.num = &sFWHA01_t.system_parameter.ch3_set_temp_f_display;
		}
	}
	
}

static void show_channel_value(void)
{
	if (sFWHA01_t.page == WORK_PAGE || sFWHA01_t.page == CURVE_PAGE)
	{
		if ((sFWHA01_t.system_parameter.last_ch1_set_temp != sFWHA01_t.system_parameter.ch1_set_temp) ||
			((sFWHA01_t.system_parameter.last_ch1_set_temp_f_display != sFWHA01_t.system_parameter.ch1_set_temp_f_display)))
		{
			if (sFWHA01_t.general_parameter.ch == 1)
			{
				if (sFWHA01_t.temp_unit == FAHRENHEIT)
				{
					LCD_ShowIntNum(ch1_set_temp_1.x, ch1_set_temp_1.y, sFWHA01_t.system_parameter.ch1_set_temp_f_display,
								   ch1_set_temp_1.len, ch1_set_temp_1.fc, ch1_set_temp_1.bc, ch1_set_temp_1.sizey, 0);
				}
				else if (sFWHA01_t.temp_unit == CELSIUS)
					LCD_ShowIntNum(ch1_set_temp_1.x, ch1_set_temp_1.y, *ch1_set_temp_1.num,
								   ch1_set_temp_1.len, ch1_set_temp_1.fc, ch1_set_temp_1.bc, ch1_set_temp_1.sizey, 0);
			}
			else
			{
				if (sFWHA01_t.temp_unit == FAHRENHEIT)
				{
					LCD_ShowIntNum(ch1_set_temp_1.x, ch1_set_temp_1.y, sFWHA01_t.system_parameter.ch1_set_temp_f_display,
								   ch1_set_temp_1.len, ch1_set_temp_1.fc, ch1_set_temp_1.bc, ch1_set_temp_1.sizey, 0);
				}
				else if (sFWHA01_t.temp_unit == CELSIUS)
					LCD_ShowIntNum(ch1_set_temp_1.x, ch1_set_temp_1.y, *ch1_set_temp_1.num,
								   ch1_set_temp_1.len, ch1_set_temp_1.fc, ch1_set_temp_1.bc, ch1_set_temp_1.sizey, 0);
			}

			sFWHA01_t.system_parameter.last_ch1_set_temp = sFWHA01_t.system_parameter.ch1_set_temp;
			sFWHA01_t.system_parameter.last_ch1_set_temp_f_display = sFWHA01_t.system_parameter.ch1_set_temp_f_display;
		}

		if ((sFWHA01_t.system_parameter.last_ch2_set_temp != sFWHA01_t.system_parameter.ch2_set_temp) ||
			((sFWHA01_t.system_parameter.last_ch2_set_temp_f_display != sFWHA01_t.system_parameter.ch2_set_temp_f_display)))
		{
			if (sFWHA01_t.general_parameter.ch == 2)
			{
				if (sFWHA01_t.temp_unit == FAHRENHEIT)
					LCD_ShowIntNum(ch2_set_temp_1.x, ch2_set_temp_1.y, sFWHA01_t.system_parameter.ch2_set_temp_f_display,
								   ch2_set_temp_1.len, ch2_set_temp_1.fc, ch2_set_temp_1.bc, ch2_set_temp_1.sizey, 0);
				else if (sFWHA01_t.temp_unit == CELSIUS)
					LCD_ShowIntNum(ch2_set_temp_1.x, ch2_set_temp_1.y, *ch2_set_temp_1.num,
								   ch2_set_temp_1.len, ch2_set_temp_1.fc, ch2_set_temp_1.bc, ch2_set_temp_1.sizey, 0);
			}
			else
			{
				if (sFWHA01_t.temp_unit == FAHRENHEIT)
					LCD_ShowIntNum(ch2_set_temp_1.x, ch2_set_temp_1.y, sFWHA01_t.system_parameter.ch2_set_temp_f_display,
								   ch2_set_temp_1.len, ch2_set_temp_1.fc, ch2_set_temp_1.bc, ch2_set_temp_1.sizey, 0);
				else if (sFWHA01_t.temp_unit == CELSIUS)
					LCD_ShowIntNum(ch2_set_temp_1.x, ch2_set_temp_1.y, *ch2_set_temp_1.num,
								   ch2_set_temp_1.len, ch2_set_temp_1.fc, ch2_set_temp_1.bc, ch2_set_temp_1.sizey, 0);
			}

			sFWHA01_t.system_parameter.last_ch2_set_temp = sFWHA01_t.system_parameter.ch2_set_temp;
			sFWHA01_t.system_parameter.last_ch2_set_temp_f_display = sFWHA01_t.system_parameter.ch2_set_temp_f_display;
		}

		if ((sFWHA01_t.system_parameter.last_ch3_set_temp != sFWHA01_t.system_parameter.ch3_set_temp) ||
			((sFWHA01_t.system_parameter.last_ch3_set_temp_f_display != sFWHA01_t.system_parameter.ch3_set_temp_f_display)))
		{
			if (sFWHA01_t.general_parameter.ch == 3)
			{
				if (sFWHA01_t.temp_unit == FAHRENHEIT)
					LCD_ShowIntNum(ch3_set_temp_1.x, ch3_set_temp_1.y, sFWHA01_t.system_parameter.ch3_set_temp_f_display,
								   ch3_set_temp_1.len, ch3_set_temp_1.fc, ch3_set_temp_1.bc, ch3_set_temp_1.sizey, 0);
				else if (sFWHA01_t.temp_unit == CELSIUS)
					LCD_ShowIntNum(ch3_set_temp_1.x, ch3_set_temp_1.y, *ch3_set_temp_1.num,
								   ch3_set_temp_1.len, ch3_set_temp_1.fc, ch3_set_temp_1.bc, ch3_set_temp_1.sizey, 0);
			}
			else
			{
				if (sFWHA01_t.temp_unit == FAHRENHEIT)
					LCD_ShowIntNum(ch3_set_temp_1.x, ch3_set_temp_1.y, sFWHA01_t.system_parameter.ch3_set_temp_f_display,
								   ch3_set_temp_1.len, ch3_set_temp_1.fc, ch3_set_temp_1.bc, ch3_set_temp_1.sizey, 0);
				else if (sFWHA01_t.temp_unit == CELSIUS)
					LCD_ShowIntNum(ch3_set_temp_1.x, ch3_set_temp_1.y, *ch3_set_temp_1.num,
								   ch3_set_temp_1.len, ch3_set_temp_1.fc, ch3_set_temp_1.bc, ch3_set_temp_1.sizey, 0);
			}

			sFWHA01_t.system_parameter.last_ch3_set_temp = sFWHA01_t.system_parameter.ch3_set_temp;
			sFWHA01_t.system_parameter.last_ch3_set_temp_f_display = sFWHA01_t.system_parameter.ch3_set_temp_f_display;
		}

		if ((sFWHA01_t.system_parameter.last_ch1_set_air != sFWHA01_t.system_parameter.ch1_set_air))
		{
			if (sFWHA01_t.general_parameter.ch == 1)
			{
				LCD_ShowIntNum(ch1_set_air_1.x, ch1_set_air_1.y, *ch1_set_air_1.num,
							   ch1_set_air_1.len, ch1_set_air_1.fc, ch1_set_air_1.bc, ch1_set_air_1.sizey, 0);
			}
			else
			{
				LCD_ShowIntNum(ch1_set_air_1.x, ch1_set_air_1.y, *ch1_set_air_1.num,
							   ch1_set_air_1.len, ch1_set_air_1.fc, ch1_set_air_1.bc, ch1_set_air_1.sizey, 0);
			}

			sFWHA01_t.system_parameter.last_ch1_set_air = sFWHA01_t.system_parameter.ch1_set_air;
		}
		
		if ((sFWHA01_t.system_parameter.last_ch2_set_air != sFWHA01_t.system_parameter.ch2_set_air))
		{
			if (sFWHA01_t.general_parameter.ch == 2)
			{
				LCD_ShowIntNum(ch2_set_air_1.x, ch2_set_air_1.y, *ch2_set_air_1.num,
							   ch2_set_air_1.len, ch2_set_air_1.fc, ch2_set_air_1.bc, ch2_set_air_1.sizey, 0);
			}
			else
			{
				LCD_ShowIntNum(ch2_set_air_1.x, ch2_set_air_1.y, *ch2_set_air_1.num,
							   ch2_set_air_1.len, ch2_set_air_1.fc, ch2_set_air_1.bc, ch2_set_air_1.sizey, 0);
			}

			sFWHA01_t.system_parameter.last_ch2_set_air = sFWHA01_t.system_parameter.ch2_set_air;
		}

		if ((sFWHA01_t.system_parameter.last_ch3_set_air != sFWHA01_t.system_parameter.ch3_set_air))
		{
			if (sFWHA01_t.general_parameter.ch == 3)
			{
				LCD_ShowIntNum(ch3_set_air_1.x, ch3_set_air_1.y, *ch3_set_air_1.num,
							   ch3_set_air_1.len, ch3_set_air_1.fc, ch3_set_air_1.bc, ch3_set_air_1.sizey, 0);
			}
			else
			{
				LCD_ShowIntNum(ch3_set_air_1.x, ch3_set_air_1.y, *ch3_set_air_1.num,
							   ch3_set_air_1.len, ch3_set_air_1.fc, ch3_set_air_1.bc, ch3_set_air_1.sizey, 0);
			}

			sFWHA01_t.system_parameter.last_ch3_set_air = sFWHA01_t.system_parameter.ch3_set_air;
		}
	}
}
void page_switch(void)
{
	static bool first_in = false;
	static int reset_time = RESET_TIME;

	if (sFWHA01_t.reset_flag == true)
	{ 

		reset_time--;
		if (reset_time < 0)
		{
			reset_time = RESET_TIME;
			sFWHA01_t.reset_flag = false;
			if (sFWHA01_t.work_mode == WORK_CURVE)
			{
				sFWHA01_t.page = WORK_PAGE;
			}
			else if (sFWHA01_t.work_mode == WORK_NORMAL)
			{
				sFWHA01_t.page = CURVE_PAGE;
			}
		}
	}

	if (first_in == false)
	{
		if (sFWHA01_t.work_mode == WORK_NORMAL)
		{
			if (sFWHA01_t.handle_position == IN_POSSITION || sFWHA01_t.handle_position == NOT_IN_POSSITION)
			{ 
				sFWHA01_t.page = WORK_PAGE;
			}
		}
		else if (sFWHA01_t.work_mode == WORK_CURVE)
		{
			sFWHA01_t.page = CURVE_PAGE;
		}
		first_in = true;
	}
	if (sFWHA01_t.work_mode == WORK_NORMAL)
	{
		if (sFWHA01_t.page == WORK_PAGE || sFWHA01_t.page == CURVE_PAGE)
		{
			if ((sFWHA01_t.handle_position == IN_POSSITION) ||
				(sFWHA01_t.handle_position == NOT_IN_POSSITION))
			{ 
				sFWHA01_t.page = WORK_PAGE;
			}
		}
	}
	if(sFWHA01_t.sleep_state == SLEEP_OPEN)
	{
		if(sFWHA01_t.last_handle_position != sFWHA01_t.handle_position)
		{
			sFWHA01_t.last_handle_position = sFWHA01_t.handle_position;
			sFWHA01_t.system_parameter.last_air_data = 0x00;
			sFWHA01_t.system_parameter.last_sleep_air_data = 0x00;
			sFWHA01_t.system_parameter.last_curve_air_data = 0x00;
			sFWHA01_t.system_parameter.last_curve_sleep_air_data = 0x00;
		}
		
	}
	if(sFWHA01_t.last_Work_handle_state != sFWHA01_t.Work_handle_state && sFWHA01_t.page == WORK_PAGE)
	{
		if(sFWHA01_t.last_Work_handle_state == HANDLE_SLEEP && sFWHA01_t.Work_handle_state == HANDLE_WORKING)
			sFWHA01_t.last_page = RESET_VALUE;
		else if(sFWHA01_t.last_Work_handle_state == HANDLE_WORKING && sFWHA01_t.Work_handle_state == HANDLE_SLEEP)
		{
			sFWHA01_t.system_parameter.last_air_data = 0x00;
			sFWHA01_t.system_parameter.last_sleep_air_data = 0x00;
			sFWHA01_t.system_parameter.last_curve_air_data = 0x00;
			sFWHA01_t.system_parameter.last_curve_sleep_air_data = 0x00;
		}
		sFWHA01_t.last_Work_handle_state = sFWHA01_t.Work_handle_state;
		actual_refesh_time = 0;	
	}

	if (sFWHA01_t.last_page != sFWHA01_t.page)
	{ 
		/* refresh system_parameter set temp */
		sFWHA01_t.system_parameter.last_set_temp = RESET_VALUE;
		/* refresh system_parameter actual temp */
		sFWHA01_t.system_parameter.last_actual_temp = RESET_VALUE;
		/* refresh system_parameter cal temp */
		/* refresh system_parameter sleep time */
		sFWHA01_t.system_parameter.last_set_sleep_time = RESET_VALUE;
		display_air = sFWHA01_t.system_parameter.air_data;
		/* refresh system_parameter ch1 set value */
		sFWHA01_t.system_parameter.last_ch1_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch1_set_temp_f_display = RESET_VALUE;
		/* refresh system_parameter ch2 set value */
		sFWHA01_t.system_parameter.last_ch2_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch2_set_temp_f_display = RESET_VALUE;
		/* refresh system_parameter ch3 set value */
		sFWHA01_t.system_parameter.last_ch3_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch3_set_temp_f_display = RESET_VALUE;

		sFWHA01_t.system_parameter.last_air_data = RESET_VALUE;
		sFWHA01_t.system_parameter.last_pwm_out = RESET_VALUE;

		sFWHA01_t.system_parameter.last_curve_actual_temp = 1000;
		sFWHA01_t.system_parameter.last_curve_actual_temp_f_display = 1000;
		sFWHA01_t.system_parameter.last_curve_air_data = RESET_VALUE;
		/* refresh system_parameter channel */
		sFWHA01_t.general_parameter.last_ch = RESET_VALUE;
		/* refresh s2 channel */
		sFWHA01_t.general_parameter.last_ch = RESET_VALUE;
		;

		sFWHA01_t.system_parameter.last_cal_temp_c_display = 1000;
		sFWHA01_t.system_parameter.last_cal_temp_f_display = 1000;
		/* refresh beep icon */
		//		sFWHA01_t.general_parameter.last_speak_state = RESET_VALUE;
		/* refresh unit icon */
		sFWHA01_t.last_temp_unit = RESET_VALUE;
		/*refresh handle work mode */
		sFWHA01_t.last_work_mode = RESET_VALUE;
		/*refresh handle temo lock mode */
		sFWHA01_t.last_display_lock_state = RESET_VALUE;
//		sFWHA01_t.last_Work_handle_state = RESET_VALUE;

		sFWHA01_t.general_parameter.last_ch = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch1_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch2_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch3_set_air = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch1_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch2_set_temp = RESET_VALUE;
		sFWHA01_t.system_parameter.last_ch3_set_temp = RESET_VALUE;
		sFWHA01_t.last_page = sFWHA01_t.page;
		TranferPicturetoTFT_LCD(0, 30, 480, 290, sFWHA01_t.page);
	}
}

void show_navigation_bar(void)
{
	static bool in_first = false;
	static handle_error_state_e last_state = HANDLE_OK;
	if (in_first == false)
	{
		TranferPicturetoTFT_LCD(0, 0, 480, 30, NAVIGATION_BAR);
		LCD_VISION(vision_2.x, vision_2.y, vision_2.len, vision_2.fc, vision_2.bc, vision_2.sizey);
		sFWHA01_t.last_speak_state = RESET_VALUE;
		in_first = true;
	}
	/* show beep icon */
	if (sFWHA01_t.last_speak_state != sFWHA01_t.speak_state && sFWHA01_t.page != SET_SPEAK_PAGE_CN)
	{
		if (sFWHA01_t.speak_state == SPEAKER_OPEN)
		{
			TranferPicturetoTFT_LCD(beep.x1, beep.y1, beep.length, beep.winth, SPEAK_ICON);
		}
		else
		{
			TranferPicturetoTFT_LCD(beep.x1, beep.y1, beep.length, beep.winth, UN_SPEAK_ICON);
		}
		sFWHA01_t.last_speak_state = sFWHA01_t.speak_state;
	}
#if 1
	if(sFWHA01_t.last_run_mode != sFWHA01_t.run_mode)
	{			
		if(sFWHA01_t.run_mode == Power_Mode)
			TranferPicturetoTFT_LCD(power_icon.x1,power_icon.y1,power_icon.length,power_icon.winth,POWER_ICON);
		else
			in_first = false;
		sFWHA01_t.last_run_mode = sFWHA01_t.run_mode;

	}
#endif
	
}
