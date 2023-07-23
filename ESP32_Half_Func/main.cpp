#include <Arduino.h>
#include <SPI.h>//Ref. https://www.arduino.cn/thread-106240-1-1.html
#include <BLEDevice.h>//Ref. https://blog.csdn.net/weixin_42880082/article/details/120534190
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <driver/touch_pad.h>
#include <esp_sleep.h>

/**
 * Define IO for AMOLED
 */
#define CS_PIN 6 
#define HSPI_MISO 16
#define HSPI_MOSI 17
#define HSPI_SCLK 18
#define CD_PIN 7 
#define Rst_PIN 8 

/*
6   CS_PIN
7   CD_PIN
8   MOSI
9   
10  SCLK
11  
12  Rst_PIN
13  
*/

/**
 * Define parameters for BLE communication
 */
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
BLECharacteristic *pCharacteristic;
uint8_t CharacterPositionX=112,CharacterPositionY=0;
bool BatteryState=false;

const int TOUCH_PIN = 2; //触摸引脚

#define Display false
#define NotDisplay true
/**
 * Write command to AMOLED Screen
 */
void WriteComm(unsigned int i)
{
	digitalWrite(CS_PIN,LOW);//片选拉低
    
	digitalWrite(CD_PIN,LOW);//C/D拉低

	SPI.transfer(i);

	digitalWrite(CS_PIN,HIGH);//片选拉高

}

/**
 * Write Data to AMOLED Screen
 */
void WriteData(unsigned int i)
{
	digitalWrite(CS_PIN,LOW);//片选拉低

	digitalWrite(CD_PIN,HIGH);//C/D拉高

	SPI.transfer(i);

	digitalWrite(CS_PIN,HIGH);//片选拉高
}

/**
 * Define display location at screen
 */
void AMOLED_Block_Write(uint16_t Xstart,uint16_t Xend,uint16_t Ystart,uint16_t Yend)
{	
	WriteComm(0x2a);  //Set Column Start Address 
	WriteData(Xstart>>8);
	WriteData(Xstart&0xff);
	WriteData(Xend>>8);
	WriteData(Xend&0xff);

	WriteComm(0x2b); //Set Row Start Address  
	WriteData(Ystart>>8);
	WriteData(Ystart&0xff);
	WriteData(Yend>>8);
	WriteData(Yend&0xff);

	WriteComm(0x2c); //Memory Write
}

/**
 * Write a single Pixel
 */
void Write_Disp_Data(uint16_t i)
{ 
	digitalWrite(CS_PIN,LOW);//片选拉低

	digitalWrite(CD_PIN,HIGH);// CD拉高

	SPI.transfer(i);

	digitalWrite(CS_PIN,HIGH);//片选拉高
}

/**
 * 两行写入
 */
void Disp(uint8_t Temp_M,uint8_t Temp_L)
{
		uint8_t j;

		for(j=0;j<8;j++)
		{
			if (Temp_M & (0x80 >> (j % 8))) {
				Write_Disp_Data(0xffff);
				Write_Disp_Data(0xffff);
				Write_Disp_Data(0xffff);
			} else {
				Write_Disp_Data(0x0000);
				Write_Disp_Data(0x0000);
				Write_Disp_Data(0x0000);
			}
		}

		for(j=0;j<8;j++)
		{
			if (Temp_L & (0x80 >> (j % 8))) {
				Write_Disp_Data(0xffff);
				Write_Disp_Data(0xffff);
				Write_Disp_Data(0xffff);
			} else {
				Write_Disp_Data(0x0000);
				Write_Disp_Data(0x0000);
				Write_Disp_Data(0x0000);
			}
		}
}

/**
 * 将6行拆成3份
 */
