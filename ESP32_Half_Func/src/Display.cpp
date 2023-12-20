#include <Arduino.h>
#include <Display.h>
#include <General.h>

/**
 * Define IO for AMOLED
    6   CS_PIN
    7   CD_PIN
    8   MOSI
    9
    10  SCLK
    11
    12  Rst_PIN
    13
*/
#define CS_PIN 6
#define HSPI_MISO 16
#define HSPI_MOSI 17
#define HSPI_SCLK 18
#define CD_PIN 7
#define Rst_PIN 8

#define Wait_Time 1

#define Display false
#define NotDisplay true

extern uint8_t CharacterPositionX, CharacterPositionY;

/**
 * 写入命令到AMOLED屏幕
 */
void WriteComm(unsigned int i)
{
  digitalWrite(CS_PIN, LOW); // 片选拉低

  digitalWrite(CD_PIN, LOW); // C/D拉低

  SPI.transfer(i);

  digitalWrite(CS_PIN, HIGH); // 片选拉高
}

/**
 * 写入数据到AMOLED屏幕
 */
void WriteData(unsigned int i)
{
  digitalWrite(CS_PIN, LOW); // 片选拉低

  digitalWrite(CD_PIN, HIGH); // C/D拉高

  SPI.transfer(i);

  digitalWrite(CS_PIN, HIGH); // 片选拉高
}

/**
 * 写入单个像素
 */
void Write_Disp_Data(uint16_t i)
{
  digitalWrite(CS_PIN, LOW); // 片选拉低

  digitalWrite(CD_PIN, HIGH); // CD拉高

  SPI.transfer(i);

  digitalWrite(CS_PIN, HIGH); // 片选拉高
}

/**
 * 两行写入,输入高位，输入低位，输入主要颜色，输入背景色
 */
void Disp(uint8_t Temp_M, uint8_t Temp_L, uint8_t color1, uint8_t color2)
{
  uint8_t j;

  uint8_t Color1_R = 0;
  uint8_t Color1_G = 0;
  uint8_t Color1_B = 0;

  uint8_t Color2_R = 0;
  uint8_t Color2_G = 0;
  uint8_t Color2_B = 0;

  switch (color1)
  {
  case 0: // 黑色
    Color1_R = BLACK_R;
    Color1_G = BLACK_G;
    Color1_B = BLACK_B;
    break;

  case 1: // 粉色
    Color1_R = RED_R;
    Color1_G = RED_G;
    Color1_B = RED_B;
    break;

  case 2: // 粉色
    Color1_R = PINK_R;
    Color1_G = PINK_G;
    Color1_B = PINK_B;
    break;

  case 3: // 橘色
    Color1_R = ORANGE_R;
    Color1_G = ORANGE_G;
    Color1_B = ORANGE_B;
    break;

  case 4: // 黄色
    Color1_R = YELLOW_R;
    Color1_G = YELLOW_G;
    Color1_B = YELLOW_B;
    break;

  case 5: // 绿色
    Color1_R = GREEN_R;
    Color1_G = GREEN_G;
    Color1_B = GREEN_B;
    break;

  case 6: // 鲜绿色
    Color1_R = LIME_R;
    Color1_G = LIME_G;
    Color1_B = LIME_B;
    break;

  case 7: // 青色
    Color1_R = CYAN_R;
    Color1_G = CYAN_G;
    Color1_B = CYAN_B;
    break;

  case 8: // 蓝色
    Color1_R = BLUE_R;
    Color1_G = BLUE_G;
    Color1_B = BLUE_B;
    break;

  case 9: // 湛蓝色
    Color1_R = AZURE_R;
    Color1_G = AZURE_G;
    Color1_B = AZURE_B;
    break;

  case 10: // 紫色
    Color1_R = PURPLE_R;
    Color1_G = PURPLE_G;
    Color1_B = PURPLE_B;
    break;

  case 11: // 灰色
    Color1_R = GRAY_R;
    Color1_G = GRAY_G;
    Color1_B = GRAY_B;
    break;

  case 12: // 白色
    Color1_R = WHITE_R;
    Color1_G = WHITE_G;
    Color1_B = WHITE_B;
    break;

  default: // 灰色
    Color1_R = BLACK_R;
    Color1_G = BLACK_G;
    Color1_B = BLACK_B;
    break;
  }

  switch (color2)
  {
  case 0: // 黑色
    Color2_R = BLACK_R;
    Color2_G = BLACK_G;
    Color2_B = BLACK_B;
    break;

  case 1: // 粉色
    Color2_R = RED_R;
    Color2_G = RED_G;
    Color2_B = RED_B;
    break;

  case 2: // 粉色
    Color2_R = PINK_R;
    Color2_G = PINK_G;
    Color2_B = PINK_B;
    break;

  case 3: // 橘色
    Color2_R = ORANGE_R;
    Color2_G = ORANGE_G;
    Color2_B = ORANGE_B;
    break;

  case 4: // 黄色
    Color2_R = YELLOW_R;
    Color2_G = YELLOW_G;
    Color2_B = YELLOW_B;
    break;

  case 5: // 绿色
    Color2_R = GREEN_R;
    Color2_G = GREEN_G;
    Color2_B = GREEN_B;
    break;

  case 6: // 鲜绿色
    Color2_R = LIME_R;
    Color2_G = LIME_G;
    Color2_B = LIME_B;
    break;

  case 7: // 青色
    Color2_R = CYAN_R;
    Color2_G = CYAN_G;
    Color2_B = CYAN_B;
    break;

  case 8: // 蓝色
    Color2_R = BLUE_R;
    Color2_G = BLUE_G;
    Color2_B = BLUE_B;
    break;

  case 9: // 湛蓝色
    Color2_R = AZURE_R;
    Color2_G = AZURE_G;
    Color2_B = AZURE_B;
    break;

  case 10: // 紫色
    Color2_R = PURPLE_R;
    Color2_G = PURPLE_G;
    Color2_B = PURPLE_B;
    break;

  case 11: // 灰色
    Color2_R = GRAY_R;
    Color2_G = GRAY_G;
    Color2_B = GRAY_B;
    break;

  case 12: // 白色
    Color2_R = WHITE_R;
    Color2_G = WHITE_G;
    Color2_B = WHITE_B;
    break;

  default: // 黑色
    Color2_R = BLACK_R;
    Color2_G = BLACK_G;
    Color2_B = BLACK_B;
    break;
  }

  for (j = 0; j < 8; j++)
  {
    if (Temp_M & (0x80 >> (j % 8)))
    {
      Write_Disp_Data(Color1_R);
      Write_Disp_Data(Color1_G);
      Write_Disp_Data(Color1_B);
    }
    else
    {
      Write_Disp_Data(Color2_R);
      Write_Disp_Data(Color2_G);
      Write_Disp_Data(Color2_B);
    }
  }

  for (j = 0; j < 8; j++)
  {
    if (Temp_L & (0x80 >> (j % 8)))
    {
      Write_Disp_Data(Color1_R);
      Write_Disp_Data(Color1_G);
      Write_Disp_Data(Color1_B);
    }
    else
    {
      Write_Disp_Data(Color2_R);
      Write_Disp_Data(Color2_G);
      Write_Disp_Data(Color2_B);
    }
  }
}

/**
 * 设定当前写入目标位置
 */
void AMOLED_Block_Write(uint16_t Xstart, uint16_t Xend, uint16_t Ystart, uint16_t Yend)
{
  WriteComm(0x2a); // Set Column Start Address
  WriteData(Xstart >> 8);
  WriteData(Xstart & 0xff);
  WriteData(Xend >> 8);
  WriteData(Xend & 0xff);

  WriteComm(0x2b); // Set Row Start Address
  WriteData(Ystart >> 8);
  WriteData(Ystart & 0xff);
  WriteData(Yend >> 8);
  WriteData(Yend & 0xff);

  WriteComm(0x2c); // Memory Write
}

/**
 * OLED屏幕批量填充像素颜色
 * color:颜色
 */
