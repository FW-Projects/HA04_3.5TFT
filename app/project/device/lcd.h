#ifndef __LCD_H
#define __LCD_H
#include "at32f415_wk_config.h"
#include "stdint.h"
#include "stdlib.h"

typedef struct
{
	u16 width;
	u16 height;
	u16 id;
	u8 dir;
	u16 wramcmd;
	u16 setxcmd;
	u16 setycmd;
} _lcd_dev;

extern _lcd_dev lcddev;

extern u16 POINT_COLOR;
extern u16 BACK_COLOR;

// PB0~15
#define DATAOUT(x) GPIOB->odt = x;
#define DATAIN GPIOB->idt;

// #define	LCD_CS_SET  gpio_bits_set(GPIOA,GPIO_PINS_15)
// #define	LCD_RS_SET	gpio_bits_set(GPIOC,GPIO_PINS_12)
// #define	LCD_WR_SET	gpio_bits_set(GPIOC,GPIO_PINS_10)
// #define	LCD_RD_SET	gpio_bits_set(GPIOC,GPIO_PINS_11)
// #define	LCD_RES_SET	gpio_bits_set(GPIOD,GPIO_PINS_2)

// #define	LCD_CS_CLR  gpio_bits_reset(GPIOA,GPIO_PINS_15)
// #define	LCD_RS_CLR	gpio_bits_reset(GPIOC,GPIO_PINS_12)
// #define	LCD_WR_CLR	gpio_bits_reset(GPIOC,GPIO_PINS_10)
// #define	LCD_RD_CLR	gpio_bits_reset(GPIOC,GPIO_PINS_11)
// #define	LCD_RES_CLR	gpio_bits_reset(GPIOD,GPIO_PINS_2)

#define LCD_CS_CLR GPIOA->clr = 0x8000	// CS  PA15
#define LCD_RS_CLR GPIOC->clr = 0x1000	// RS  PC12
#define LCD_WR_CLR GPIOC->clr = 0x0400	// WR  PC10
#define LCD_RD_CLR GPIOC->clr = 0x0800	// RD  PC11
#define LCD_RES_CLR GPIOD->clr = 0x0004 // RES PD12

#define LCD_CS_SET GPIOA->scr = 0x8000
#define LCD_RS_SET GPIOC->scr = 0x1000
#define LCD_WR_SET GPIOC->scr = 0x0400
#define LCD_RD_SET GPIOC->scr = 0x0800
#define LCD_RES_SET GPIOD->scr = 0x0004

#define L2R_U2D 0
#define L2R_D2U 1
#define R2L_U2D 2
#define R2L_D2U 3

#define U2D_L2R 4
#define U2D_R2L 5
#define D2U_L2R 6
#define D2U_R2L 7

#define DFT_SCAN_DIR R2L_D2U

#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define YELLOW_1 0x1F
#define BROWN 0XBC40
#define BRRED 0XFC07
#define GRAY 0X8430
#define DARKBLUE 0X01CF
#define LIGHTBLUE 0X7D7C
#define GRAYBLUE 0X5458
#define LIGHTGREEN 0X841F
#define LGRAY 0XC618
#define LGRAYBLUE 0XA651
#define LBBLUE 0X2B12

#define BLOCK_SIZE 1024