void LCD_font_5_7(unsigned char Tempdata[8],uint8_t CharacterPositionX,uint8_t CharacterPositionY)
{	

		AMOLED_Block_Write(CharacterPositionX,CharacterPositionX+7,CharacterPositionY  ,CharacterPositionY+10);
		Disp(Tempdata[0],Tempdata[1]);

		AMOLED_Block_Write(CharacterPositionX,CharacterPositionX+7,CharacterPositionY+2,CharacterPositionY+10);
		Disp(Tempdata[2],Tempdata[3]);

		AMOLED_Block_Write(CharacterPositionX,CharacterPositionX+7,CharacterPositionY+4,CharacterPositionY+10);
		Disp(Tempdata[4],Tempdata[5]);

		AMOLED_Block_Write(CharacterPositionX,CharacterPositionX+7,CharacterPositionY+6,CharacterPositionY+10);
		Disp(Tempdata[6],Tempdata[7]);
}

void AMOLED_Clear(uint8_t ColumnStart, uint16_t ColumnEnd,uint8_t RowStart,uint16_t RowEnd,uint16_t color)
{  	
	uint16_t i,j;
	
	AMOLED_Block_Write(ColumnStart,ColumnEnd,RowStart,RowEnd);

	for(i=0;i<ColumnEnd;i++)//ColumnEnd-ColumnStart
		for(j=0;j<RowEnd;j++)//RowEnd-RowStart
			{
				Write_Disp_Data(color);Write_Disp_Data(color);Write_Disp_Data(color);
			}

}

void DisplayBTlogo(bool i)
{ 
    //unsigned char BleLogo8x8[5] = {0x28,0x10,0xFE,0x92,0x6c};
    unsigned char LowerRight[8]={0x42,0x24,0x18,0x00,0x00,0x00,0x00,0x00};//Use 8*8 or 16*16 Logo 
    unsigned char  LowerLeft[8]={0x00,0x00,0x08,0x04,0x02,0x01,0xff,0x80};
    unsigned char UpperRight[8]={0x42,0x24,0x18,0x00,0x00,0x00,0x00,0x00};
    unsigned char  UpperLeft[8]={0x00,0x00,0x20,0x40,0x80,0x00,0xfe,0x02};
    if(i){
        for (int i = 0; i < 8; i++) {
            LowerRight[i] = 0x00;
            LowerLeft[i] = 0x00;
            UpperRight[i] = 0x00;
            UpperLeft[i] = 0x00;
        }
    }
    LCD_font_5_7(LowerLeft,90,178);
    LCD_font_5_7(LowerRight,90,186);
    LCD_font_5_7(UpperLeft,98,178);
    LCD_font_5_7(UpperRight,98,186);
}




/**
 * Display Battery value
 */
void Battery_Manage(uint16_t color){
  int adcValue;
  adcValue = analogRead(4) -1830;//分压电阻二分之一，2.1v时2600  1.5v时1830  共770个刻度 
  //Serial.print(adcValue);
    if (adcValue > 15)
      AMOLED_Clear(22,30,180,190,color);
    if (adcValue > 154)
      AMOLED_Clear(34,42,180,190,color);
    if (adcValue > 308)
      AMOLED_Clear(46,54,180,190,color);
    if (adcValue > 462)
      AMOLED_Clear(58,66,180,190,color);
    if (adcValue > 616)
      AMOLED_Clear(70,74,182,188,color);

}