void AMOLED_Clear(uint8_t ColumnStart, uint16_t ColumnEnd, uint8_t RowStart, uint16_t RowEnd, uint16_t color)
{
  uint16_t i, j;

  AMOLED_Block_Write(ColumnStart, ColumnEnd, RowStart, RowEnd);

  for (i = 0; i < ColumnEnd; i++) // ColumnEnd-ColumnStart
    for (j = 0; j < RowEnd; j++)  // RowEnd-RowStart
    {
      switch (color)
      {
      case 0: // 黑色
        Write_Disp_Data(BLACK_R);
        Write_Disp_Data(BLACK_G);
        Write_Disp_Data(BLACK_B);

        break;

      case 1: // 红色
        Write_Disp_Data(RED_R);
        Write_Disp_Data(RED_G);
        Write_Disp_Data(RED_B);

        break;

      case 2: // 粉红色
        Write_Disp_Data(PINK_R);
        Write_Disp_Data(PINK_G);
        Write_Disp_Data(PINK_B);

        break;

      case 3: // 橘色
        Write_Disp_Data(ORANGE_R);
        Write_Disp_Data(ORANGE_G);
        Write_Disp_Data(ORANGE_B);

        break;

      case 4: // 黄色
        Write_Disp_Data(YELLOW_R);
        Write_Disp_Data(YELLOW_G);
        Write_Disp_Data(YELLOW_B);

        break;

      case 5: // 棕色
        Write_Disp_Data(APRICOT_R);
        Write_Disp_Data(APRICOT_G);
        Write_Disp_Data(APRICOT_B);

        break;

      case 6: // 绿色
        Write_Disp_Data(GREEN_R);
        Write_Disp_Data(GREEN_G);
        Write_Disp_Data(GREEN_B);

        break;

      case 7: // 鲜绿色
        Write_Disp_Data(LIME_R);
        Write_Disp_Data(LIME_G);
        Write_Disp_Data(LIME_B);

        break;

      case 8: // 青色
        Write_Disp_Data(CYAN_R);
        Write_Disp_Data(CYAN_G);
        Write_Disp_Data(CYAN_B);

        break;

      case 9: // 蓝色
        Write_Disp_Data(BLUE_R);
        Write_Disp_Data(BLUE_G);
        Write_Disp_Data(BLUE_B);

        break;

      case 10: // 湛蓝色
        Write_Disp_Data(AZURE_R);
        Write_Disp_Data(AZURE_G);
        Write_Disp_Data(AZURE_B);

        break;

      case 11: // 紫色
        Write_Disp_Data(PURPLE_R);
        Write_Disp_Data(PURPLE_G);
        Write_Disp_Data(PURPLE_B);

        break;

      case 12: // 灰色
        Write_Disp_Data(GRAY_R);
        Write_Disp_Data(GRAY_G);
        Write_Disp_Data(GRAY_B);

        break;

      case 13: // 白色
        Write_Disp_Data(WHITE_R);
        Write_Disp_Data(WHITE_G);
        Write_Disp_Data(WHITE_B);

        break;

        break;
      default: // 黑色
        Write_Disp_Data(BLACK_R);
        Write_Disp_Data(BLACK_G);
        Write_Disp_Data(BLACK_B);
        break;
      }
    }
}

/**
 * OLED软件初始化函数
 */
