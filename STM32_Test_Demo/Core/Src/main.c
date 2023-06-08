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
extern uint16_t font_5_8[][5];
#define RxLenth 8
uint8_t  Value[RxLenth];//接收数据存放数组
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void LCD_Init(void);


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
	SendDataSPI(val);
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

void Disp(uint8_t Num)
{
		uint8_t j;

		for(j=0;j<8;j++)
		{
			if (Value[Num] & (0x80 >> (j % 8))) {
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
			if (Value[Num+1] & (0x80 >> (j % 8))) {
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

//字体=8高5宽
void LCD_font_5_7(void)
{

	
	uint8_t j=Value[7];
	//for(j=0;j<3;j++)
	//{
		AMOLED_Block_Write(Value[6],Value[6]+7,j,Value[7]+10);
		Disp(0);

		AMOLED_Block_Write(Value[6],Value[6]+7,j+2,Value[7]+10);
		Disp(2);

		AMOLED_Block_Write(Value[6],Value[6]+7,j+4,Value[7]+10);
		Disp(4);
	//}

//		uint16_t j;

//		for(j=0;j<8;j++)
//		{
//			if (Value[0] & (0x80 >> (j % 8))) {
//				Write_Disp_Data(0xffff);
//				Write_Disp_Data(0xffff);
//				Write_Disp_Data(0xffff);
//			} else {
//				Write_Disp_Data(0x0000);
//				Write_Disp_Data(0x0000);
//				Write_Disp_Data(0x0000);
//			}
//		}

//		for(j=0;j<8;j++)
//		{
//			if (Value[1] & (0x80 >> (j % 8))) {
//				Write_Disp_Data(0xffff);
//				Write_Disp_Data(0xffff);
//				Write_Disp_Data(0xffff);
//			} else {
//				Write_Disp_Data(0x0000);
//				Write_Disp_Data(0x0000);
//				Write_Disp_Data(0x0000);
//			}
//		}

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *Uarthandle)
{
	HAL_UART_Receive_IT(&huart1,(uint8_t*)&Value,RxLenth);
	LCD_font_5_7();
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

	HAL_UART_Receive_IT(&huart1,(uint8_t*)&Value,RxLenth);

//	uint8_t id[3];

//	HAL_SPI_Receive(&hspi1,id,3,HAL_MAX_DELAY);

//	AMOLED_Clear(120,120,0xffff);//经测试能用

//	AMOLED_Clear(120,120,0x0000);//经测试能用

	//uint16_t color=0xffff;
	//ST7789_DrawImage(0,0,128,128,(uint16_t *)saber);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