void OLED_Init(void)
{	
	digitalWrite(Rst_PIN,HIGH);//RST=1;  
	delay(30);

 //========turly0.95_code=====69310=============// 
 
WriteComm(0xFE);WriteData(0x01);
WriteComm(0x04);WriteData(0xa0);  //SPI write ram enable
WriteComm(0x05);WriteData(0x70);  //128RGB);;LCDSPI_InitDAT( T->B);;LCDSPI_InitDAT( NW
WriteComm(0x06);WriteData(0x3C);  //NL = 240 line
WriteComm(0x25);WriteData(0x06);  //normal mode: gamma1);;LCDSPI_InitDAT( 24bit   
WriteComm(0x26);WriteData(0x80);  //T1A = 280(640 * 100ns = 64us);   
WriteComm(0x27);WriteData(0x12);  //normal mode VBP = 12   0c
WriteComm(0x28);WriteData(0x12);  //normal mode VFP = 8    08
WriteComm(0x2A);WriteData(0x06);  //idle mode: gamma1);;LCDSPI_InitDAT( 24bit
WriteComm(0x2B);WriteData(0x80);  //T1B = 280(640 * 100ns = 64us);
WriteComm(0x2D);WriteData(0x12);  //idle mode VBP = 12   0c
WriteComm(0x2F);WriteData(0x12);  //idle mode VFP = 8    08
WriteComm(0x37);WriteData(0x0C);  //precharge to VGSP);;LCDSPI_InitDAT( mux 1:6
WriteComm(0x6D);WriteData(0x18);  //skip frame VGMP and VGSP regulator off
WriteComm(0x29);WriteData(0x01);  //normal mode skip frame off
WriteComm(0x30);WriteData(0x43);  //idle mode skip frame = 60/2 = 30Hz
WriteComm(0x0E);WriteData(0x83);  //AVDD = 5.6V normal mode
WriteComm(0x0F);WriteData(0x83);  //AVDD = 5.6V idle mode
WriteComm(0x10);WriteData(0x71);  //AVDD = 3xVCI);;LCDSPI_InitDAT( AVDD regulator enable);;LCDSPI_InitDAT(VCL regulator enable
WriteComm(0x11);WriteData(0xb3);  //VCL = -2xVCI);;LCDSPI_InitDAT( normal mode
WriteComm(0x12);WriteData(0xb3);  //VCL = -2xVCI);;LCDSPI_InitDAT( idle mode
WriteComm(0x13);WriteData(0x80);  //VGH = AVDD normal mode
WriteComm(0x14);WriteData(0x80);  //VGH = AVDD idle mode
WriteComm(0x15);WriteData(0x81);  //VGL = VCL - VCI normal mode
WriteComm(0x16);WriteData(0x81);  //VGL = VCL - VCI idle mode
WriteComm(0x18);WriteData(0x66);  //VGHR = 6V normal/idle mode
WriteComm(0x19);WriteData(0x44);  //VGLR =  -6V normal/idle mode
WriteComm(0x1E);WriteData(0x02);  //Switch EQ on
WriteComm(0x5B);WriteData(0x10);  //VREFN5 on
WriteComm(0x62);WriteData(0x19);  //VREFN5 = -3V normal mode
WriteComm(0x63);WriteData(0x19);  //VREFN5 = -3V idle mode
WriteComm(0x70);WriteData(0x55);  //display off SD to AVDD);;LCDSPI_InitDAT( display on SD to AVDD
WriteComm(0x1D);WriteData(0x02);  //Switch EQ on
WriteComm(0x89);WriteData(0x18);  //VGMP =118 );;LCDSPI_InitDAT(5.5V
WriteComm(0x8A);WriteData(0xb9);  //VGSP = 090 );;LCDSPI_InitDAT(2V
WriteComm(0x8B);WriteData(0x01);  //VGMP VGSP high byte
WriteComm(0x8C);WriteData(0x10);  //VGMP = 110 );;LCDSPI_InitDAT(5.4V
WriteComm(0x8D);WriteData(0x90);  //VGSP = 090 );;LCDSPI_InitDAT(2V
WriteComm(0x8E);WriteData(0x01);  //VGMP VGSP high byte
WriteComm(0x6E);WriteData(0x0A);  //MIPI interface off
WriteComm(0x6A);WriteData(0x05); //MUX               
WriteComm(0x3A);WriteData(0x08);  //T1_sd
WriteComm(0x3B);WriteData(0x00);  //Tp_sd
WriteComm(0x3D);WriteData(0x16);  //Th_sd
WriteComm(0x3F);WriteData(0x27);  //Tsw_sd
WriteComm(0x40);WriteData(0x0F);  //Thsw_sd
WriteComm(0x41);WriteData(0x0D);  //Thsd_sd
                          
WriteComm(0x42);WriteData(0x14);  //Mux 142536);;LCDSPI_InitDAT( odd/even line SWAP
WriteComm(0x43);WriteData(0x41);
WriteComm(0x44);WriteData(0x25);
WriteComm(0x45);WriteData(0x52);
WriteComm(0x46);WriteData(0x36);
WriteComm(0x47);WriteData(0x63);
WriteComm(0x48);WriteData(0x14);
WriteComm(0x49);WriteData(0x41);
WriteComm(0x4A);WriteData(0x25);
WriteComm(0x4B);WriteData(0x52);
WriteComm(0x4C);WriteData(0x36);
WriteComm(0x4D);WriteData(0x63);
WriteComm(0x4E);WriteData(0x14); //Data R1R2G1G2B1B2);;LCDSPI_InitDAT( odd/even line SWAP
WriteComm(0x4F);WriteData(0x41);
WriteComm(0x50);WriteData(0x25);
WriteComm(0x51);WriteData(0x52);
WriteComm(0x52);WriteData(0x36);
WriteComm(0x53);WriteData(0x63);
WriteComm(0x54);WriteData(0x14);
WriteComm(0x55);WriteData(0x41);
WriteComm(0x56);WriteData(0x25);
WriteComm(0x57);WriteData(0x52);
WriteComm(0x58);WriteData(0x36);
WriteComm(0x59);WriteData(0x63);
                          
WriteComm(0x66);WriteData(0x90);  //idle mode internal power
WriteComm(0x67);WriteData(0x40);  //internal power delay 1 frame off
WriteComm(0x72);WriteData(0x1A);  //internal OVDD = 4.6V
WriteComm(0x73);WriteData(0x07);  //internal OVSS = -2V
WriteComm(0x74);WriteData(0x0C);  //OVDD power from AVDD);;LCDSPI_InitDAT( source power from AVDD
WriteComm(0x6A);WriteData(0x3D);  //swire 61=0x3D pulse);;LCDSPI_InitDAT( 4.6V for SGM38042
WriteComm(0x6B);WriteData(0x29);  //swire 41=0x29 pulse);;LCDSPI_InitDAT( -2.4V for SGM38042
                          
WriteComm(0xFE);WriteData(0x04);
WriteComm(0x5E);WriteData(0x01);
WriteComm(0x5F);WriteData(0xB8);
WriteComm(0x60);WriteData(0xBB);
WriteComm(0x61);WriteData(0xBB);
WriteComm(0x62);WriteData(0xBB);
WriteComm(0x76);WriteData(0xBB);
WriteComm(0x77);WriteData(0x3B);
WriteComm(0x78);WriteData(0x92);
WriteComm(0x79);WriteData(0xBB);
WriteComm(0x7A);WriteData(0xBB);
                          
WriteComm(0x00);WriteData(0xDC);  //SN_CK1
WriteComm(0x01);WriteData(0x00);
WriteComm(0x02);WriteData(0x02);
WriteComm(0x03);WriteData(0x00);
WriteComm(0x04);WriteData(0x08);
WriteComm(0x05);WriteData(0x01);
WriteComm(0x06);WriteData(0x70);
WriteComm(0x07);WriteData(0x0A);
WriteComm(0x08);WriteData(0x00);
                          
WriteComm(0x09);WriteData(0xDC);  //SN_CK2
WriteComm(0x0a);WriteData(0x00);
WriteComm(0x0b);WriteData(0x02);
WriteComm(0x0C);WriteData(0x00);
WriteComm(0x0D);WriteData(0x08);
WriteComm(0x0E);WriteData(0x00);
WriteComm(0x0F);WriteData(0x70);
WriteComm(0x10);WriteData(0x0A);
WriteComm(0x11);WriteData(0x00);
                          
WriteComm(0x12);WriteData(0xCC);  //EM_CK1
WriteComm(0x13);WriteData(0x00);
WriteComm(0x14);WriteData(0x02);
WriteComm(0x15);WriteData(0x00);
WriteComm(0x16);WriteData(0x20);
WriteComm(0x17);WriteData(0x00);
WriteComm(0x18);WriteData(0x28);
WriteComm(0x19);WriteData(0x26);
WriteComm(0x1A);WriteData(0x00);
                          
WriteComm(0x1B);WriteData(0xCC);  //EM_CK2
WriteComm(0x1C);WriteData(0x00);
WriteComm(0x1D);WriteData(0x02);
WriteComm(0x1E);WriteData(0x00);
WriteComm(0x1F);WriteData(0x20);
WriteComm(0x20);WriteData(0x01);
WriteComm(0x21);WriteData(0x28);
WriteComm(0x22);WriteData(0x26);
WriteComm(0x23);WriteData(0x00);
                          
WriteComm(0x4C);WriteData(0x89);  //SN_STV
WriteComm(0x4D);WriteData(0x00);
WriteComm(0x4E);WriteData(0x01);
WriteComm(0x4F);WriteData(0x00);
WriteComm(0x50);WriteData(0x01);
WriteComm(0x51);WriteData(0xBB);
WriteComm(0x52);WriteData(0xBB);
                          
WriteComm(0x53);WriteData(0xCA);  //EM_STV
WriteComm(0x54);WriteData(0x00);
WriteComm(0x55);WriteData(0x03);
WriteComm(0x56);WriteData(0x00);
WriteComm(0x58);WriteData(0x00);
WriteComm(0x59);WriteData(0x00);
WriteComm(0x65);WriteData(0x45);  //04
WriteComm(0x66);WriteData(0x0C);  //03
WriteComm(0x67);WriteData(0x00);  //10
                          
WriteComm(0xFE);WriteData(0x01);//ID
WriteComm(0xE5);WriteData(0x00);
WriteComm(0xE6);WriteData(0x10);
WriteComm(0xE7);WriteData(0x31);
WriteComm(0xFE);WriteData(0x00);
WriteComm(0xC4);WriteData(0x80);
WriteComm(0x2A);WriteData(0x00);WriteData(0x04);WriteData(0x00);WriteData(0x7B);

WriteComm(0x11);WriteData(0x00);
delay(150);
WriteComm(0x29);WriteData(0x00);
}

