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
#define PIC_ADDRESS_2   0x00007458
#define PIC_ADDRESS_3   0x0004B3D8
#define PIC_ADDRESS_4   0x0008F358
#define PIC_ADDRESS_5   0x000D32D8
#define PIC_ADDRESS_6   0x00117258
#define PIC_ADDRESS_7   0x0015B1D8
#define PIC_ADDRESS_8   0x0019F158
#define PIC_ADDRESS_9   0x001E30D8
#define PIC_ADDRESS_10  0x00227058
#define PIC_ADDRESS_11  0x0026AFD8
#define PIC_ADDRESS_12  0x002AEF58
#define PIC_ADDRESS_13  0x002F2ED8
#define PIC_ADDRESS_14  0x00336E58
#define PIC_ADDRESS_15  0x0037ADD8
#define PIC_ADDRESS_16  0x003BED58
#define PIC_ADDRESS_17  0x00402CD8
#define PIC_ADDRESS_18  0x00446C58
#define PIC_ADDRESS_19  0x0048ABD8
#define PIC_ADDRESS_20  0x004CEB58
#define PIC_ADDRESS_21  0x00512AD8
#define PIC_ADDRESS_22  0x00556A58
#define PIC_ADDRESS_23  0x0059A9D8
#define PIC_ADDRESS_24  0x005DE958
#define PIC_ADDRESS_25  0x006228D8
#define PIC_ADDRESS_26  0x00666858
#define PIC_ADDRESS_27  0x006AA7D8
#define PIC_ADDRESS_28  0x006EE758
#define PIC_ADDRESS_29  0x007326D8
#define PIC_ADDRESS_30  0x0074C5EC
#define PIC_ADDRESS_31  0x00766500
#define PIC_ADDRESS_32  0x00780414
#define PIC_ADDRESS_33  0x0079A328
#define PIC_ADDRESS_34  0x007B423C
#define PIC_ADDRESS_35  0x007CE150
#define PIC_ADDRESS_36  0x007EB35A
#define PIC_ADDRESS_37  0x00808564
#define PIC_ADDRESS_38  0x0082576E
#define PIC_ADDRESS_39  0x00842978
#define PIC_ADDRESS_40  0x0085FB82
#define PIC_ADDRESS_41  0x0087CD8C
#define PIC_ADDRESS_42  0x00899F96
#define PIC_ADDRESS_43  0x008B71A0
#define PIC_ADDRESS_44  0x008CC6E0
#define PIC_ADDRESS_45  0x008E1C20
#define PIC_ADDRESS_46  0x008FBB34
#define PIC_ADDRESS_47  0x00915A48
#define PIC_ADDRESS_48  0x0092F95C
#define PIC_ADDRESS_49  0x00949870
#define PIC_ADDRESS_50  0x00963784
#define PIC_ADDRESS_51  0x0097D698
#define PIC_ADDRESS_52  0x009975AC
#define PIC_ADDRESS_53  0x009B14C0
#define PIC_ADDRESS_54  0x009CB3D4
#define PIC_ADDRESS_55  0x009E52E8
#define PIC_ADDRESS_56  0x009FF1FC
#define PIC_ADDRESS_57  0x00A19110
#define PIC_ADDRESS_58  0x00A33024
#define PIC_ADDRESS_59  0x00A4CF38
#define PIC_ADDRESS_60  0x00A6ABA8
#define PIC_ADDRESS_61  0x00A88818
#define PIC_ADDRESS_62  0x00A8F898
#define PIC_ADDRESS_63  0x00A8FC0A
#define PIC_ADDRESS_64  0x00A8FF7C
#define PIC_ADDRESS_65  0x00A95760
#define PIC_ADDRESS_66  0x00A9AF44
#define PIC_ADDRESS_67  0x00AA6C5E
#define PIC_ADDRESS_68  0x00AB2978
#define PIC_ADDRESS_69  0x00ABE692
#define PIC_ADDRESS_70  0x00ACA3AC
#define PIC_ADDRESS_71  0x00AD60C6
#define PIC_ADDRESS_72  0x00AE1DE0
#define PIC_ADDRESS_73  0x00AE23C8
#define PIC_ADDRESS_74  0x00AE29B0
#define PIC_ADDRESS_75  0x00AE2E90
#define PIC_ADDRESS_76  0x00AE3370
#define PIC_ADDRESS_77  0x00AE36B8
#define PIC_ADDRESS_78  0x00AE3A00
#define PIC_ADDRESS_79  0x00AE58F0
#define PIC_ADDRESS_80  0x00AE77E0
#define PIC_ADDRESS_81  0x00AE96D0
#define PIC_ADDRESS_82  0x00AEB5C0
#define PIC_ADDRESS_83  0x00AEDDBA
#define PIC_ADDRESS_84  0x00AF05B4
#define PIC_ADDRESS_85  0x00AF2DAE
#define PIC_ADDRESS_86  0x00AF55A8
#define PIC_ADDRESS_87  0x00AF5F38
#define PIC_ADDRESS_88  0x00AF68C8
#define PIC_ADDRESS_89  0x00AF7258
#define PIC_ADDRESS_90  0x00AF7BE8
#define PIC_ADDRESS_91  0x00AF8494
#define PIC_ADDRESS_92  0x00AF8D40
#define PIC_ADDRESS_93  0x00AFA828
#define PIC_ADDRESS_94  0x00AFC310
#define PIC_ADDRESS_95  0x00AFDDF8
#define PIC_ADDRESS_96  0x00AFF8E0
#define PIC_ADDRESS_97  0x00B010E6
#define PIC_ADDRESS_98  0x00B028EC
#define PIC_ADDRESS_99  0x00B040F2
#define PIC_ADDRESS_100 0x00B058F8
#define PIC_ADDRESS_101 0x00B07BD8
#define PIC_ADDRESS_102 0x00B09EB8
#define PIC_ADDRESS_103 0x00B0C198
#define PIC_ADDRESS_104 0x00B0E478
#define PIC_ADDRESS_105 0x00B10758
#define PIC_ADDRESS_106 0x00B12A38
#define PIC_ADDRESS_107 0x00B12BFA
#define PIC_ADDRESS_108 0x00B12DBC
#define PIC_ADDRESS_109 0x00B13F3C
#define PIC_ADDRESS_110 0x00B150BC
#define PIC_ADDRESS_111 0x00B1623C
#define PIC_ADDRESS_112 0x00B173BC
#define PIC_ADDRESS_113 0x00B17B9C
#define PIC_ADDRESS_114 0x00B1CB4C
#define PIC_ADDRESS_115 0x00B21AFC
#define PIC_ADDRESS_116 0x00B2242A
#define PIC_ADDRESS_117 0x00B2284C
#define PIC_ADDRESS_118 0x00B25C40
#define PIC_ADDRESS_119 0x00B29034
#define PIC_ADDRESS_120 0x00B2A1BC
#define PIC_ADDRESS_121 0x00B2B344
#define PIC_ADDRESS_122 0x00B2B664
#define PIC_ADDRESS_123 0x00B2B984
#define PIC_ADDRESS_124 0x00B31168
#define PIC_ADDRESS_125 0x00B3455C
#define PIC_ADDRESS_126 0x00B784DC

































































































































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
