
void SendDataSPI(unsigned char dat)
{  
   unsigned char i;
   
   for(i=0; i<8; i++)			
   {  
      if( (dat&0x80)!=0 ) SDA = 1;
        else SDA = 0;

      dat <<= 1;

	  SCL = 0;
      SCL = 1;			
   }
}

void WriteComm(unsigned int i)
{

    CS0 = 0;
	RS  = 0;

	SendDataSPI(i);

	CS0 = 1;

}

void WriteData(unsigned int i)
{
    CS0 = 0;
	RS  = 1;

	SendDataSPI(i);

	CS0 = 1;
}

void WriteDispData(unsigned char DataH,unsigned char DataL)
{
	 //CS0=0;

	 SendDataSPI(DataH);
	 SendDataSPI(DataL);

	 //CS0=1;
}


void LCD_Init(void)
{	
	RST=1;  
	Delay(30);
	
	RST=0;
	Delay(30);

	RST=1;
	Delay(30);

WriteComm(0x00);			
WriteData(0x00);
				
WriteComm(0xff);			
WriteData(0x22);
WriteData(0x01);
WriteData(0x01);			
WriteData(0x00);
			
WriteComm(0x00);			
WriteData(0x80);
						
WriteComm(0xff);			
WriteData(0x22);
WriteData(0x01);			
WriteData(0x00);

//OSC
WriteComm(0x00);			
WriteData(0x90);

WriteComm(0xc1);			
WriteData(0x1e);

WriteComm(0x00);			
WriteData(0x91);
WriteComm(0xc1);					
WriteData(0x1e);

//rtn

WriteComm(0x00);			
WriteData(0x80);
WriteComm(0xc0);			
WriteData(0x00);

WriteComm(0x00);			
WriteData(0x81);
WriteComm(0xc0);				
WriteData(0xf1);

WriteComm(0x00);			
WriteData(0x82);
WriteComm(0xc0);	
WriteData(0x00);

WriteComm(0x00);			
WriteData(0x83);
WriteComm(0xc0);				
WriteData(0x12);

WriteComm(0x00);			
WriteData(0x84);
WriteComm(0xc0);	
WriteData(0x00);

WriteComm(0x00);			
WriteData(0x85);
WriteComm(0xc0);				
WriteData(0x12);

WriteComm(0x00);			
WriteData(0x86);
WriteComm(0xc0);	
WriteData(0x00);

WriteComm(0x00);			
WriteData(0x87);
WriteComm(0xc0);				
WriteData(0xf1);

WriteComm(0x00);			
WriteData(0x88);
WriteComm(0xc0);	
WriteData(0x00);

WriteComm(0x00);			
WriteData(0x89);
WriteComm(0xc0);				
WriteData(0x12);

WriteComm(0x00);			
WriteData(0x8a);
WriteComm(0xc0);	
WriteData(0x00);

WriteComm(0x00);			
WriteData(0x8b);
WriteComm(0xc0);			
WriteData(0x12);

			

WriteComm(0x00);			
WriteData(0x90);
WriteComm(0xc0);			
WriteData(0x00);


WriteComm(0x00);			
WriteData(0x91);
WriteComm(0xc0);			
WriteData(0xf1);


WriteComm(0x00);			
WriteData(0x92);
WriteComm(0xc0);
WriteData(0x00);


WriteComm(0x00);			
WriteData(0x93);
WriteComm(0xc0);			
WriteData(0x12);


WriteComm(0x00);			
WriteData(0x94);
WriteComm(0xc0);
WriteData(0x00);


WriteComm(0x00);			
WriteData(0x95);
WriteComm(0xc0);			
WriteData(0x12);


WriteComm(0x00);			
WriteData(0x96);
WriteComm(0xc0);
WriteData(0x00);


WriteComm(0x00);			
WriteData(0x97);
WriteComm(0xc0);			
WriteData(0xf1);


WriteComm(0x00);			
WriteData(0x98);
WriteComm(0xc0);
WriteData(0x00);


WriteComm(0x00);			
WriteData(0x99);
WriteComm(0xc0);			
WriteData(0x12);


WriteComm(0x00);			
WriteData(0x9a);
WriteComm(0xc0);
WriteData(0x00);


WriteComm(0x00);			
WriteData(0x9b);
WriteComm(0xc0);			
WriteData(0x12);
			
//Hacitve/Vactive

WriteComm(0x00);			
WriteData(0xa1);
WriteComm(0xb3);			
WriteData(0x78);

WriteComm(0x00);			
WriteData(0xa2);
WriteComm(0xb3);
WriteData(0x00);

WriteComm(0x00);			
WriteData(0xa3);
WriteComm(0xb3);
WriteData(0xF0);

WriteComm(0x00);			
WriteData(0xa4);
WriteComm(0xb3);
WriteData(0x00);

WriteComm(0x00);			
WriteData(0xa5);
WriteComm(0xb3);
WriteData(0xF0);

WriteComm(0x00);			
WriteData(0xa6);
WriteComm(0xb3);
WriteData(0x00);

WriteComm(0x00);			
WriteData(0xa7);
WriteComm(0xb3);
WriteData(0xF0);
		
			//source resolution

WriteComm(0x00);			
WriteData(0x82);
WriteComm(0xb2);						
WriteData(0x66);
						
			//120 setting

WriteComm(0x00);			
WriteData(0x83);
WriteComm(0xf3);						
WriteData(0x60);

WriteComm(0x00);			
WriteData(0x84);
WriteComm(0xf3);		
WriteData(0x80);
										
			//GOA
			//CKV1 STR END
WriteComm(0x00);			
WriteData(0x90);
WriteComm(0xc2);						
WriteData(0x83);

WriteComm(0x00);			
WriteData(0x91);
WriteComm(0xc2);	
WriteData(0x01);	
	
//CKV1
WriteComm(0x00);			
WriteData(0x95);
WriteComm(0xc2);						
WriteData(0xe5);//0c	//e5

WriteComm(0x00);			
WriteData(0x96);
WriteComm(0xc2);	
WriteData(0x00);//00	

WriteComm(0x00);			
WriteData(0x97);
WriteComm(0xc2);	
WriteData(0xdd);//04	//db	
		
//CKV2 STR END

WriteComm(0x00);			
WriteData(0x98);
WriteComm(0xc2);						
WriteData(0x82);

WriteComm(0x00);			
WriteData(0x99);
WriteComm(0xc2);	
WriteData(0x01);

WriteComm(0x00);			
WriteData(0x9a);
WriteComm(0xc2);
WriteData(0x01);
	
			//CKV2

WriteComm(0x00);			
WriteData(0x9d);
WriteComm(0xc2);						
WriteData(0x98);//b0		//95

WriteComm(0x00);			
WriteData(0x9e);
WriteComm(0xc2);
WriteData(0x12);//00		//13	

WriteComm(0x00);			
WriteData(0x9f);
WriteComm(0xc2);
WriteData(0x00);//08		

			//STE
WriteComm(0x00);			
WriteData(0xf0);
WriteComm(0xc3);					
WriteData(0x83);//

WriteComm(0x00);			
WriteData(0xf1);
WriteComm(0xc3);	
WriteData(0x00);//

WriteComm(0x00);			
WriteData(0xf2);
WriteComm(0xc3);
WriteData(0x00);//

WriteComm(0x00);			
WriteData(0xf3);
WriteComm(0xc3);
WriteData(0x44);//	

WriteComm(0x00);			
WriteData(0xf4);
WriteComm(0xc3);
WriteData(0x00);//db	

WriteComm(0x00);			
WriteData(0xf5);
WriteComm(0xc3);
WriteData(0xdb);//20	

WriteComm(0x00);			
WriteData(0xf6);
WriteComm(0xc3);
WriteData(0x20);//00	
//STE width
WriteComm(0x00);			
WriteData(0x0d);
WriteComm(0xca);					
WriteData(0x05);//	

WriteComm(0x00);			
WriteData(0x0e);
WriteComm(0xca);
WriteData(0x05);//

WriteComm(0x00);			
WriteData(0x0f);
WriteComm(0xca);
WriteData(0x05);//	

WriteComm(0x00);			
WriteData(0x10);
WriteComm(0xca);					
WriteData(0x05);//	

WriteComm(0x00);			
WriteData(0x11);
WriteComm(0xca);
WriteData(0x05);//

WriteComm(0x00);			
WriteData(0x12);
WriteComm(0xca);
WriteData(0x05);//	

WriteComm(0x00);			
WriteData(0x13);
WriteComm(0xca);		
WriteData(0x05);//

WriteComm(0x00);			
WriteData(0x14);
WriteComm(0xca);	
WriteData(0x05);//

WriteComm(0x00);			
WriteData(0x15);
WriteComm(0xca);
WriteData(0x05);//

WriteComm(0x00);			
WriteData(0x16);
WriteComm(0xca);	
WriteData(0x40);//	3e	

WriteComm(0x00);			
WriteData(0x17);
WriteComm(0xca);		
WriteData(0x40);//

WriteComm(0x00);			
WriteData(0x18);
WriteComm(0xca);	
WriteData(0x40);//

WriteComm(0x00);			
WriteData(0x19);
WriteComm(0xca);	
WriteData(0x40);//

WriteComm(0x00);			
WriteData(0x1a);
WriteComm(0xca);	
WriteData(0x40);//	

WriteComm(0x00);			
WriteData(0x1b);
WriteComm(0xca);
WriteData(0x40);//	

WriteComm(0x00);			
WriteData(0x1c);
WriteComm(0xca);
WriteData(0x40);//

WriteComm(0x00);			
WriteData(0x1d);
WriteComm(0xca);	
WriteData(0x40);//	

WriteComm(0x00);			
WriteData(0x1e);
WriteComm(0xca);
WriteData(0x40);//	

			//STE in skipframe

WriteComm(0x00);			
WriteData(0xfa);
WriteComm(0xc3);					
WriteData(0x7b);//82	

WriteComm(0x00);			
WriteData(0xfb);
WriteComm(0xc3);
WriteData(0x0b);//03	

//GSTV

WriteComm(0x00);			
WriteData(0xb0);
WriteComm(0xc2);						
WriteData(0x00);

WriteComm(0x00);			
WriteData(0xb1);
WriteComm(0xc2);		
WriteData(0x02);

WriteComm(0x00);			
WriteData(0xb2);
WriteComm(0xc2);			
WriteData(0x00);

WriteComm(0x00);			
WriteData(0xb3);
WriteComm(0xc2);			
WriteData(0x8d);//a4	//89

WriteComm(0x00);			
WriteData(0xb4);
WriteComm(0xc2);		
WriteData(0x00);		

WriteComm(0x00);			
WriteData(0xb5);
WriteComm(0xc2);	
WriteData(0x21);//3a	//1f	
//EN mode

WriteComm(0x00);			
WriteData(0x80);
WriteComm(0xc3);
WriteData(0x00);

WriteComm(0x00);			
WriteData(0x81);
WriteComm(0xc3);
WriteData(0x07);

WriteComm(0x00);			
WriteData(0x82);
WriteComm(0xc3);
WriteData(0x07);

WriteComm(0x00);			
WriteData(0x83);
WriteComm(0xc3);
WriteData(0x07);

WriteComm(0x00);			
WriteData(0x84);
WriteComm(0xc3);
WriteData(0x07);

WriteComm(0x00);			
WriteData(0x85);
WriteComm(0xc3);
WriteData(0x07);

WriteComm(0x00);			
WriteData(0x86);
WriteComm(0xc3);
WriteData(0x07);

WriteComm(0x00);			
WriteData(0x87);
WriteComm(0xc3);
WriteData(0x07);

WriteComm(0x00);			
WriteData(0x88);
WriteComm(0xc3);
WriteData(0x07);

WriteComm(0x00);			
WriteData(0x89);
WriteComm(0xc3);
WriteData(0x07);

WriteComm(0x00);			
WriteData(0x8a);
WriteComm(0xc3);	
WriteData(0x00);			

WriteComm(0x00);			
WriteData(0x90);
WriteComm(0xc3);
WriteData(0x04);


WriteComm(0x00);			
WriteData(0x91);
WriteComm(0xc3);
WriteData(0xfb);


WriteComm(0x00);			
WriteData(0x92);
WriteComm(0xc3);
WriteData(0xfb);

WriteComm(0x00);			
WriteData(0x93);
WriteComm(0xc3);
WriteData(0xfb);

WriteComm(0x00);			
WriteData(0x94);
WriteComm(0xc3);
WriteData(0xfb);

WriteComm(0x00);			
WriteData(0x95);
WriteComm(0xc3);
WriteData(0xfb);

WriteComm(0x00);			
WriteData(0x96);
WriteComm(0xc3);
WriteData(0xfb);

WriteComm(0x00);			
WriteData(0x97);
WriteComm(0xc3);
WriteData(0xfb);

WriteComm(0x00);			
WriteData(0x98);
WriteComm(0xc3);
WriteData(0xfb);

WriteComm(0x00);			
WriteData(0x99);
WriteComm(0xc3);
WriteData(0xfb);

WriteComm(0x00);			
WriteData(0x9a);
WriteComm(0xc3);	
WriteData(0x04);
					
	//GOA out sel
WriteComm(0x00);			
WriteData(0xa0);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xa1);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xa2);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xa3);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xa4);
WriteComm(0xc3);
WriteData(0x15);