void OLED_Init(void)
{
  digitalWrite(Rst_PIN, HIGH); // RST=1;
  delay(30);

  //========turly0.95_code=====69310=============//

  WriteComm(0xFE);
  WriteData(0x01);
  WriteComm(0x04);
  WriteData(0xa0); // SPI write ram enable
  WriteComm(0x05);
  WriteData(0x70); // 128RGB);;LCDSPI_InitDAT( T->B);;LCDSPI_InitDAT( NW
  WriteComm(0x06);
  WriteData(0x3C); // NL = 240 line
  WriteComm(0x25);
  WriteData(0x06); // normal mode: gamma1);;LCDSPI_InitDAT( 24bit
  WriteComm(0x26);
  WriteData(0x80); // T1A = 280(640 * 100ns = 64us);
  WriteComm(0x27);
  WriteData(0x12); // normal mode VBP = 12   0c
  WriteComm(0x28);
  WriteData(0x12); // normal mode VFP = 8    08
  WriteComm(0x2A);
  WriteData(0x06); // idle mode: gamma1);;LCDSPI_InitDAT( 24bit
  WriteComm(0x2B);
  WriteData(0x80); // T1B = 280(640 * 100ns = 64us);
  WriteComm(0x2D);
  WriteData(0x12); // idle mode VBP = 12   0c
  WriteComm(0x2F);
  WriteData(0x12); // idle mode VFP = 8    08
  WriteComm(0x37);
  WriteData(0x0C); // precharge to VGSP);;LCDSPI_InitDAT( mux 1:6
  WriteComm(0x6D);
  WriteData(0x18); // skip frame VGMP and VGSP regulator off
  WriteComm(0x29);
  WriteData(0x01); // normal mode skip frame off
  WriteComm(0x30);
  WriteData(0x43); // idle mode skip frame = 60/2 = 30Hz
  WriteComm(0x0E);
  WriteData(0x83); // AVDD = 5.6V normal mode
  WriteComm(0x0F);
  WriteData(0x83); // AVDD = 5.6V idle mode
  WriteComm(0x10);
  WriteData(0x71); // AVDD = 3xVCI);;LCDSPI_InitDAT( AVDD regulator enable);;LCDSPI_InitDAT(VCL regulator enable
  WriteComm(0x11);
  WriteData(0xb3); // VCL = -2xVCI);;LCDSPI_InitDAT( normal mode
  WriteComm(0x12);
  WriteData(0xb3); // VCL = -2xVCI);;LCDSPI_InitDAT( idle mode
  WriteComm(0x13);
  WriteData(0x80); // VGH = AVDD normal mode
  WriteComm(0x14);
  WriteData(0x80); // VGH = AVDD idle mode
  WriteComm(0x15);
  WriteData(0x81); // VGL = VCL - VCI normal mode
  WriteComm(0x16);
  WriteData(0x81); // VGL = VCL - VCI idle mode
  WriteComm(0x18);
  WriteData(0x66); // VGHR = 6V normal/idle mode
  WriteComm(0x19);
  WriteData(0x44); // VGLR =  -6V normal/idle mode
  WriteComm(0x1E);
  WriteData(0x02); // Switch EQ on
  WriteComm(0x5B);
  WriteData(0x10); // VREFN5 on
  WriteComm(0x62);
  WriteData(0x19); // VREFN5 = -3V normal mode
  WriteComm(0x63);
  WriteData(0x19); // VREFN5 = -3V idle mode
  WriteComm(0x70);
  WriteData(0x55); // display off SD to AVDD);;LCDSPI_InitDAT( display on SD to AVDD
  WriteComm(0x1D);
  WriteData(0x02); // Switch EQ on
  WriteComm(0x89);
  WriteData(0x18); // VGMP =118 );;LCDSPI_InitDAT(5.5V
  WriteComm(0x8A);
  WriteData(0xb9); // VGSP = 090 );;LCDSPI_InitDAT(2V
  WriteComm(0x8B);
  WriteData(0x01); // VGMP VGSP high byte
  WriteComm(0x8C);
  WriteData(0x10); // VGMP = 110 );;LCDSPI_InitDAT(5.4V
  WriteComm(0x8D);
  WriteData(0x90); // VGSP = 090 );;LCDSPI_InitDAT(2V
  WriteComm(0x8E);
  WriteData(0x01); // VGMP VGSP high byte
  WriteComm(0x6E);
  WriteData(0x0A); // MIPI interface off
  WriteComm(0x6A);
  WriteData(0x05); // MUX
  WriteComm(0x3A);
  WriteData(0x08); // T1_sd
  WriteComm(0x3B);
  WriteData(0x00); // Tp_sd
  WriteComm(0x3D);
  WriteData(0x16); // Th_sd
  WriteComm(0x3F);
  WriteData(0x27); // Tsw_sd
  WriteComm(0x40);
  WriteData(0x0F); // Thsw_sd
  WriteComm(0x41);
  WriteData(0x0D); // Thsd_sd

  WriteComm(0x42);
  WriteData(0x14); // Mux 142536);;LCDSPI_InitDAT( odd/even line SWAP
  WriteComm(0x43);
  WriteData(0x41);
  WriteComm(0x44);
  WriteData(0x25);
  WriteComm(0x45);
  WriteData(0x52);
  WriteComm(0x46);
  WriteData(0x36);
  WriteComm(0x47);
  WriteData(0x63);
  WriteComm(0x48);
  WriteData(0x14);
  WriteComm(0x49);
  WriteData(0x41);
  WriteComm(0x4A);
  WriteData(0x25);
  WriteComm(0x4B);
  WriteData(0x52);
  WriteComm(0x4C);
  WriteData(0x36);
  WriteComm(0x4D);
  WriteData(0x63);
  WriteComm(0x4E);
  WriteData(0x14); // Data R1R2G1G2B1B2);;LCDSPI_InitDAT( odd/even line SWAP
  WriteComm(0x4F);
  WriteData(0x41);
  WriteComm(0x50);
  WriteData(0x25);
  WriteComm(0x51);
  WriteData(0x52);
  WriteComm(0x52);
  WriteData(0x36);
  WriteComm(0x53);
  WriteData(0x63);
  WriteComm(0x54);
  WriteData(0x14);
  WriteComm(0x55);
  WriteData(0x41);
  WriteComm(0x56);
  WriteData(0x25);
  WriteComm(0x57);
  WriteData(0x52);
  WriteComm(0x58);
  WriteData(0x36);
  WriteComm(0x59);
  WriteData(0x63);

  WriteComm(0x66);
  WriteData(0x90); // idle mode internal power
  WriteComm(0x67);
  WriteData(0x40); // internal power delay 1 frame off
  WriteComm(0x72);
  WriteData(0x1A); // internal OVDD = 4.6V
  WriteComm(0x73);
  WriteData(0x07); // internal OVSS = -2V
  WriteComm(0x74);
  WriteData(0x0C); // OVDD power from AVDD);;LCDSPI_InitDAT( source power from AVDD
  WriteComm(0x6A);
  WriteData(0x3D); // swire 61=0x3D pulse);;LCDSPI_InitDAT( 4.6V for SGM38042
  WriteComm(0x6B);
  WriteData(0x29); // swire 41=0x29 pulse);;LCDSPI_InitDAT( -2.4V for SGM38042

  WriteComm(0xFE);
  WriteData(0x04);
  WriteComm(0x5E);
  WriteData(0x01);
  WriteComm(0x5F);
  WriteData(0xB8);
  WriteComm(0x60);
  WriteData(0xBB);
  WriteComm(0x61);
  WriteData(0xBB);
  WriteComm(0x62);
  WriteData(0xBB);
  WriteComm(0x76);
  WriteData(0xBB);
  WriteComm(0x77);
  WriteData(0x3B);
  WriteComm(0x78);
  WriteData(0x92);
  WriteComm(0x79);
  WriteData(0xBB);
  WriteComm(0x7A);
  WriteData(0xBB);

  WriteComm(0x00);
  WriteData(0xDC); // SN_CK1
  WriteComm(0x01);
  WriteData(0x00);
  WriteComm(0x02);
  WriteData(0x02);
  WriteComm(0x03);
  WriteData(0x00);
  WriteComm(0x04);
  WriteData(0x08);
  WriteComm(0x05);
  WriteData(0x01);
  WriteComm(0x06);
  WriteData(0x70);
  WriteComm(0x07);
  WriteData(0x0A);
  WriteComm(0x08);
  WriteData(0x00);

  WriteComm(0x09);
  WriteData(0xDC); // SN_CK2
  WriteComm(0x0a);
  WriteData(0x00);
  WriteComm(0x0b);
  WriteData(0x02);
  WriteComm(0x0C);
  WriteData(0x00);
  WriteComm(0x0D);
  WriteData(0x08);
  WriteComm(0x0E);
  WriteData(0x00);
  WriteComm(0x0F);
  WriteData(0x70);
  WriteComm(0x10);
  WriteData(0x0A);
  WriteComm(0x11);
  WriteData(0x00);

  WriteComm(0x12);
  WriteData(0xCC); // EM_CK1
  WriteComm(0x13);
  WriteData(0x00);
  WriteComm(0x14);
  WriteData(0x02);
  WriteComm(0x15);
  WriteData(0x00);
  WriteComm(0x16);
  WriteData(0x20);
  WriteComm(0x17);
  WriteData(0x00);
  WriteComm(0x18);
  WriteData(0x28);
  WriteComm(0x19);
  WriteData(0x26);
  WriteComm(0x1A);
  WriteData(0x00);

  WriteComm(0x1B);
  WriteData(0xCC); // EM_CK2
  WriteComm(0x1C);
  WriteData(0x00);
  WriteComm(0x1D);
  WriteData(0x02);
  WriteComm(0x1E);
  WriteData(0x00);
  WriteComm(0x1F);
  WriteData(0x20);
  WriteComm(0x20);
  WriteData(0x01);
  WriteComm(0x21);
  WriteData(0x28);
  WriteComm(0x22);
  WriteData(0x26);
  WriteComm(0x23);
  WriteData(0x00);

  WriteComm(0x4C);
  WriteData(0x89); // SN_STV
  WriteComm(0x4D);
  WriteData(0x00);
  WriteComm(0x4E);
  WriteData(0x01);
  WriteComm(0x4F);
  WriteData(0x00);
  WriteComm(0x50);
  WriteData(0x01);
  WriteComm(0x51);
  WriteData(0xBB);
  WriteComm(0x52);
  WriteData(0xBB);

  WriteComm(0x53);
  WriteData(0xCA); // EM_STV
  WriteComm(0x54);
  WriteData(0x00);
  WriteComm(0x55);
  WriteData(0x03);
  WriteComm(0x56);
  WriteData(0x00);
  WriteComm(0x58);
  WriteData(0x00);
  WriteComm(0x59);
  WriteData(0x00);
  WriteComm(0x65);
  WriteData(0x45); // 04
  WriteComm(0x66);
  WriteData(0x0C); // 03
  WriteComm(0x67);
  WriteData(0x00); // 10

  WriteComm(0xFE);
  WriteData(0x01); // ID
  WriteComm(0xE5);
  WriteData(0x00);
  WriteComm(0xE6);
  WriteData(0x10);
  WriteComm(0xE7);
  WriteData(0x31);
  WriteComm(0xFE);
  WriteData(0x00);
  WriteComm(0xC4);
  WriteData(0x80);
  WriteComm(0x2A);
  WriteData(0x00);
  WriteData(0x04);
  WriteData(0x00);
  WriteData(0x7B);

  WriteComm(0x11);
  WriteData(0x00);
  delay(150);
  WriteComm(0x29);
  WriteData(0x00);
}

/**
 * OLED屏幕整体初始化(包括软硬件)函数
 */
void AmoledInit(void)
{
  pinMode(Rst_PIN, OUTPUT);
  digitalWrite(Rst_PIN, LOW);
  pinMode(CS_PIN, OUTPUT);
  pinMode(CD_PIN, OUTPUT);
  OLED_Init();
}

/**
 * 写入英文字，每次写入两行，写入三次，字体尺寸5*7
 * color1:主要颜色，color2:次要颜色
 */
void LCD_font_5_7(unsigned char Tempdata[8], uint8_t CharacterPositionX, uint8_t CharacterPositionY, uint8_t color1, uint8_t color2)
{
  delay(6);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY, CharacterPositionY + 10);
  Disp(Tempdata[0], Tempdata[1], color1, color2);

  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 2, CharacterPositionY + 10);
  Disp(Tempdata[2], Tempdata[3], color1, color2);

  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 4, CharacterPositionY + 10);
  Disp(Tempdata[4], Tempdata[5], color1, color2);

  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 6, CharacterPositionY + 10);
  Disp(Tempdata[6], Tempdata[7], color1, color2);
}

/**
 * 写入英文字，每次写入两行，写入三次，字体尺寸5*7
 * color1:主要颜色，color2:次要颜色
 */
void LCD_font_8_13(unsigned char Tempdata[20], uint8_t CharacterPositionX, uint8_t CharacterPositionY, uint8_t color1, uint8_t color2)
{
  delay(6);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 8, CharacterPositionY, CharacterPositionY + 10);
  Disp(Tempdata[0], Tempdata[1], color1, color2);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 8, CharacterPositionY + 2, CharacterPositionY + 10 + 2);
  Disp(Tempdata[2], Tempdata[3], color1, color2);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 8, CharacterPositionY + 4, CharacterPositionY + 10 + 4);
  Disp(Tempdata[4], Tempdata[5], color1, color2);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 8, CharacterPositionY + 6, CharacterPositionY + 10 + 6);
  Disp(Tempdata[6], Tempdata[7], color1, color2);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 7 + 8, CharacterPositionY, CharacterPositionY + 10);
  Disp(Tempdata[8], Tempdata[9], color1, color2);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 7 + 8, CharacterPositionY + 2, CharacterPositionY + 10 + 2);
  Disp(Tempdata[10], Tempdata[11], color1, color2);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 7 + 8, CharacterPositionY + 4, CharacterPositionY + 10 + 4);
  Disp(Tempdata[12], Tempdata[13], color1, color2);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 7 + 8, CharacterPositionY + 6, CharacterPositionY + 10 + 6);
  Disp(Tempdata[14], Tempdata[15], color1, color2);
}