#define PIC_ADDRESS_1   0x00000000
#define PIC_ADDRESS_2   0x0004B000
#define PIC_ADDRESS_3   0x0008EF80
#define PIC_ADDRESS_4   0x000D2F00
#define PIC_ADDRESS_5   0x00116E80
#define PIC_ADDRESS_6   0x0015AE00
#define PIC_ADDRESS_7   0x0019ED80
#define PIC_ADDRESS_8   0x001E2D00
#define PIC_ADDRESS_9   0x00226C80
#define PIC_ADDRESS_10  0x0026AC00
#define PIC_ADDRESS_11  0x002AEB80
#define PIC_ADDRESS_12  0x002F2B00
#define PIC_ADDRESS_13  0x00336A80
#define PIC_ADDRESS_14  0x0037AA00
#define PIC_ADDRESS_15  0x003BE980
#define PIC_ADDRESS_16  0x00402900
#define PIC_ADDRESS_17  0x00446880
#define PIC_ADDRESS_18  0x0048A800
#define PIC_ADDRESS_19  0x004CE780
#define PIC_ADDRESS_20  0x00512700
#define PIC_ADDRESS_21  0x00556680
#define PIC_ADDRESS_22  0x0059A600
#define PIC_ADDRESS_23  0x005DE580
#define PIC_ADDRESS_24  0x00622500
#define PIC_ADDRESS_25  0x00666480
#define PIC_ADDRESS_26  0x006AA400
#define PIC_ADDRESS_27  0x006EE380
#define PIC_ADDRESS_28  0x00732300
#define PIC_ADDRESS_29  0x00776280
#define PIC_ADDRESS_30  0x007BA200
#define PIC_ADDRESS_31  0x007FE180
#define PIC_ADDRESS_32  0x00842100
#define PIC_ADDRESS_33  0x00886080
#define PIC_ADDRESS_34  0x008CA000
#define PIC_ADDRESS_35  0x0090DF80
#define PIC_ADDRESS_36  0x00951F00
#define PIC_ADDRESS_37  0x00995E80
#define PIC_ADDRESS_38  0x009D9E00
#define PIC_ADDRESS_39  0x00A1DD80
#define PIC_ADDRESS_40  0x00A61D00
#define PIC_ADDRESS_41  0x00AA5C80
#define PIC_ADDRESS_42  0x00AE9C00
#define PIC_ADDRESS_43  0x00B2DB80
#define PIC_ADDRESS_44  0x00B71B00
#define PIC_ADDRESS_45  0x00BB5A80
#define PIC_ADDRESS_46  0x00BF9A00
#define PIC_ADDRESS_47  0x00C3D980
#define PIC_ADDRESS_48  0x00C81900
#define PIC_ADDRESS_49  0x00CC5880
#define PIC_ADDRESS_50  0x00CCC900
#define PIC_ADDRESS_51  0x00CCCC72
#define PIC_ADDRESS_52  0x00CCCFE4
#define PIC_ADDRESS_53  0x00CD27C8
#define PIC_ADDRESS_54  0x00CD7FAC
#define PIC_ADDRESS_55  0x00CE3CC6
#define PIC_ADDRESS_56  0x00CEF9E0
#define PIC_ADDRESS_57  0x00CFB6FA
#define PIC_ADDRESS_58  0x00D07414
#define PIC_ADDRESS_59  0x00D1312E
#define PIC_ADDRESS_60  0x00D1EE48
#define PIC_ADDRESS_61  0x00D1F430
#define PIC_ADDRESS_62  0x00D1FA18
#define PIC_ADDRESS_63  0x00D1FEF8
#define PIC_ADDRESS_64  0x00D203D8
#define PIC_ADDRESS_65  0x00D20720
#define PIC_ADDRESS_66  0x00D20A68
#define PIC_ADDRESS_67  0x00D22958
#define PIC_ADDRESS_68  0x00D24848
#define PIC_ADDRESS_69  0x00D26738
#define PIC_ADDRESS_70  0x00D28628
#define PIC_ADDRESS_71  0x00D2AE22
#define PIC_ADDRESS_72  0x00D2D61C
#define PIC_ADDRESS_73  0x00D2FE16
#define PIC_ADDRESS_74  0x00D32610
#define PIC_ADDRESS_75  0x00D32FA0
#define PIC_ADDRESS_76  0x00D33930
#define PIC_ADDRESS_77  0x00D342C0
#define PIC_ADDRESS_78  0x00D34C50
#define PIC_ADDRESS_79  0x00D354FC
#define PIC_ADDRESS_80  0x00D35DA8
#define PIC_ADDRESS_81  0x00D37890
#define PIC_ADDRESS_82  0x00D39378
#define PIC_ADDRESS_83  0x00D3AE60
#define PIC_ADDRESS_84  0x00D3C948
#define PIC_ADDRESS_85  0x00D3E14E
#define PIC_ADDRESS_86  0x00D3F954
#define PIC_ADDRESS_87  0x00D4115A
#define PIC_ADDRESS_88  0x00D42960
#define PIC_ADDRESS_89  0x00D44C40
#define PIC_ADDRESS_90  0x00D46F20
#define PIC_ADDRESS_91  0x00D49200
#define PIC_ADDRESS_92  0x00D4B4E0
#define PIC_ADDRESS_93  0x00D4D7C0
#define PIC_ADDRESS_94  0x00D4FAA0
#define PIC_ADDRESS_95  0x00D4FC62
#define PIC_ADDRESS_96  0x00D4FE24
#define PIC_ADDRESS_97  0x00D93DA4
#define PIC_ADDRESS_98  0x00DD7D24
#define PIC_ADDRESS_99  0x00DD8EA4
#define PIC_ADDRESS_100 0x00DDA024
#define PIC_ADDRESS_101 0x00DDB1A4
#define PIC_ADDRESS_102 0x00DDC324
#define PIC_ADDRESS_103 0x00DDCB04
#define PIC_ADDRESS_104 0x00DE1AB4
#define PIC_ADDRESS_105 0x00DE6A64
#define PIC_ADDRESS_106 0x00DE7392



