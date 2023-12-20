#ifndef _DISPLAY_H // 和文件名一致，将.换成_；前面加_。

#define _DISPLAY_H // 避免重复声明，使用if no define,define......endif

//**************宏定义AMOLED屏幕的内置颜色*****************
#define BLACK_R 0x00 //  黑色
#define BLACK_G 0x00 //  黑色
#define BLACK_B 0x00 //  黑色

#define RED_R 0xFF //  红色
#define RED_G 0x00 //  红色
#define RED_B 0x00 //  红色

#define PINK_R 0xFF //  粉红色
#define PINK_G 0x00 //  粉红色
#define PINK_B 0x00 //  粉红色

#define ORANGE_R 0xFF //  橙色
#define ORANGE_G 0x45 //  橙色
#define ORANGE_B 0x00 //  橙色

#define YELLOW_R 0xFF //  黄色
#define YELLOW_G 0xFF //  黄色
#define YELLOW_B 0x00 //  黄色

#define APRICOT_R 0xE6 //  棕色
#define APRICOT_G 0x99 //  棕色
#define APRICOT_B 0x66 //  棕色

#define GREEN_R 0x00 //  绿色
#define GREEN_G 0x80 //  绿色
#define GREEN_B 0x00 //  绿色

#define LIME_R 0x00 //  鲜绿色
#define LIME_G 0xFF //  鲜绿色
#define LIME_B 0x00 //  鲜绿色

#define CYAN_R 0x00 //  青色
#define CYAN_G 0xFF //  青色
#define CYAN_B 0xFF //  青色

#define BLUE_R 0x00 //  蓝色
#define BLUE_G 0x00 //  蓝色
#define BLUE_B 0xFF //  蓝色

#define AZURE_R 0x00 //  湛蓝色
#define AZURE_G 0x7F //  湛蓝色
#define AZURE_B 0xFF //  湛蓝色

#define PURPLE_R 0x80 //  紫色
#define PURPLE_G 0x00 //  紫色
#define PURPLE_B 0x80 //  紫色

#define GRAY_R 0x80 //  灰色
#define GRAY_G 0x80 //  灰色
#define GRAY_B 0x80 //  灰色

#define WHITE_R 0xFF //  白色
#define WHITE_G 0xFF //  白色
#define WHITE_B 0xFF //  白色
//**************宏定义AMOLED屏幕的内置颜色*****************

#include <stdio.h> //添加程序所需要的所有头文件
#include <SPI.h>
#include <string>

extern char CHN_Font_14pixel[][28];
extern char font_5_8[][5];
extern char CHN_Font_12pixel[][24];
extern char font_8_13[][20];

extern char Picture1_9_20[27];
extern char Picture2_14_20[42];
extern char Picture3_14_20[42];
extern char Picture4_19_17[57];
extern char Picture5_19_17[57];
extern char Picture6_23_16[46];
extern char Picture7_60_60[480];

extern unsigned char Tempdata1[28];
extern unsigned char Tempdata2[28];
extern unsigned char Tempdata3[28];
extern unsigned char Tempdata4[28];
extern unsigned char Tempdata5[28];
extern unsigned char Tempdata6[28];
extern unsigned char Tempdata7[28];
extern unsigned char Tempdata8[28];
extern unsigned char Tempdata9[28];
extern unsigned char Tempdata10[28];
extern unsigned char Tempdata11[28];
extern unsigned char Tempdata12[28];
extern unsigned char Tempdata13[28];
extern unsigned char Tempdata14[28];
extern unsigned char Tempdata15[28];
extern unsigned char Tempdata16[28];
extern unsigned char Tempdata17[28];
extern unsigned char Tempdata18[28];
extern unsigned char Tempdata19[28];
extern unsigned char Tempdata20[28];
extern unsigned char Tempdata21[28];
extern unsigned char Tempdata22[28];
extern unsigned char Tempdata23[28];
extern unsigned char Tempdata24[28];
extern unsigned char Tempdata25[28];
extern unsigned char Tempdata26[28];
extern unsigned char Tempdata27[28];
extern unsigned char Tempdata28[28];
extern unsigned char Tempdata29[28];
extern unsigned char Tempdata30[28];
extern unsigned char Tempdata31[28];
extern unsigned char Tempdata32[28];
extern unsigned char Tempdata33[28];
extern unsigned char Tempdata34[28];
extern unsigned char Tempdata35[28];
extern unsigned char Tempdata36[28];
extern unsigned char Tempdata37[28];
extern unsigned char Tempdata38[28];