/**
 * 写入中文字，大小为14pixel
 * color1:主要颜色，color2:次要颜色
 */
void ChN_Font_14(unsigned char Tempdata[28], uint8_t CharacterPositionX, uint8_t CharacterPositionY, uint8_t color1, uint8_t color2)
{
  // 第一次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY, CharacterPositionY + 14);
  Disp(Tempdata[14], Tempdata[15], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY, CharacterPositionY + 14);
  Disp(Tempdata[0], Tempdata[1], color1, color2);

  // 第二次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 2, CharacterPositionY + 14);
  Disp(Tempdata[16], Tempdata[17], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 2, CharacterPositionY + 14);
  Disp(Tempdata[2], Tempdata[3], color1, color2);

  // 第三次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 4, CharacterPositionY + 14);
  Disp(Tempdata[18], Tempdata[19], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 4, CharacterPositionY + 14);
  Disp(Tempdata[4], Tempdata[5], color1, color2);

  // 第四次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 6, CharacterPositionY + 14);
  Disp(Tempdata[20], Tempdata[21], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 6, CharacterPositionY + 14);
  Disp(Tempdata[6], Tempdata[7], color1, color2);

  // 第五次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 8, CharacterPositionY + 14);
  Disp(Tempdata[22], Tempdata[23], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 8, CharacterPositionY + 14);
  Disp(Tempdata[8], Tempdata[9], color1, color2);

  // 第六次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 10, CharacterPositionY + 14);
  Disp(Tempdata[24], Tempdata[25], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 10, CharacterPositionY + 14);
  Disp(Tempdata[10], Tempdata[11], color1, color2);

  // 第七次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 12, CharacterPositionY + 14);
  Disp(Tempdata[26], Tempdata[27], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 12, CharacterPositionY + 14);
  Disp(Tempdata[12], Tempdata[13], color1, color2);
}

/**
 * 写入中文字，大小为12pixel
 * color1:主要颜色，color2:次要颜色
 */
void ChN_Font_12(unsigned char Tempdata[24], uint8_t CharacterPositionX, uint8_t CharacterPositionY, uint8_t color1, uint8_t color2)
{
  // 第一次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY, CharacterPositionY + 14);
  Disp(Tempdata[12], Tempdata[13], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY, CharacterPositionY + 14);
  Disp(Tempdata[0], Tempdata[1], color1, color2);

  // 第二次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 2, CharacterPositionY + 14);
  Disp(Tempdata[14], Tempdata[15], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 2, CharacterPositionY + 14);
  Disp(Tempdata[2], Tempdata[3], color1, color2);

  // 第三次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 4, CharacterPositionY + 14);
  Disp(Tempdata[16], Tempdata[17], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 4, CharacterPositionY + 14);
  Disp(Tempdata[4], Tempdata[5], color1, color2);

  // 第四次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 6, CharacterPositionY + 14);
  Disp(Tempdata[18], Tempdata[19], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 6, CharacterPositionY + 14);
  Disp(Tempdata[6], Tempdata[7], color1, color2);

  // 第五次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 8, CharacterPositionY + 14);
  Disp(Tempdata[20], Tempdata[21], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 8, CharacterPositionY + 14);
  Disp(Tempdata[8], Tempdata[9], color1, color2);

  // 第六次填充
  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX, CharacterPositionX + 7, CharacterPositionY + 10, CharacterPositionY + 14);
  Disp(Tempdata[22], Tempdata[23], color1, color2);

  delay(Wait_Time);
  AMOLED_Block_Write(CharacterPositionX + 8, CharacterPositionX + 15, CharacterPositionY + 10, CharacterPositionY + 14);
  Disp(Tempdata[10], Tempdata[11], color1, color2);
}

/**
 * 图案写入函数
 * x_num：理论分辨率X，y_num：理论分辨率Y，x_location：X的实际位置，y_location：Y的实际位置，color1:主要颜色，color2:次要颜色
 */