WriteComm(0x00);			
WriteData(0xa5);
WriteComm(0xc3);
WriteData(0x05);

WriteComm(0x00);			
WriteData(0xa6);
WriteComm(0xc3);
WriteData(0x06);

WriteComm(0x00);			
WriteData(0xa7);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xa8);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xa9);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xaa);
WriteComm(0xc3);	
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xab);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xac);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xad);
WriteComm(0xc3);	
WriteData(0x04);

WriteComm(0x00);			
WriteData(0xae);
WriteComm(0xc3);
WriteData(0x05);

WriteComm(0x00);			
WriteData(0xaf);
WriteComm(0xc3);
WriteData(0x06);
		
WriteComm(0x00);			
WriteData(0xb0);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xb1);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xb2);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xb3);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xb4);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xb5);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xb6);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xb7);
WriteComm(0xc3);
WriteData(0x11);

WriteComm(0x00);			
WriteData(0xb8);
WriteComm(0xc3);
WriteData(0x09);

WriteComm(0x00);			
WriteData(0xb9);
WriteComm(0xc3);
WriteData(0x0a);

WriteComm(0x00);			
WriteData(0xba);
WriteComm(0xc3);
WriteData(0x01);

WriteComm(0x00);			
WriteData(0xbb);
WriteComm(0xc3);
WriteData(0x02);

