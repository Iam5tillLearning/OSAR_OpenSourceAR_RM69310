//DEMO CODE DO0200PFS01 
//SPI_3Wire & SPI_4Wire
//R3 =NC,R4 =0R---SPI_3Wire
//R3 =0R,R4 =NC---SPI_4Wire
//驱动IC 寄存器初始配置
// **********************
//深圳达沃科技有限公司
// DWO LIMITED
// www.dwo.net.cn
// mail: alan@dwo.net.cn
// Tel: 86-755-8258 0810
// AMOLED design, driver board development, PCBA, provide one-stop service.
//************************

/*Recommended Operating Sequence */
/*STEP 1---[ Power On ] */
/*STEP 2---[ Activate Reset ] Driver IC */
/*STEP 3---[ Configure AMOLED Register] */ 	


//Power ON sequence
/*  STEP 1---[ Power On ]
（1）turn-ON VBAT  (+3.7 VDC)
（2）turn-ON VCC   (+2.8VDC)  IOVCC=VCC
Wait 10ms
STEP 2---[ Activate Reset ] 
STEP 3---[ SPI Configure AMOLED Register] 
STEP 4---[ SPI Send AMOLED Display Data]
*/

void DO0200FS01_Init(void) // www.dwo.net.cn
{	 	
WriteCommData(0xFE,0x00);//PAGE

//WriteCommData(0x35,0x00);//TE ON	
//WriteCommData(0x34,0x00);//TE OFF	

//WriteCommData(0x36,0x00);//Scan Direction Control

//WriteCommData(0x3A,0x75);//Interface Pixel Format	16bit/pixel
//WriteCommData(0x3A,0x76);//Interface Pixel Format	18bit/pixel
//WriteCommData(0x3A,0x77);//Interface Pixel Format	24bit/pixel

WriteCommData(0x51,0x00); //Write Display Brightness MAX_VAL=0XFF
	             
WriteCommData(0x11,0x00); //Sleep Out
delay_ms(120); 
               

WriteCommData(0x29,0x00); //Display on   	
delay_ms(20);
  
WriteCommData(0x51,0xD0); //Write Display Brightness	MAX_VAL=0XFF

}  //end of AMOLED_Init


///*---------------------------------------------------------------------------
//此函数用于设置AMOLED“窗口”---GRAM
//---------------------------------------------------------------------------*/
void AMOLED_Block_Write(u16 Xstart,u16 Xend,u16 Ystart,u16 Yend)
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

//SPI写数据
//----------------------------------------------------------------------
void  SPI_1L_SendData(unsigned char dat)
{  
  unsigned char i;

   for(i=0; i<8; i++)			
   {   
      if( (dat&0x80)!=0 ) SPI_SDA = 1;
      else                SPI_SDA = 0;

		dat  <<= 1;

	  SPI_SCL = 0;//delay_us(2);
    SPI_SCL = 1;	
		 
   }
	 
}

void WriteComm(u16 regval)
{ 

	if(Interface==SPI_4W_1L)//if SPI_4Wire
	{
	SPI_CS = 0;
	SPI_RS = 0;//Write_Cmd

	SPI_1L_SendData(regval);

	SPI_CS = 1;
	}
	else if(Interface==SPI_3W_1L)//if SPI_3Wire
	{

	SPI_CS = 0;

	SPI_SDA = 0;//Write_Cmd
	SPI_SCL = 0;//delay_us(1);
	SPI_SCL = 1;//delay_us(1);	

	SPI_1L_SendData(regval);
	SPI_CS = 1;
	}				
}

void WriteData(u16 val)
{   
	if(Interface==SPI_4W_1L)//如果接口为4线1通道
	{
	SPI_CS = 0;
	SPI_RS = 1;//Write_parameter

	SPI_1L_SendData(val);

	SPI_CS = 1;
	}

	else if(Interface==SPI_3W_1L)//如果接口为3线1通道
	{			
	SPI_CS = 0;

	SPI_SDA = 1;//Write_parameter
	SPI_SCL = 0;
	SPI_SCL = 1;	

	SPI_1L_SendData(val);
	SPI_CS = 1;
	}	

}


void WriteCommData(u16 regval,u16 val)
{ 
WriteComm(regval);
WriteData(val);	
}


void Write_Disp_Data(u16 val)
{ 
    if(Interface==SPI_4W_1L)//如果接口为4线1通道
		{	
  	    SPI_CS=0; 
		SPI_RS=1;//Write_Display_data	
		SPI_1L_SendData(val>>8);
		SPI_1L_SendData(val&0xff);	
	    SPI_CS=1; 
		}
	else if(Interface==SPI_3W_1L)//如果接口为3线1通道
		{	
  	  SPI_CS=0; 
	  SPI_SDA=1;//Write_Display_data	
	  SPI_1L_SendData(val>>8);
	  SPI_1L_SendData(val&0xff);	
	  SPI_CS=1; 
		}		

}


void AMOLED_Clear(u16 color)
{  	
	unsigned char i,j;
	
	COL=240;
	ROW=536;
	
	AMOLED_Block_Write(0,COL-1,0,ROW-1);
	

	for(i=0;i<COL;i++)
		for(j=0;j<ROW;j++)
			{
			Write_Disp_Data(color);
			}

}