void ace_picture_EVER_Display(uint8_t x_location, uint8_t y_location, uint8_t picture_number, uint8_t color1, uint8_t color2)
{

  uint8_t x_num;

  uint8_t y_num;

  switch (picture_number)
  {
  case 1:
    x_num = 9;
    y_num = 20;
    break;

  case 2:
    x_num = 14;
    y_num = 20;
    break;

  case 3:
    x_num = 14;
    y_num = 20;
    break;

  case 4:
    x_num = 19;
    y_num = 17;
    break;

  case 5:
    x_num = 19;
    y_num = 17;
    break;

  case 6:
    x_num = 23;
    y_num = 16;
    break;

  case 7:
    x_num = 60;
    y_num = 60;
    break;

  default:
    break;
  }

  uint16_t x1_num; // X的实际刷新次数
  uint16_t y1_num; // Y的实际刷新次数

  uint16_t m = 0; // 用于计算当前数组中的填充次数

  bool Return1 = false;

  // 用于判断是否为特殊情况，这段是因为数据写入函数，一次写入两列所以这么写。
  if ((x_num > 0) && (x_num < 8))
  {
    x1_num = 1;
  }
  else if ((x_num > 0) && ((x_num % 8) != 0)) // 虽然写X实际却是Y
  {
    x1_num = (x_num / 8) + 1;
  }
  else if ((x_num > 0) && ((x_num % 8) == 0))
  {
    x1_num = (x_num / 8);
  }

  if ((y_num > 0) && (y_num < 2))
  {
    y1_num = 1;
    Return1 = false;
  }
  else if ((y_num > 0) && ((y_num % 2) != 0)) // 虽然写X实际却是Y
  {
    y1_num = (y_num / 2) + 1;
    Return1 = true;
  }
  else if ((y_num > 0) && ((y_num % 2) == 0))
  {
    y1_num = (y_num / 2);
    Return1 = false;
  }

  switch (picture_number)
  {
  case 1: // 内置样式1箭头 UP pixelSize 9 * 20 纵向先左右再下上 9/24
    AMOLED_Block_Write(x_location, x_location + 7, y_location, y_location + 10);
    Disp(Picture1_9_20[0], Picture1_9_20[1], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 2, y_location + 10 + 2);
    Disp(Picture1_9_20[2], Picture1_9_20[3], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 4, y_location + 10 + 4);
    Disp(Picture1_9_20[4], Picture1_9_20[5], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 6, y_location + 10 + 6);
    Disp(Picture1_9_20[6], Picture1_9_20[7], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 8, y_location + 10 + 8);
    Disp(Picture1_9_20[8], 0x00, color1, color2);

    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location, y_location + 10);
    Disp(Picture1_9_20[9], Picture1_9_20[10], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture1_9_20[11], Picture1_9_20[12], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture1_9_20[13], Picture1_9_20[14], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture1_9_20[15], Picture1_9_20[16], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture1_9_20[17], 0x00, color1, color2);

    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location, y_location + 10);
    Disp(Picture1_9_20[18], Picture1_9_20[19], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture1_9_20[20], Picture1_9_20[21], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture1_9_20[22], Picture1_9_20[23], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture1_9_20[24], Picture1_9_20[25], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture1_9_20[26], 0x00, color1, color2);
    break;

  case 2: // 内置样式2箭头向左 LIFT pixelSize 14 * 20 纵向先左右再上下
    AMOLED_Block_Write(x_location, x_location + 7, y_location, y_location + 10);
    Disp(Picture2_14_20[0], Picture2_14_20[1], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 2, y_location + 10 + 2);
    Disp(Picture2_14_20[2], Picture2_14_20[3], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 4, y_location + 10 + 4);
    Disp(Picture2_14_20[4], Picture2_14_20[5], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 6, y_location + 10 + 6);
    Disp(Picture2_14_20[6], Picture2_14_20[7], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 8, y_location + 10 + 8);
    Disp(Picture2_14_20[8], Picture2_14_20[9], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 10, y_location + 10 + 10);
    Disp(Picture2_14_20[10], Picture2_14_20[11], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 12, y_location + 10 + 12);
    Disp(Picture2_14_20[12], Picture2_14_20[13], color1, color2);

    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location, y_location + 10);
    Disp(Picture2_14_20[14], Picture2_14_20[15], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture2_14_20[16], Picture2_14_20[17], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture2_14_20[18], Picture2_14_20[19], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture2_14_20[20], Picture2_14_20[21], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture2_14_20[22], Picture2_14_20[23], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 10, y_location + 10 + 10);
    Disp(Picture2_14_20[24], Picture2_14_20[25], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 12, y_location + 10 + 12);
    Disp(Picture2_14_20[26], Picture2_14_20[27], color1, color2);

    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location, y_location + 10);
    Disp(Picture2_14_20[28], Picture2_14_20[29], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture2_14_20[30], Picture2_14_20[31], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture2_14_20[32], Picture2_14_20[33], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture2_14_20[34], Picture2_14_20[35], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture2_14_20[36], Picture2_14_20[37], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 10, y_location + 10 + 10);
    Disp(Picture2_14_20[38], Picture2_14_20[39], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 12, y_location + 10 + 12);
    Disp(Picture2_14_20[40], Picture2_14_20[41], color1, color2);
    break;

  case 3: // 内置样式3箭头向右 RIGHT pixelSize 14 * 20 纵向先左右再上下
    AMOLED_Block_Write(x_location, x_location + 7, y_location, y_location + 10);
    Disp(Picture3_14_20[0], Picture3_14_20[1], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 2, y_location + 10 + 2);
    Disp(Picture3_14_20[2], Picture3_14_20[3], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 4, y_location + 10 + 4);
    Disp(Picture3_14_20[4], Picture3_14_20[5], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 6, y_location + 10 + 6);
    Disp(Picture3_14_20[6], Picture3_14_20[7], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 8, y_location + 10 + 8);
    Disp(Picture3_14_20[8], Picture3_14_20[9], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 10, y_location + 10 + 10);
    Disp(Picture3_14_20[10], Picture3_14_20[11], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 12, y_location + 10 + 12);
    Disp(Picture3_14_20[12], Picture3_14_20[13], color1, color2);

    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location, y_location + 10);
    Disp(Picture3_14_20[14], Picture3_14_20[15], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture3_14_20[16], Picture3_14_20[17], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture3_14_20[18], Picture3_14_20[19], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture3_14_20[20], Picture3_14_20[21], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture3_14_20[22], Picture3_14_20[23], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 10, y_location + 10 + 10);
    Disp(Picture3_14_20[24], Picture3_14_20[25], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 12, y_location + 10 + 12);
    Disp(Picture3_14_20[26], Picture3_14_20[27], color1, color2);

    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location, y_location + 10);
    Disp(Picture3_14_20[28], Picture3_14_20[29], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture3_14_20[30], Picture3_14_20[31], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture3_14_20[32], Picture3_14_20[33], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture3_14_20[34], Picture3_14_20[35], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture3_14_20[36], Picture3_14_20[37], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 10, y_location + 10 + 10);
    Disp(Picture3_14_20[38], Picture3_14_20[39], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 12, y_location + 10 + 12);
    Disp(Picture3_14_20[40], Picture3_14_20[41], color1, color2);
    break;

  case 4: // 内置样式4 箭头向左前 pixelSize 19 * 17 纵向先左右再上下
    AMOLED_Block_Write(x_location, x_location + 7, y_location, y_location + 10);
    Disp(Picture4_19_17[0], Picture4_19_17[1], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 2, y_location + 10 + 2);
    Disp(Picture4_19_17[2], Picture4_19_17[3], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 4, y_location + 10 + 4);
    Disp(Picture4_19_17[4], Picture4_19_17[5], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 6, y_location + 10 + 6);
    Disp(Picture4_19_17[6], Picture4_19_17[7], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 8, y_location + 10 + 8);
    Disp(Picture4_19_17[8], Picture4_19_17[9], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 10, y_location + 10 + 10);
    Disp(Picture4_19_17[10], Picture4_19_17[11], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 12, y_location + 10 + 12);
    Disp(Picture4_19_17[12], Picture4_19_17[13], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 14, y_location + 10 + 14);
    Disp(Picture4_19_17[14], Picture4_19_17[15], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 16, y_location + 10 + 16);
    Disp(Picture4_19_17[16], Picture4_19_17[17], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 18, y_location + 10 + 18);
    Disp(Picture4_19_17[18], 0x00, color1, color2);

    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location, y_location + 10);
    Disp(Picture4_19_17[19], Picture4_19_17[20], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture4_19_17[21], Picture4_19_17[22], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture4_19_17[23], Picture4_19_17[24], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture4_19_17[25], Picture4_19_17[26], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture4_19_17[27], Picture4_19_17[28], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 10, y_location + 10 + 10);
    Disp(Picture4_19_17[29], Picture4_19_17[30], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 12, y_location + 10 + 12);
    Disp(Picture4_19_17[31], Picture4_19_17[32], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 14, y_location + 10 + 14);
    Disp(Picture4_19_17[33], Picture4_19_17[34], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 16, y_location + 10 + 16);
    Disp(Picture4_19_17[35], Picture4_19_17[36], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 18, y_location + 10 + 18);
    Disp(Picture4_19_17[37], 0x00, color1, color2);

    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location, y_location + 10);
    Disp(Picture4_19_17[38], Picture4_19_17[39], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture4_19_17[40], Picture4_19_17[41], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture4_19_17[42], Picture4_19_17[43], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture4_19_17[44], Picture4_19_17[45], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture4_19_17[46], Picture4_19_17[47], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 10, y_location + 10 + 10);
    Disp(Picture4_19_17[48], Picture4_19_17[49], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 12, y_location + 10 + 12);
    Disp(Picture4_19_17[50], Picture4_19_17[51], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 14, y_location + 10 + 14);
    Disp(Picture4_19_17[52], Picture4_19_17[53], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 16, y_location + 10 + 16);
    Disp(Picture4_19_17[54], Picture4_19_17[55], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 18, y_location + 10 + 18);
    Disp(Picture4_19_17[56], 0x00, color1, color2);
    break;

  case 5: // 内置样式5 箭头向右前 pixelSize 19 * 17 纵向先左右再上下
    AMOLED_Block_Write(x_location, x_location + 7, y_location, y_location + 10);
    Disp(Picture5_19_17[0], Picture5_19_17[1], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 2, y_location + 10 + 2);
    Disp(Picture5_19_17[2], Picture5_19_17[3], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 4, y_location + 10 + 4);
    Disp(Picture5_19_17[4], Picture5_19_17[5], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 6, y_location + 10 + 6);
    Disp(Picture5_19_17[6], Picture5_19_17[7], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 8, y_location + 10 + 8);
    Disp(Picture5_19_17[8], Picture5_19_17[9], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 10, y_location + 10 + 10);
    Disp(Picture5_19_17[10], Picture5_19_17[11], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 12, y_location + 10 + 12);
    Disp(Picture5_19_17[12], Picture5_19_17[13], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 14, y_location + 10 + 14);
    Disp(Picture5_19_17[14], Picture5_19_17[15], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 16, y_location + 10 + 16);
    Disp(Picture5_19_17[16], Picture5_19_17[17], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 18, y_location + 10 + 18);
    Disp(Picture5_19_17[18], 0x00, color1, color2);

    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location, y_location + 10);
    Disp(Picture5_19_17[19], Picture5_19_17[20], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture5_19_17[21], Picture5_19_17[22], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture5_19_17[23], Picture5_19_17[24], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture5_19_17[25], Picture5_19_17[26], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture5_19_17[27], Picture5_19_17[28], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 10, y_location + 10 + 10);
    Disp(Picture5_19_17[29], Picture5_19_17[30], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 12, y_location + 10 + 12);
    Disp(Picture5_19_17[31], Picture5_19_17[32], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 14, y_location + 10 + 14);
    Disp(Picture5_19_17[33], Picture5_19_17[34], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 16, y_location + 10 + 16);
    Disp(Picture5_19_17[35], Picture5_19_17[36], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 18, y_location + 10 + 18);
    Disp(Picture5_19_17[37], 0x00, color1, color2);

    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location, y_location + 10);
    Disp(Picture5_19_17[38], Picture5_19_17[39], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture5_19_17[40], Picture5_19_17[41], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture5_19_17[42], Picture5_19_17[43], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture5_19_17[44], Picture5_19_17[45], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture5_19_17[46], Picture5_19_17[47], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 10, y_location + 10 + 10);
    Disp(Picture5_19_17[48], Picture5_19_17[49], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 12, y_location + 10 + 12);
    Disp(Picture5_19_17[50], Picture5_19_17[51], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 14, y_location + 10 + 14);
    Disp(Picture5_19_17[52], Picture5_19_17[53], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 16, y_location + 10 + 16);
    Disp(Picture5_19_17[54], Picture5_19_17[55], color1, color2);
    AMOLED_Block_Write(x_location + 8 + 8, x_location + 7 + 8 + 8, y_location + 18, y_location + 10 + 18);
    Disp(Picture5_19_17[56], 0x00, color1, color2);
    break;

  case 6: // 内置样式6 箭头向后 pixelSize 23 * 16 纵向先左右再上下
    AMOLED_Block_Write(x_location, x_location + 7, y_location, y_location + 10);
    Disp(Picture6_23_16[0], Picture6_23_16[1], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 2, y_location + 10 + 2);
    Disp(Picture6_23_16[2], Picture6_23_16[3], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 4, y_location + 10 + 4);
    Disp(Picture6_23_16[4], Picture6_23_16[5], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 6, y_location + 10 + 6);
    Disp(Picture6_23_16[6], Picture6_23_16[7], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 8, y_location + 10 + 8);
    Disp(Picture6_23_16[8], Picture6_23_16[9], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 10, y_location + 10 + 10);
    Disp(Picture6_23_16[10], Picture6_23_16[11], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 12, y_location + 10 + 12);
    Disp(Picture6_23_16[12], Picture6_23_16[13], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 14, y_location + 10 + 14);
    Disp(Picture6_23_16[14], Picture6_23_16[15], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 16, y_location + 10 + 16);
    Disp(Picture6_23_16[16], Picture6_23_16[17], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 18, y_location + 10 + 18);
    Disp(Picture6_23_16[18], Picture6_23_16[19], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 20, y_location + 10 + 20);
    Disp(Picture6_23_16[20], Picture6_23_16[21], color1, color2);
    AMOLED_Block_Write(x_location, x_location + 7, y_location + 22, y_location + 10 + 22);
    Disp(Picture6_23_16[22], 0x00, color1, color2);

    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location, y_location + 10);
    Disp(Picture6_23_16[23], Picture6_23_16[24], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 2, y_location + 10 + 2);
    Disp(Picture6_23_16[25], Picture6_23_16[26], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 4, y_location + 10 + 4);
    Disp(Picture6_23_16[27], Picture6_23_16[28], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 6, y_location + 10 + 6);
    Disp(Picture6_23_16[29], Picture6_23_16[30], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 8, y_location + 10 + 8);
    Disp(Picture6_23_16[31], Picture6_23_16[32], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 10, y_location + 10 + 10);
    Disp(Picture6_23_16[33], Picture6_23_16[34], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 12, y_location + 10 + 12);
    Disp(Picture6_23_16[35], Picture6_23_16[36], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 14, y_location + 10 + 14);
    Disp(Picture6_23_16[37], Picture6_23_16[38], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 16, y_location + 10 + 16);
    Disp(Picture6_23_16[39], Picture6_23_16[40], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 18, y_location + 10 + 18);
    Disp(Picture6_23_16[41], Picture6_23_16[42], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 20, y_location + 10 + 20);
    Disp(Picture6_23_16[43], Picture6_23_16[44], color1, color2);
    AMOLED_Block_Write(x_location + 8, x_location + 7 + 8, y_location + 22, y_location + 10 + 22);
    Disp(Picture6_23_16[45], 0x00, color1, color2);
    break;

  case 7:
    for (uint8_t i = 0; i < x1_num; i++)
    {
      // x_location = x_location + (8 * i);
      for (uint8_t j = 0; j < y1_num; j++)
      {
        AMOLED_Block_Write(x_location + (8 * i), x_location + ((8 * i) + 7), y_location + (2 * j), y_location + ((2 * j) + 2));
        if (Return1 == true)
        {
          if ((j + 1) < y1_num)
          {
            Disp(Picture7_60_60[m], Picture7_60_60[m + 1], color1, color2);
            m = m + 2;
          }
          else if ((j + 1) == y1_num)
          {
            Disp(Picture7_60_60[m], 0x00, color1, color2);
            m = m + 1;
          }
        }
        else
        {
          Disp(Picture7_60_60[m], Picture7_60_60[m + 1], color1, color2);
          m = m + 2;
        }
        // delay(Wait_Time);
      }
    }
    break;

  default:
    break;
  }
}