WriteComm(0x00);			
WriteData(0xbc);
WriteComm(0xc3);
WriteData(0x03);

WriteComm(0x00);			
WriteData(0xbd);
WriteComm(0xc3);	
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xbe);
WriteComm(0xc3);
WriteData(0x16);

WriteComm(0x00);			
WriteData(0xbf);
WriteComm(0xc3);
WriteData(0x16);

//SW out SET

WriteComm(0x00);			
WriteData(0xc0);
WriteComm(0xc2);						
WriteData(0x32);

WriteComm(0x00);			
WriteData(0xc1);
WriteComm(0xc2);		
WriteData(0x54);

WriteComm(0x00);			
WriteData(0xc2);
WriteComm(0xc2);	
WriteData(0x10);

WriteComm(0x00);			
WriteData(0xc3);
WriteComm(0xc2);					
WriteData(0x23);

WriteComm(0x00);			
WriteData(0xc4);
WriteComm(0xc2);		
WriteData(0x45);

WriteComm(0x00);			
WriteData(0xc5);
WriteComm(0xc2);		
WriteData(0x01);

WriteComm(0x00);			
WriteData(0xc6);
WriteComm(0xc2);								
WriteData(0x35);

WriteComm(0x00);			
WriteData(0xc7);
WriteComm(0xc2);		
WriteData(0x24);