/**
 * Font Area
 */
char font_5_8[][5] = {
        /*
        * delta = SPCACE(0x20)
        */
        0x00, 0x00, 0x00, 0x00, 0x00, // SPACE
        0x00, 0x00, 0x4f, 0x00, 0x00, // !
        0x00, 0x07, 0x00, 0x07, 0x00, // "
        0x14, 0x7f, 0x14, 0x7f, 0x14, // #
        0x24, 0x2a, 0x7f, 0x2a, 0x12, // $
        0x23, 0x13, 0x08, 0x64, 0x62, // %
        0x36, 0x49, 0x55, 0x22, 0x50, // &
        0x00, 0x05, 0x03, 0x00, 0x00, // '
        0x00, 0x1c, 0x22, 0x41, 0x00, // (
        0x00, 0x41, 0x22, 0x1c, 0x00, // )
        0x14, 0x08, 0x3e, 0x08, 0x14, // *
        0x08, 0x08, 0x3e, 0x08, 0x08, // +
        0x00, 0x50, 0x30, 0x00, 0x00, // ,
        0x08, 0x08, 0x08, 0x08, 0x08, // -
        0x00, 0x60, 0x60, 0x00, 0x00, // .
        0x20, 0x10, 0x08, 0x04, 0x02, // /
        0x3e, 0x51, 0x49, 0x45, 0x3e, // 0
        0x00, 0x42, 0x7f, 0x40, 0x00, // 1
        0x42, 0x61, 0x51, 0x49, 0x46, // 2
        0x21, 0x41, 0x45, 0x4b, 0x31, // 3
        0x18, 0x14, 0x12, 0x7f, 0x10, // 4
        0x27, 0x45, 0x45, 0x45, 0x39, // 5
        0x3c, 0x4a, 0x49, 0x49, 0x30, // 6
        0x01, 0x71, 0x09, 0x05, 0x03, // 7
        0x36, 0x49, 0x49, 0x49, 0x36, // 8
        0x06, 0x49, 0x49, 0x29, 0x1e, // 9
        0x00, 0x36, 0x36, 0x00, 0x00, // :
        0x00, 0x56, 0x36, 0x00, 0x00, // ;
        0x08, 0x14, 0x22, 0x41, 0x00, // <
        0x14, 0x14, 0x14, 0x14, 0x14, // =
        0x00, 0x41, 0x22, 0x14, 0x08, // >
        0x02, 0x01, 0x51, 0x09, 0x06, // ?
        0x32, 0x49, 0x79, 0x41, 0x3e, // @
        0x7e, 0x11, 0x11, 0x11, 0x7e, // A
        0x7f, 0x49, 0x49, 0x49, 0x36, // B
        0x3e, 0x41, 0x41, 0x41, 0x22, // C
        0x7f, 0x41, 0x41, 0x22, 0x1c, // D
        0x7f, 0x49, 0x49, 0x49, 0x41, // E
        0x7f, 0x09, 0x09, 0x09, 0x01, // F
        0x3e, 0x41, 0x49, 0x49, 0x7a, // G
        0x7f, 0x08, 0x08, 0x08, 0x7f, // H
        0x00, 0x41, 0x7f, 0x41, 0x00, // I
        0x20, 0x40, 0x41, 0x3f, 0x01, // J
        0x7f, 0x08, 0x14, 0x22, 0x41, // K
        0x7f, 0x40, 0x40, 0x40, 0x40, // L
        0x7f, 0x02, 0x0c, 0x02, 0x7f, // M
        0x7f, 0x04, 0x08, 0x10, 0x7f, // N
        0x3e, 0x41, 0x41, 0x41, 0x3e, // O
        0x7f, 0x09, 0x09, 0x09, 0x06, // P
        0x3e, 0x41, 0x51, 0x21, 0x5e, // Q
        0x7f, 0x09, 0x19, 0x29, 0x46, // R
        0x46, 0x49, 0x49, 0x49, 0x31, // S
        0x01, 0x01, 0x7f, 0x01, 0x01, // T
        0x3f, 0x40, 0x40, 0x40, 0x3f, // U
        0x1f, 0x20, 0x40, 0x20, 0x1f, // V
        0x3f, 0x40, 0x38, 0x40, 0x3f, // W
        0x63, 0x14, 0x08, 0x14, 0x63, // X
        0x07, 0x08, 0x70, 0x08, 0x07, // Y
        0x61, 0x51, 0x49, 0x45, 0x43, // Z
        0x00, 0x7f, 0x41, 0x41, 0x00, // [
        0x02, 0x04, 0x08, 0x10, 0x20, //
        0x00, 0x41, 0x41, 0x7f, 0x00, // ]
        0x04, 0x02, 0x01, 0x02, 0x04, // ^
        0x40, 0x40, 0x40, 0x40, 0x40, // _
        0x00, 0x01, 0x02, 0x04, 0x00, // `
        0x20, 0x54, 0x54, 0x54, 0x78, // a
        0x7f, 0x48, 0x44, 0x44, 0x38, // b
        0x38, 0x44, 0x44, 0x44, 0x20, // c
        0x38, 0x44, 0x44, 0x48, 0x7f, // d
        0x38, 0x54, 0x54, 0x54, 0x18, // e
        0x08, 0x7e, 0x09, 0x01, 0x02, // f
        0x0c, 0x52, 0x52, 0x52, 0x3e, // g
        0x7f, 0x08, 0x04, 0x04, 0x78, // h
        0x00, 0x44, 0x7d, 0x40, 0x00, // i
        0x20, 0x40, 0x44, 0x3d, 0x00, // j
        0x7f, 0x10, 0x28, 0x44, 0x00, // k
        0x00, 0x41, 0x7f, 0x40, 0x00, // l
        0x7c, 0x04, 0x18, 0x04, 0x78, // m
        0x7c, 0x08, 0x04, 0x04, 0x78, // n
        0x38, 0x44, 0x44, 0x44, 0x38, // o
        0x7c, 0x14, 0x14, 0x14, 0x08, // p
        0x08, 0x14, 0x14, 0x18, 0x7c, // q
        0x7c, 0x08, 0x04, 0x04, 0x08, // r
        0x48, 0x54, 0x54, 0x54, 0x20, // s
        0x04, 0x3f, 0x44, 0x40, 0x20, // t
        0x3c, 0x40, 0x40, 0x20, 0x7c, // u
        0x1c, 0x20, 0x40, 0x20, 0x1c, // v
        0x3c, 0x40, 0x30, 0x40, 0x3c, // w
        0x44, 0x28, 0x10, 0x28, 0x44, // x
        0x0c, 0x50, 0x50, 0x50, 0x3c, // y
        0x44, 0x64, 0x54, 0x4c, 0x44, // z
        0x00, 0x08, 0x36, 0x41, 0x00, // {
        0x00, 0x00, 0x7f, 0x00, 0x00, // |
        0x00, 0x41, 0x36, 0x08, 0x00, // }
        0x08, 0x04, 0x08, 0x10, 0x08, // ~
};