/**
 * 两行写入,输入高位，输入低位，输入主要颜色，输入背景色
 */
void Disp(uint8_t Temp_M, uint8_t Temp_L, uint8_t color1, uint8_t color2);

/**
 * 设定当前写入目标位置
 */
void AMOLED_Block_Write(uint16_t Xstart, uint16_t Xend, uint16_t Ystart, uint16_t Yend);

/**
 * OLED屏幕批量填充像素颜色
 * color:颜色
 */
void AMOLED_Clear(uint8_t ColumnStart, uint16_t ColumnEnd, uint8_t RowStart, uint16_t RowEnd, uint16_t color);

/**
 * OLED软件初始化函数
 */
void OLED_Init(void);

/**
 * OLED屏幕整体初始化(包括软硬件)函数
 */
void AmoledInit(void);

/**
 * 写入英文字，每次写入两行，写入三次，字体尺寸5*7
 * color1:主要颜色，color2:次要颜色
 */
void LCD_font_5_7(unsigned char Tempdata[8], uint8_t CharacterPositionX, uint8_t CharacterPositionY, uint8_t color1, uint8_t color2);

/**
 * 写入中文字，大小为14pixel
 * color1:主要颜色，color2:次要颜色
 */
void ChN_Font_14(unsigned char Tempdata[28], uint8_t CharacterPositionX, uint8_t CharacterPositionY, uint8_t color1, uint8_t color2);

/**
 * 写入中文字，大小为12pixel
 * color1:主要颜色，color2:次要颜色
 */
void ChN_Font_12(unsigned char Tempdata[24], uint8_t CharacterPositionX, uint8_t CharacterPositionY, uint8_t color1, uint8_t color2);

/**
 * 万能图案写入函数
 * 输入图片的横纵宽度，用于计算写入多少次
 * x_num：理论分辨率X，y_num：理论分辨率Y，x_location：X的实际位置，y_location：Y的实际位置，color1:主要颜色，color2:次要颜色
 */
void ace_picture_EVER_Display(uint8_t x_location, uint8_t y_location, uint8_t picture_number, uint8_t color1, uint8_t color2);

/**
 * 蓝牙LOGO图标
 * color1：主要颜色，color2：次要颜色
 */
void DisplayBTlogo(bool i, uint8_t color1, uint8_t color2);

/**
 * 骑行模式1 显示表盘
 * color1：主要颜色，color2:次要颜色
 */
void ace_Mode1_Display(uint8_t color1, uint8_t color2);

/**
 * 骑行模式1 显示演示数据
 * color1:主要颜色，color2:次要颜色
 */
void ace_Mode1_Data_Display(uint8_t color1, uint8_t color2);

/**
 * 骑行模式2 显示表盘
 * color1：主要颜色，color2:次要颜色
 */
void ace_Mode2_Display(uint8_t color1, uint8_t color2);

/**
 * 骑行模式2 显示演示数据
 * color1:主要颜色，color2:次要颜色
 */
void ace_Mode2_Data_Display(uint8_t color1, uint8_t color2);

/**
 * 日常模式1 显示表盘
 * color1：主要颜色，color2:次要颜色
 */
void ace_Mode3_Display(uint8_t color1, uint8_t color2);

/**
 * 骑行模式2 显示演示数据
 * color1:主要颜色，color2:次要颜色
 */
void ace_Mode3_Data_Display(uint8_t color1, uint8_t color2);

/**
 * 画矩形函数
 * 输入起始点X轴和Y轴，输入长和宽，选择是否需要填充，输入颜色
 * x_location：起始点X，y_location：起始点Y，p_x：矩形长度，p_y：矩形宽度：是否需要填充，color:颜色
 */
void ace_print_rectangle(uint8_t x_location, uint8_t y_location, uint8_t p_x, uint8_t p_y, bool padding, uint8_t color);

/**
 * 画圆形函数
 * 输入起始点X轴和Y轴，输入半径，选择是否需要填充，输入颜色
 * x_location：起始点X，y_location：起始点Y，radius：半径，padding：是否需要填充，color:颜色
 */
void ace_print_round(uint8_t x_location, uint8_t y_location, uint8_t radius, bool padding, uint8_t color);

#endif