WriteComm(0x00);			
WriteData(0xc8);
WriteComm(0xc2);		
WriteData(0x01);		
						
WriteComm(0x00);			
WriteData(0xd0);
WriteComm(0xc2);								
WriteData(0x32);//23

WriteComm(0x00);			
WriteData(0xd1);
WriteComm(0xc2);	
WriteData(0x54);//45	

WriteComm(0x00);			
WriteData(0xd2);
WriteComm(0xc2);
WriteData(0x10);//01	

WriteComm(0x00);			
WriteData(0xd3);
WriteComm(0xc2);				
WriteData(0x23);//32	

WriteComm(0x00);			
WriteData(0xd4);
WriteComm(0xc2);	
WriteData(0x45);//54	

WriteComm(0x00);			
WriteData(0xd5);
WriteComm(0xc2);	
WriteData(0x01);//10	

WriteComm(0x00);			
WriteData(0xd6);
WriteComm(0xc2);							
WriteData(0x35);

WriteComm(0x00);			
WriteData(0xd7);
WriteComm(0xc2);		
WriteData(0x24);

WriteComm(0x00);			
WriteData(0xd8);
WriteComm(0xc2);		
WriteData(0x01);						
			//CKH
WriteComm(0x00);			
WriteData(0xf0);
WriteComm(0xc2);						
WriteData(0x00);//04	//02

WriteComm(0x00);			
WriteData(0xf1);
WriteComm(0xc2);
WriteData(0x00);//06	//02	

WriteComm(0x00);			
WriteData(0xf2);
WriteComm(0xc2);
WriteData(0x02);//05	//02