/**
 * Only for Navigation Display
 */
void DisplayNavigationPrompt(std::string  Meter)//这个配置下一行15个
{ 
    unsigned char Tempdata[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    //unsigned char PositionY=36;

    unsigned char PositionY=26;
    for (int i = 0; i < Meter.length(); i++) {
        int index = Meter[i] - ' '; 
        for (int i = 0; i < 5; i++) {
        Tempdata[i] = font_5_8[index][i];
        }
        PositionY = PositionY + 8;
        LCD_font_5_7(Tempdata,60,PositionY);          
    }
}

/**
 * Only for Navigation Display
 */
void DisplayString(std::string  Meter)//这个配置下一行15个
{ 
        unsigned char Tempdata[8]={0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00};
 
        for (int i = 0; i < Meter.length(); i++) {
            int index = Meter[i] - ' '; 
            for (int i = 0; i < 5; i++) {
            Tempdata[i] = font_5_8[index][i];
            }
            CharacterPositionY = CharacterPositionY + 8;
            if(CharacterPositionY >116)
            {
                CharacterPositionX = CharacterPositionX-8;
                CharacterPositionY=0;
            }
            LCD_font_5_7(Tempdata,CharacterPositionX,CharacterPositionY);          
        }
}

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        DisplayBTlogo(NotDisplay);
    };
 
    void onDisconnect(BLEServer* pServer) {
      pServer->getAdvertising()->start();//Restart Advertising
        DisplayBTlogo(Display);
    }
};
/**
 *  
 */
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      //DisplayNavigationPrompt(rxValue);

        unsigned char Tempdata[8]={0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00};
 
        for (int i = 0; i < rxValue.length(); i++) {
            int index = rxValue[i] - ' '; 
            for (int i = 0; i < 5; i++) {
            Tempdata[i] = font_5_8[index][i];
            }
            CharacterPositionY = CharacterPositionY + 8;
            if(CharacterPositionY >116)
            {
                CharacterPositionX = CharacterPositionX-8;
                CharacterPositionY=0;
            }
            LCD_font_5_7(Tempdata,CharacterPositionX,CharacterPositionY);          
        
        }
        
    }
};