/**
 * 画矩形函数
 * 输入起始点X轴和Y轴，输入长和宽，选择是否需要填充，输入颜色
 * x_location：起始点X，y_location：起始点Y，p_x：矩形长度，p_y：矩形宽度：是否需要填充，color:颜色
 */
void ace_print_rectangle(uint8_t x_location, uint8_t y_location, uint8_t p_x, uint8_t p_y, uint8_t line_wide, bool padding, uint8_t color1)
{
  if (padding == 1)
  {
    AMOLED_Clear(y_location, y_location + p_x, x_location, x_location + p_y, color1);
  }
  else
  {
    AMOLED_Clear(y_location, y_location + p_x, x_location, x_location + p_x, color1);
    AMOLED_Clear(y_location + line_wide, y_location + p_x - line_wide, x_location + line_wide, x_location + p_y - line_wide, 0);
  }
}

/**
 * 画圆形函数
 * 输入起始点X轴和Y轴，输入半径，选择是否需要填充，输入颜色
 * x_location：起始点X，y_location：起始点Y，radius：半径，padding：是否需要填充，color:颜色
 */
void ace_print_round(uint8_t x_location, uint8_t y_location, uint8_t radius, bool padding, uint8_t color)
{
}

/**
 * 蓝牙LOGO图标
 * color1：主要颜色，color2：次要颜色
 */
void DisplayBTlogo(bool i, uint8_t color1, uint8_t color2)
{
  // unsigned char BleLogo8x8[5] = {0x28,0x10,0xFE,0x92,0x6c};
  unsigned char LowerRight[8] = {0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}; // Use 8*8 or 16*16 Logo
  unsigned char LowerLeft[8] = {0x00, 0x00, 0x08, 0x04, 0x02, 0x01, 0xff, 0x80};
  unsigned char UpperRight[8] = {0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00};
  unsigned char UpperLeft[8] = {0x00, 0x00, 0x20, 0x40, 0x80, 0x00, 0xfe, 0x02};
  if (i)
  {
    for (int i = 0; i < 8; i++)
    {
      LowerRight[i] = 0x00;
      LowerLeft[i] = 0x00;
      UpperRight[i] = 0x00;
      UpperLeft[i] = 0x00;
    }
  }
  LCD_font_5_7(LowerLeft, 90, 178, color1, color2);
  LCD_font_5_7(LowerRight, 90, 186, color1, color2);
  LCD_font_5_7(UpperLeft, 98, 178, color1, color2);
  LCD_font_5_7(UpperRight, 98, 186, color1, color2);
}

/**
 * 中文字体显示
 * X：文字显示的X轴，Y：文字显示的Y轴
 * color1：主要颜色，color2：次要颜色
 */
void ace_CHN_Text_Display(uint8_t x, uint8_t y, uint8_t color1, uint8_t color2)
{
}

/**
 * 菜单参数显示
 * color1：主要颜色，color2：次要颜色
 */