void LCD_WR_REG(u16 reg);
void LCD_WR_data(u16 data);
void LCD_WR_DATA(u16 data);
u16 LCD_RD_DATA(void);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_SetCursor(u16 x, u16 y);
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
u16 LCD_ReadPoint(u16 x, u16 y);
void LCD_Clear(u16 color);

void LCD_Fill(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color);
void LCD_DrawPoint(u16 x, u16 y, u16 color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void Draw_Circle(u16 x0, u16 y0, u8 r, u16 color);
void DrawArcRect(u16 x1, u16 y1, u16 x2, u16 y2, u16 r, u32 c);

void DrawProgressBar(u16 x1, u16 y1, u16 x2, u16 y2,
					 u16 pic_width, u16 pic_height,
					 u8 scale, u16 bar_color, u16 bc_color, u8 pic);
void DrawProgressBar_2(u16 x1, u16 y1, u16 x2, u16 y2, u8 scale, u16 bar_color, u16 bc_color);

void LCD_Show_Curve(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
					float curve_1, float curve_2, uint8_t *curve_1_arr, uint8_t *curve_2_arr);
void LCD_Show_Grid(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint8_t unit);

void LCD_ShowChinese(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode);	   // ????????
void LCD_ShowChinese12x12(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode); // ???????12x12????
void LCD_ShowChinese16x16(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode); // ???????16x16????
void LCD_ShowChinese24x24(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode); // ???????24x24????
void LCD_ShowChinese32x32(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode); // ???????32x32????

void LCD_ShowChar(u16 x, u16 y, u8 num, u16 fc, u16 bc, u8 sizey, u8 mode); // ?????????
void LCD_ShowChar1(u16 x, u16 y, u8 num, u16 fc, u16 bc, u8 size, u8 mode);
void LCD_ShowString(u16 x, u16 y, const u8 *p, u16 fc, u16 bc, u8 sizey, u8 mode);	   // ????????
u32 mypow(u8 m, u8 n);																   // ????
void LCD_ShowIntNum(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc, u8 sizey, u8 mode); // ???????????
void LCD_ShowIntNum_nozero(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc, u8 sizey, u8 mode);
void LCD_ShowIntNum64(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc);
void LCD_ShowIntNum128(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc);
void LCD_ShowIntNum138(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc);
void LCD_ShowFloatNum1(u16 x, u16 y, float num, u8 len, u16 fc, u16 bc, u8 sizey); // ?????¦Ë§³??????

void LCD_ShowPicture(u16 x, u16 y, u16 length, u16 width, const u8 pic[]); // ?????
void TranferPicturetoTFT_LCD(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, uint8_t Pic_Num);
void Set_Dir(u8 dir);
void LCD_Init(void);

void LCD_ShowPictureFromFlash(u16 x, u16 y, u16 length, u16 width, uint8_t Pic_Num);

void LCD_VISION(uint16_t x, uint16_t y,  uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey);
void LCD_VISION_1(uint16_t x, uint16_t y,  uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey);
#endif