/**
 * Belong to DisplayTriangle
 * Display a Forward Arrow
 */
void DisplayForwardArrow(unsigned char square[8])
{ 
    unsigned char ForwardTriangleA[8]   ={0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};
    unsigned char ForwardTriangleB[8]   ={0xfe,0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80};
    LCD_font_5_7(square,40,50);
    LCD_font_5_7(ForwardTriangleA,46,46);
    LCD_font_5_7(ForwardTriangleB,46,53);
}

/**
 * Belong to DisplayTriangle
 * Display a Forward Arrow
 */
void DisplayTurnLeftArrow(unsigned char square[8])
{ 
    unsigned char UpperLeftTriangle[8]  ={0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};//这里可以用交叉取反方法节省一个数组，知道上半边后计算得到下半边
    unsigned char LowerLeftTriangle[8]  ={0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};

    LCD_font_5_7(square,40,44);
    LCD_font_5_7(square,40,50);
    LCD_font_5_7(UpperLeftTriangle,44,36);
    LCD_font_5_7(LowerLeftTriangle,36,36);
}

/**
 * Belong to DisplayTriangle
 * Display a Turn Right Arrow
 */
void DisplayTurnRightArrow(unsigned char square[8])
{ 
    unsigned char UpperRightTriangle[8] ={0xff,0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80};//这里可以用交叉取反方法节省一个数组，知道上半边后计算得到下半边
    unsigned char LowerRightTriangle[8] ={0xff,0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01};
    LCD_font_5_7(square,40,50);
    LCD_font_5_7(square,40,56);
    LCD_font_5_7(UpperRightTriangle,44,62);
    LCD_font_5_7(LowerRightTriangle,36,62);
}