void ace_Menu_Display(uint8_t i, uint8_t y, uint8_t x, uint8_t color1, uint8_t color2)
{
  switch (i)
  {
  case 1:                                               // 天气：
    ChN_Font_14(Tempdata15, x, y, color1, color2);      // 写入天
    ChN_Font_14(Tempdata16, x, y + 14, color1, color2); // 写入气
    ChN_Font_14(Tempdata14, x, y + 28, color1, color2); // 写入：
    break;

  case 2:                                               // 里程：
    ChN_Font_14(Tempdata5, x, y, color1, color2);       // 写入里
    ChN_Font_14(Tempdata6, x, y + 14, color1, color2);  // 写入程
    ChN_Font_14(Tempdata14, x, y + 28, color1, color2); // 写入：
    break;

  case 3:                                               // 用时：
    ChN_Font_14(Tempdata11, x, y, color1, color2);      // 写入用
    ChN_Font_14(Tempdata1, x, y + 14, color1, color2);  // 写入时
    ChN_Font_14(Tempdata14, x, y + 28, color1, color2); // 写入：
    break;

  case 4:                                               // 时速
    ChN_Font_14(Tempdata2, x, y, color1, color2);       // 写入时
    ChN_Font_14(Tempdata8, x, y + 14, color1, color2);  // 写入速
    ChN_Font_14(Tempdata14, x, y + 28, color1, color2); // 写入：
    break;

  case 5:                                               // 心率
    ChN_Font_14(Tempdata3, x, y, color1, color2);       // 写入心
    ChN_Font_14(Tempdata4, x, y + 14, color1, color2);  // 写入率
    ChN_Font_14(Tempdata14, x, y + 28, color1, color2); // 写入：
    break;

  case 6:                                               // 踏频
    ChN_Font_14(Tempdata9, x, y, color1, color2);       // 写入踏
    ChN_Font_14(Tempdata10, x, y + 14, color1, color2); // 写入频
    ChN_Font_14(Tempdata14, x, y + 28, color1, color2); // 写入：
    break;

  case 7:                                               // 极速
    ChN_Font_14(Tempdata7, x, y, color1, color2);       // 写入极
    ChN_Font_14(Tempdata8, x, y + 14, color1, color2);  // 写入速
    ChN_Font_14(Tempdata14, x, y + 28, color1, color2); // 写入：
    break;

  case 8:                                               // 爬升
    ChN_Font_14(Tempdata12, x, y, color1, color2);      // 写入爬
    ChN_Font_14(Tempdata13, x, y + 14, color1, color2); // 写入升
    ChN_Font_14(Tempdata14, x, y + 28, color1, color2); // 写入：
    break;

  case 9:                                               // 待办事项
    ChN_Font_14(Tempdata24, x, y, color1, color2);      // 写入待
    ChN_Font_14(Tempdata25, x, y + 14, color1, color2); // 写入办
    ChN_Font_14(Tempdata26, x, y + 28, color1, color2); // 写入事
    ChN_Font_14(Tempdata27, x, y + 42, color1, color2); // 写入项
    ChN_Font_14(Tempdata14, x, y + 56, color1, color2); // 写入：
    break;

  case 10:                                              // 倒计时
    ChN_Font_14(Tempdata9, x, y, color1, color2);       // 写入倒
    ChN_Font_14(Tempdata28, x, y + 14, color1, color2); // 写入计
    ChN_Font_14(Tempdata2, x, y + 28, color1, color2);  // 写入时
    ChN_Font_14(Tempdata14, x, y + 42, color1, color2); // 写入：
    break;

  case 11:                                              // 计时
    ChN_Font_14(Tempdata2, x, y, color1, color2);       // 写入时
    ChN_Font_14(Tempdata8, x, y + 14, color1, color2);  // 写入速
    ChN_Font_14(Tempdata14, x, y + 28, color1, color2); // 写入：
    break;

  case 12:                                              // 周一
    ChN_Font_14(Tempdata30, x, y, color1, color2);      // 写入周
    ChN_Font_14(Tempdata17, x, y + 14, color1, color2); // 写入一
    break;

  case 13:                                              // 周二
    ChN_Font_14(Tempdata30, x, y, color1, color2);      // 写入周
    ChN_Font_14(Tempdata18, x, y + 14, color1, color2); // 写入二
    break;

  case 14:                                              // 周三
    ChN_Font_14(Tempdata30, x, y, color1, color2);      // 写入时
    ChN_Font_14(Tempdata19, x, y + 14, color1, color2); // 写入速
    break;

  case 15:                                              // 周四
    ChN_Font_14(Tempdata30, x, y, color1, color2);      // 写入时
    ChN_Font_14(Tempdata20, x, y + 14, color1, color2); // 写入速
    break;

  case 16:                                              // 周五
    ChN_Font_14(Tempdata30, x, y, color1, color2);      // 写入周
    ChN_Font_14(Tempdata21, x, y + 14, color1, color2); // 写入五
    break;

  case 17:                                              // 周六
    ChN_Font_14(Tempdata30, x, y, color1, color2);      // 写入周
    ChN_Font_14(Tempdata22, x, y + 14, color1, color2); // 写入六
    break;

  case 18:                                              // 周日
    ChN_Font_14(Tempdata30, x, y, color1, color2);      // 写入时
    ChN_Font_14(Tempdata23, x, y + 14, color1, color2); // 写入速
    break;

  case 19:                                              // 晴天
    ChN_Font_14(Tempdata38, x, y, color1, color2);      // 写入晴
    ChN_Font_14(Tempdata15, x, y + 14, color1, color2); // 写入天
    break;

  case 20:                                              // 大雨
    ChN_Font_14(Tempdata31, x, y, color1, color2);      // 写入大
    ChN_Font_14(Tempdata34, x, y + 14, color1, color2); // 写入雨
    break;

  case 21:                                              // 中雨
    ChN_Font_14(Tempdata32, x, y, color1, color2);      // 写入中
    ChN_Font_14(Tempdata34, x, y + 14, color1, color2); // 写入雨
    break;

  case 22:                                              // 小雨
    ChN_Font_14(Tempdata33, x, y, color1, color2);      // 写入小
    ChN_Font_14(Tempdata34, x, y + 14, color1, color2); // 写入雨
    break;

  case 23:                                              // 多云
    ChN_Font_14(Tempdata37, x, y, color1, color2);      // 写入时
    ChN_Font_14(Tempdata36, x, y + 14, color1, color2); // 写入速
    break;

  case 24:                                              // 大雪
    ChN_Font_14(Tempdata31, x, y, color1, color2);      // 写入大
    ChN_Font_14(Tempdata35, x, y + 14, color1, color2); // 写入雪
    break;

  case 25:                                              // 中雪
    ChN_Font_14(Tempdata32, x, y, color1, color2);      // 写入中
    ChN_Font_14(Tempdata35, x, y + 14, color1, color2); // 写入雪
    break;

  case 26:                                              // 小雪
    ChN_Font_14(Tempdata33, x, y, color1, color2);      // 写入小
    ChN_Font_14(Tempdata35, x, y + 14, color1, color2); // 写入雪
    break;

  default:
    break;
  }
}

/**
 * 骑行模式1 显示表盘
 * color1：主要颜色，color2:次要颜色
 */
void ace_Mode1_Display(uint8_t color1, uint8_t color2)
{
  ChN_Font_14(Tempdata11, 50, 14, color1, color2); // 写入用
  ChN_Font_14(Tempdata1, 50, 28, color1, color2);  // 写入时
  ChN_Font_14(Tempdata14, 50, 42, color1, color2); // 写入：

  ChN_Font_14(Tempdata5, 30, 14, color1, color2);  // 写入里
  ChN_Font_14(Tempdata6, 30, 28, color1, color2);  // 写入程
  ChN_Font_14(Tempdata14, 30, 42, color1, color2); // 写入：
}

/**
 * 骑行模式1 显示演示数据
 * color1:主要颜色，color2:次要颜色
 */