WriteComm(0x00);			
WriteData(0xf3);
WriteComm(0xc2);	
WriteData(0x0f);//11	//11	

WriteComm(0x00);			
WriteData(0xf4);
WriteComm(0xc2);	
WriteData(0x02);//05	//02	

WriteComm(0x00);			
WriteData(0xf5);
WriteComm(0xc2);
WriteData(0x0f);//11	//11	

WriteComm(0x00);			
WriteData(0xf6);
WriteComm(0xc2);	
WriteData(0x02);//04	//02  //06

WriteComm(0x00);			
WriteData(0xf7);
WriteComm(0xc2);
WriteData(0x0f);//11	//11	

WriteComm(0x00);			
WriteData(0xf8);
WriteComm(0xc2);	
WriteData(0x02);//05	//02	

WriteComm(0x00);			
WriteData(0xf9);
WriteComm(0xc2);
WriteData(0x0f);//11	//11	

WriteComm(0x00);			
WriteData(0xfa);
WriteComm(0xc2);	
WriteData(0x02);//05	//02

WriteComm(0x00);			
WriteData(0xfb);
WriteComm(0xc2);
WriteData(0x0f);//11	//11	

WriteComm(0x00);			
WriteData(0xfc);
WriteComm(0xc2);	
WriteData(0x02);//07	//02   //06

WriteComm(0x00);			
WriteData(0xfd);
WriteComm(0xc2);
WriteData(0x0f);//11	//11	
		//MUX					

WriteComm(0x00);			
WriteData(0xa0);
WriteComm(0xc0);						
WriteData(0x00);//0d	

WriteComm(0x00);			
WriteData(0xa1);
WriteComm(0xc0);
WriteData(0x1a);//1a

WriteComm(0x00);			
WriteData(0xa2);
WriteComm(0xc0);		
WriteData(0x1a);//1a

WriteComm(0x00);			
WriteData(0xa3);
WriteComm(0xc0);	
WriteData(0x1a);//1a	

WriteComm(0x00);			
WriteData(0xa4);
WriteComm(0xc0);	
WriteData(0x1a);//1a	

WriteComm(0x00);			
WriteData(0xa5);
WriteComm(0xc0);	
WriteData(0x1a);//1a	

WriteComm(0x00);			
WriteData(0xa6);
WriteComm(0xc0);	
WriteData(0x1a);//1a	

WriteComm(0x00);			
WriteData(0xa7);
WriteComm(0xc0);			
WriteData(0x00);//0d	//idle

WriteComm(0x00);			
WriteData(0xa8);
WriteComm(0xc0);
WriteData(0x1a);//1a	

WriteComm(0x00);			
WriteData(0xa9);
WriteComm(0xc0);	
WriteData(0x1a);//1a

WriteComm(0x00);			
WriteData(0xaa);
WriteComm(0xc0);		
WriteData(0x1a);//1a	

WriteComm(0x00);			
WriteData(0xab);
WriteComm(0xc0);	
WriteData(0x1a);//1a	

WriteComm(0x00);			
WriteData(0xac);
WriteComm(0xc0);	
WriteData(0x1a);//1a	

WriteComm(0x00);			
WriteData(0xad);
WriteComm(0xc0);	
WriteData(0x1a);//1a														
				
//Source pch off	

WriteComm(0x00);			
WriteData(0x92);
WriteComm(0xf5);						
WriteData(0x20);	//off
//PCH	

WriteComm(0x00);			
WriteData(0xe1);
WriteComm(0xc2);						
WriteData(0x00);	//off
															
//EQ
WriteComm(0x00);			
WriteData(0xe0);
WriteComm(0xc3);						
WriteData(0x00);

WriteComm(0x00);			
WriteData(0xe1);
WriteComm(0xc3);	
WriteData(0x11);	//22  //11

WriteComm(0x00);			
WriteData(0xe2);
WriteComm(0xc3);	
WriteData(0x00);		

WriteComm(0x00);			
WriteData(0xe3);
WriteComm(0xc3);
WriteData(0x11);	//22	//11		
		
			//SAP	
WriteComm(0x00);			
WriteData(0x44);
WriteComm(0xc5);						
WriteData(0xca);	

			
			//AP	
WriteComm(0x00);			
WriteData(0x40);
WriteComm(0xc5);						
WriteData(0x29);	


			//chop
WriteComm(0x00);			
WriteData(0x65);
WriteComm(0xc4);						
WriteData(0xc0);	//0xc0

