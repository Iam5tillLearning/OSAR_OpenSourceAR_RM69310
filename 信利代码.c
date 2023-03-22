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
	Delay(150);
WriteComm(0x29);WriteData(0x00);