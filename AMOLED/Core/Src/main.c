/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern uint16_t saber[][128];
uint8_t  Value[20];//接收数据存放数组
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void LCD_Init(void);

const uint8_t font_5_8[][5] = {
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

        /*
        * Index = 0x5f
        */
        0x08, 0x08, 0x2a, 0x1c, 0x08, // ->                [0x5f]
        0x08, 0x1c, 0x2a, 0x08, 0x08, // <-                [0x60]
        0x04, 0x02, 0x7f, 0x02, 0x04, // ↑                [0x61]
        0x10, 0x20, 0x7f, 0x20, 0x10, // ↓                [0x62]
        0x15, 0x16, 0x7c, 0x16, 0x15, // ￥                [0x63]
        0x03, 0x3b, 0x44, 0x44, 0x44, // ℃                [0x64]
        0x03, 0x03, 0x7c, 0x14, 0x14, // ℉                [0x65]
        0x44, 0x28, 0x10, 0x28, 0x44, // ×                [0x66]
        0x08, 0x08, 0x2a, 0x08, 0x08, // ÷                [0x67]
        0x38, 0x44, 0x48, 0x30, 0x2c, // α         [0x68]
        0xf8, 0x54, 0x54, 0x54, 0x28, // β                [0x69]
        0x28, 0x54, 0x54, 0x44, 0x20, // ε                [0x6a]
        0x3e, 0x49, 0x09, 0x09, 0x06, // ρ                [0x6b]
        0x38, 0x44, 0x4c, 0x54, 0x24, // σ                [0x6c]
        0x40, 0x3f, 0x08, 0x08, 0x1f, // μ                [0x6d]
        0x1f, 0x08, 0x08, 0x3f, 0x40, // η                [0x6e]
        0x3c, 0x4a, 0x4a, 0x4a, 0x3c, // θ                [0x6f]
        0x58, 0x64, 0x04, 0x64, 0x58, // Ω                [0x70]
        0x44, 0x3c, 0x04, 0x7c, 0x44, // π                [0x71]
        0x30, 0x28, 0x10, 0x28, 0x18, // ∞                [0x72]
        0x30, 0x28, 0x24, 0x28, 0x30, // △                [0x73]
        0x08, 0x1c, 0x08, 0x08, 0x0e, // Enter<-[0x74]
};

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

void SendDataSPI(uint8_t dat)
{  
	HAL_SPI_Transmit(&hspi1, &dat, sizeof(dat), HAL_MAX_DELAY);
}

void WriteComm(unsigned int i)
{
	HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_RESET);//片选拉低
    
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);//C/D拉低

	SendDataSPI(i);

	HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_SET);//片选拉高

}

void WriteData(unsigned int i)
{
	HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_RESET);//片选拉低

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);//C/D拉高

	SendDataSPI(i);

	HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_SET);//片选拉高
}

void WriteDispData_2(unsigned char DataH,unsigned char DataL)
{

	SendDataSPI(DataH);
	SendDataSPI(DataL);

}

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


void Write_Disp_Data(uint16_t val)
{ 

	HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_RESET);//片选拉低 
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);//C/D拉高
	WriteDispData_2(val&0xff,val>>8);
	HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_SET);//片选拉高

}

void AMOLED_Clear(uint16_t Column,uint16_t ROW,uint16_t color)
{  	
	uint16_t i,j;
	
	AMOLED_Block_Write(0,Column-1,0,ROW-1);

	for(i=0;i<Column;i++)
		for(j=0;j<ROW;j++)
			{
				Write_Disp_Data(color);
			}

}
/*
static void ST7789_WriteData(uint8_t *buff, size_t buff_size)
{
	HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_RESET);//片选拉低 
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);//C/D拉高

	// split data in small chunks because HAL can't send more than 64K at once

	while (buff_size > 0) {
		uint16_t chunk_size = buff_size > 65535 ? 65535 : buff_size;
		HAL_SPI_Transmit(&hspi1, buff, chunk_size, HAL_MAX_DELAY);
		buff += chunk_size;
		buff_size -= chunk_size;
	}

	HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_SET);//片选拉高
}

void ST7789_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data)
{

	AMOLED_Block_Write(0,x-1,0,y-1);
	ST7789_WriteData((uint8_t *)data, sizeof(uint16_t) * w * h);
}

*/
void LCD_font_5_7(uint16_t Column,uint16_t ROW,uint16_t font_colour,uint16_t back_colour,const uint8_t font)
{
		uint16_t i,j;
		uint8_t font_temp_table[8];

		for(i=0;i<5;i++)
		{
			font_temp_table[i]=font_5_8[font][i];	
		}

		font_temp_table[5]=0;
		font_temp_table[6]=0;
		font_temp_table[7]=0;

		AMOLED_Block_Write(Column,Column+8,ROW,ROW+8);
	
		for(j=0;j<8;j++)
		{
			for(i=0;i<8;i++)
			{
				if((font_temp_table[i]&0x01)==0x01)
				{
						Write_Disp_Data(font_colour);
				}
				else
				{
						Write_Disp_Data(back_colour);
				}
				font_temp_table[i]=font_temp_table[i]>>1;
			}
		}
	
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *Uarthandle)
{
	HAL_UART_Receive_IT(&huart1,(uint8_t*)&Value,1);
	HAL_UART_Transmit (&huart1 ,(uint8_t*)&Value,1,0xfff);//接收到的再发送出去
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

	LCD_Init();

	HAL_UART_Receive_IT(&huart1,(uint8_t*)&Value,1);

//	uint8_t id[3];

//	HAL_SPI_Receive(&hspi1,id,3,HAL_MAX_DELAY);

	AMOLED_Clear(30,60,0xffff);//经测试能用

	AMOLED_Clear(30,60,0x0000);//经测试能用

	//LCD_font_5_7(64,64,0xffff,0x0000,2);

	LCD_font_5_7(32,32,0xffff,0x0000,3);

	//LCD_font_5_7(78,78,0xffff,0x0000,6);

	//LCD_font_5_7(128,128,0xffff,0x0000,5);//不能用

	//uint16_t color=0xffff;
	//ST7789_DrawImage(0,0,128,128,(uint16_t *)saber);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	//color = color -50;
	//AMOLED_Clear(color);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void LCD_Init(void)
{	
	HAL_GPIO_WritePin(GPIOA, RST_Pin, GPIO_PIN_SET);//RST=1;  
	HAL_Delay(30);

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
HAL_Delay(150);
WriteComm(0x29);WriteData(0x00);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