//Gamma chop off

WriteComm(0x00);			
WriteData(0x68);
WriteComm(0xc4);						
WriteData(0x01);	
		

//VCL SET
WriteComm(0x00);			
WriteData(0x14);
WriteComm(0xc5);						
WriteData(0x12);		
//AVDD

WriteComm(0x00);			
WriteData(0x11);
WriteComm(0xc5);						
WriteData(0x4a);	//5.5	

WriteComm(0x00);			
WriteData(0x12);
WriteComm(0xc5);			
WriteData(0x4a);		

//TCON
WriteComm(0x00);			
WriteData(0xa1); 
WriteComm(0xc1);						
WriteData(0xc0); 
//video mode HS follow external, CMD mode HS follow internal		
			
WriteComm(0x00);			
WriteData(0xa2);
WriteComm(0xc1);						
WriteData(0xe3);		


//Timeout VS

WriteComm(0x00);			
WriteData(0xa8);
WriteComm(0xc1);						
WriteData(0x0a);		


//cke toggle all
WriteComm(0x00);	
WriteData(0xa8);
WriteComm(0xc2);	
WriteData(0x54);	//28	

//mipi off
WriteComm(0x00);			
WriteData(0x90);
WriteComm(0xff);						
WriteData(0x80);		

//vrefp5 vrefn5

WriteComm(0x00);			
WriteData(0x42);
WriteComm(0xc5);						
WriteData(0x33);

WriteComm(0x00);			
WriteData(0x43);
WriteComm(0xc5);				
WriteData(0x44);		

//voltageset VGMP VGSP
WriteComm(0x00);			
WriteData(0x31);
WriteComm(0xc5);			
WriteData(0xd6);//cf=5.1v, fe=5.8V, e3=5.4V

WriteComm(0x00);			
WriteData(0x32);
WriteComm(0xc5);
WriteData(0xbb);//VGSP ae=2.8 ca=3.225 dd=3.51	f0=3.8 e6=3.645 e9=3.69 eb=3.72 ea=3.705 d2=3.345 da=3.465

WriteComm(0x00);			
WriteData(0x33);
WriteComm(0xc5);
WriteData(0xd6);//cf = 5.1

WriteComm(0x00);			
WriteData(0x34);
WriteComm(0xc5);
WriteData(0xbb);//ca=3.225		//d8=3.435	//d5=3.39

//NB
WriteComm(0x00);//Cmd
WriteData(0xa0);//Data
WriteComm(0xb3);//Cmd
WriteData(0x00);//Data		
			
//EL
WriteComm(0x00);			
WriteData(0x01);
WriteComm(0xcb);			
WriteData(0x20);///15==-3.4,29==-1.4,20==-2.3			

 //mirror x
WriteComm(0x00);			
WriteData(0xd0);
WriteComm(0xc0);			
WriteData(0x04);			

//VGH/VGL
WriteComm(0x00);			
WriteData(0x02);
WriteComm(0xc5);			
WriteData(0x05);


WriteComm(0x00);			
WriteData(0x03);
WriteComm(0xc5);						
WriteData(0xc5);

WriteComm(0x00);			
WriteData(0x04);
WriteComm(0xc5);			
WriteData(0x24);		//24	

WriteComm(0x00);			
WriteData(0x05);
WriteComm(0xc5);
WriteData(0x24);		//24	
			//VGH/VGL pump
WriteComm(0x00);			
WriteData(0x00);
WriteComm(0xc5);			
WriteData(0x5b);


WriteComm(0x00);			
WriteData(0x01);
WriteComm(0xc5);						
WriteData(0x5b);			

//vrefp5 off
WriteComm(0x00);			
WriteData(0x6c);
WriteComm(0xf5);			
WriteData(0x00);			

//bvp3d bvn3d off
WriteComm(0x00);			
WriteData(0x6b);
WriteComm(0xc4);			
WriteData(0xb6);			

//skipframe
WriteComm(0x00);			
WriteData(0xf0);
WriteComm(0xc0);						
WriteData(0x26);	


WriteComm(0x00);			
WriteData(0xf4);
WriteComm(0xc0);						
WriteData(0x03);	//0b:5Hz 03:15Hz

WriteComm(0x3A);						
WriteData(0x05);

WriteComm(0x51);						
WriteData(0xff);//·¶Î§00-ff


	
WriteComm(0x11);

Delay(120);

WriteComm(0x29);
}