void ace_Mode1_Data_Display(uint8_t color1, uint8_t color2)
{
  std::string d_km = "km/h";
  std::string d_time = "00:00";
  std::string d_lc = "320km/h";
  std::string d_time1 = "14:46";

  unsigned char Tempdata0[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00}; // 定义的初始化数组

  CharacterPositionY = 30;
  CharacterPositionX = 85;

  for (int i = 0; i < d_time.length(); i++) // 写入用时
  {
    int index = d_time[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata0[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata0, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata1[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00}; // 定义的初始化数组

  CharacterPositionY = 80;
  CharacterPositionX = 85;

  for (int i = 0; i < d_km.length(); i++) // 写入单位
  {
    int index = d_km[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata1[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 7;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata1, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata2[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00}; // 定义的初始化数组

  CharacterPositionY = 50;
  CharacterPositionX = 35;

  for (int i = 0; i < d_lc.length(); i++) // 写入里程
  {
    int index = d_lc[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata2[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata2, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata3[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00}; // 定义的初始化数组

  CharacterPositionY = 50;
  CharacterPositionX = 55;

  for (int i = 0; i < d_time1.length(); i++) // 写入用时
  {
    int index = d_time1[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata3[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata3, CharacterPositionX, CharacterPositionY, color1, color2);
  }
}

/**
 * 骑行模式2 显示表盘
 * color1：主要颜色，color2:次要颜色
 */
void ace_Mode2_Display(uint8_t color1, uint8_t color2)
{
  ChN_Font_14(Tempdata1, 105, 0, color1, color2);   // 写入时
  ChN_Font_14(Tempdata2, 105, 16, color1, color2);  // 写入间
  ChN_Font_14(Tempdata14, 105, 32, color1, color2); // 写入：

  ChN_Font_14(Tempdata3, 79, 0, color1, color2);   // 写入心
  ChN_Font_14(Tempdata4, 79, 16, color1, color2);  // 写入率
  ChN_Font_14(Tempdata14, 79, 32, color1, color2); // 写入：

  ChN_Font_14(Tempdata5, 44, 0, color1, color2);   // 写入里
  ChN_Font_14(Tempdata6, 44, 16, color1, color2);  // 写入程
  ChN_Font_14(Tempdata14, 44, 32, color1, color2); // 写入：

  ChN_Font_14(Tempdata7, 14, 0, color1, color2);   // 写入极
  ChN_Font_14(Tempdata8, 14, 16, color1, color2);  // 写入速
  ChN_Font_14(Tempdata14, 14, 32, color1, color2); // 写入：

  ChN_Font_14(Tempdata9, 79, 55, color1, color2);  // 写入踏
  ChN_Font_14(Tempdata10, 79, 71, color1, color2); // 写入频
  ChN_Font_14(Tempdata14, 79, 87, color1, color2); // 写入：

  ChN_Font_14(Tempdata11, 44, 55, color1, color2); // 写入用
  ChN_Font_14(Tempdata1, 44, 71, color1, color2);  // 写入时
  ChN_Font_14(Tempdata14, 44, 87, color1, color2); // 写入：

  ChN_Font_14(Tempdata12, 14, 55, color1, color2); // 写入爬
  ChN_Font_14(Tempdata13, 14, 71, color1, color2); // 写入升
  ChN_Font_14(Tempdata14, 14, 87, color1, color2); // 写入：
}

/**
 * 骑行模式2 显示演示数据
 * color1:主要颜色，color2:次要颜色
 */
void ace_Mode2_Data_Display(uint8_t color1, uint8_t color2)
{

  std::string d_time = "15:30";
  std::string d_tp = "15/s";
  std::string d_heart = "160";
  std::string d_speed = "25km/h";
  std::string d_ps = "30";
  std::string d_ys = "15min";
  std::string d_lc = "12km";

  unsigned char Tempdata1[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00}; // 定义的初始化数组

  CharacterPositionY = 50;
  CharacterPositionX = 104;

  for (int i = 0; i < d_time.length(); i++) // 写入时间
  {
    int index = d_time[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata1[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata1, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata2[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00};

  CharacterPositionY = 0;
  CharacterPositionX = 66;

  for (int i = 0; i < d_heart.length(); i++) // 写入心率
  {
    int index = d_heart[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata2[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata2, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata3[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00};

  CharacterPositionY = 0;
  CharacterPositionX = 6;

  for (int i = 0; i < d_speed.length(); i++) // 写入极速
  {
    int index = d_speed[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata3[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata3, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata4[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00};

  CharacterPositionY = 60;
  CharacterPositionX = 66;

  for (int i = 0; i < d_tp.length(); i++) // 写入踏频
  {
    int index = d_tp[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata4[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata4, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata5[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00};

  CharacterPositionY = 60;
  CharacterPositionX = 35;

  for (int i = 0; i < d_ys.length(); i++) // 写入用时
  {
    int index = d_ys[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata5[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata5, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata6[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00};

  CharacterPositionY = 60;
  CharacterPositionX = 6;

  for (int i = 0; i < d_ps.length(); i++) // 写入爬升
  {
    int index = d_ps[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata6[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata6, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata7[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00};

  CharacterPositionY = 0;
  CharacterPositionX = 35;

  for (int i = 0; i < d_lc.length(); i++) // 写入里程
  {
    int index = d_lc[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata7[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata7, CharacterPositionX, CharacterPositionY, color1, color2);
  }
}

/**
 * 日常模式1 显示表盘
 * color1：主要颜色，color2:次要颜色
 */
void ace_Mode3_Display(uint8_t color1, uint8_t color2)
{
  ace_Menu_Display(9, 5, 65, 2, 0);
}

/**
 * 日常模式1 显示演示数据
 * color1:主要颜色，color2:次要颜色
 */
void ace_Mode3_Data_Display(uint8_t color1, uint8_t color2)
{
  std::string d_time = "15:30";
  std::string d_tp = "12/15";
  std::string d_heart = "27°";
  std::string d_speed = "25km/h";
  std::string d_ps = "30";
  std::string d_ys = "15min";
  std::string d_lc = "12km";

  unsigned char Tempdata1[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00}; // 定义的初始化数组

  CharacterPositionY = 0;
  CharacterPositionX = 110;

  for (int i = 0; i < d_time.length(); i++) // 写入时间
  {
    int index = d_time[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata1[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata1, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata4[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00};

  CharacterPositionY = 50;
  CharacterPositionX = 110;

  for (int i = 0; i < d_tp.length(); i++) // 
  {
    int index = d_tp[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata4[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata4, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  unsigned char Tempdata5[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00};

  CharacterPositionY = 100;
  CharacterPositionX = 110;

  for (int i = 0; i < d_heart.length(); i++) // 写入踏频
  {
    int index = d_heart[i] - ' ';
    for (int i = 0; i < 5; i++)
    {
      Tempdata5[i] = font_5_8[index][i];
    }

    CharacterPositionY = CharacterPositionY + 8;
    if (CharacterPositionY > 116)
    {
      CharacterPositionX = CharacterPositionX - 8;
      CharacterPositionY = 0;
    }
    LCD_font_5_7(Tempdata5, CharacterPositionX, CharacterPositionY, color1, color2);
  }

  ace_Menu_Display(23, 86, 85, 1, 0); // 多云
  ace_Menu_Display(16, 53, 85, 1, 0); // 周五
}

/**
 * 导航模式1 显示表盘
 * color1：主要颜色，color2:次要颜色
 */
void ace_Mode4_Navigation1_Display(uint8_t color1, uint8_t color2)
{
  ChN_Font_14(Tempdata11, 44, 55, color1, color2); // 写入用
  ChN_Font_14(Tempdata1, 44, 71, color1, color2);  // 写入时
  ChN_Font_14(Tempdata14, 44, 87, color1, color2); // 写入：

  ChN_Font_14(Tempdata5, 44, 0, color1, color2);   // 写入里
  ChN_Font_14(Tempdata6, 44, 16, color1, color2);  // 写入程
  ChN_Font_14(Tempdata14, 44, 32, color1, color2); // 写入：
}

/**
 * 导航模式1 显示演示数据
 * color1:主要颜色，color2:次要颜色
 */
void ace_Mode4_Navigation1_Data_Display(uint8_t color1, uint8_t color2)
{
}

/**
 * 导航模式2 显示表盘
 * color1：主要颜色，color2:次要颜色
 */
void ace_Mode5_Navigation2_Display(uint8_t color1, uint8_t color2)
{
  ChN_Font_14(Tempdata11, 44, 55, color1, color2); // 写入用
  ChN_Font_14(Tempdata1, 44, 71, color1, color2);  // 写入时
  ChN_Font_14(Tempdata14, 44, 87, color1, color2); // 写入：

  ChN_Font_14(Tempdata5, 44, 0, color1, color2);   // 写入里
  ChN_Font_14(Tempdata6, 44, 16, color1, color2);  // 写入程
  ChN_Font_14(Tempdata14, 44, 32, color1, color2); // 写入：
}

/**
 * 导航模式2 显示演示数据
 * color1:主要颜色，color2:次要颜色
 */
void ace_Mode5_Navigation2_Data_Display(uint8_t color1, uint8_t color2)
{
}

/**
 * 计时模式 显示表盘
 * color1：主要颜色，color2:次要颜色
 */
void ace_Mode6_Time_Display(uint8_t color1, uint8_t color2)
{
  ChN_Font_14(Tempdata11, 44, 55, color1, color2); // 写入用
  ChN_Font_14(Tempdata1, 44, 71, color1, color2);  // 写入时
  ChN_Font_14(Tempdata14, 44, 87, color1, color2); // 写入：

  ChN_Font_14(Tempdata5, 44, 0, color1, color2);   // 写入里
  ChN_Font_14(Tempdata6, 44, 16, color1, color2);  // 写入程
  ChN_Font_14(Tempdata14, 44, 32, color1, color2); // 写入：
}

/**
 * 计时模式 显示演示数据
 * color1:主要颜色，color2:次要颜色
 */
void ace_Mode6_Time_Data_Display(uint8_t color1, uint8_t color2)
{
}