/**
 * Clear Display
 * 1=Clean all
 * 0=Arrow only
 */
void ClearArrowDisplay(bool CleanALL)
{ 
    unsigned char Blacksquare[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//定义一个方块
    if(CleanALL)
    {
        LCD_font_5_7(Blacksquare,24,50);
        LCD_font_5_7(Blacksquare,32,50);
    }
    LCD_font_5_7(Blacksquare,40,44);
    LCD_font_5_7(Blacksquare,40,50);
    LCD_font_5_7(Blacksquare,40,56);
    LCD_font_5_7(Blacksquare,44,62);//UpperRightTriangle
    LCD_font_5_7(Blacksquare,36,62);//LowerRightTriangle
    LCD_font_5_7(Blacksquare,44,36);//UpperLeftTriangle
    LCD_font_5_7(Blacksquare,36,36);//LowerLeftTriangle
    LCD_font_5_7(Blacksquare,46,46);//ForwardTriangleA
    LCD_font_5_7(Blacksquare,46,54);//ForwardTriangleB
}
/**
 * Navigation display
 * 1=Forward  2=Right  3=Left  4=Undisplay
 */
void DisplayTriangle(uint8_t i)
{ 
unsigned char square[8]={0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00};//定义一个方块
LCD_font_5_7(square,24,50);//绘制主干
LCD_font_5_7(square,32,50);

ClearArrowDisplay(false);
//这里还有Bug，晚点改
}

void DispSpeed()
{
//这里还有Bug，晚点改②
}

/**
 *  Setup BLE
 */
void BLEseverSetup()
{
  // Create the BLE Device
  BLEDevice::init("LittleAR"); 
  
  // 创建蓝牙服务器
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  
  // // 创建广播服务的UUID
  BLEService *pService = pServer->createService(SERVICE_UUID);
  
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
                   
  pCharacteristic->addDescriptor(new BLE2902());
  
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
  
  pCharacteristic->setCallbacks(new MyCallbacks());
  
  // 开始蓝牙服务
  pService->start();
  
  // 开始广播
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}


/**
 *  call if touched
 */
void myTouchHandler() {
  BatteryState = true;
}


void AmoledInit(void)
{
  pinMode(Rst_PIN, OUTPUT);
  digitalWrite(Rst_PIN,LOW);         
  pinMode(CS_PIN, OUTPUT);
  pinMode(CD_PIN, OUTPUT);
  OLED_Init();
}

void setup()
{ 
  Serial.begin(115200);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  BLEseverSetup();
  AmoledInit();
  touchAttachInterrupt(TOUCH_PIN, myTouchHandler, 1000);
  ClearArrowDisplay(0);
}

void loop()
{
  if(BatteryState){
    BatteryState = false;
    //Serial.print("touched");
    Battery_Manage(0xffff);
    delay(5000);
    Battery_Manage(0x0000);
  }

}