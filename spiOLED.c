#include "spiOLED.h"

void SetupSPI()
{
    int spi1;    
    int spiChannel = 0;
    int clock = 1000000;
    
    //unsigned char test = '~'; test
    //printf("SPI is ready, spi1=%d\n", test);    

    printf("Starting SPI Test\n");
    wiringPiSetup();    
    spi1 = wiringPiSPISetup(spiChannel,clock);    
    if(spi1!=-1)
      printf("SPI is ready, spi1=%d\n", spi1);
    else
      printf("SPI Setup Fail, spi1=%d\n", spi1);
}
void setPinMode()
{
  pinMode(RESET, 1);  //output =1
  pinMode(DC, 1);     //output =1
}

void reset()
{
    digitalWrite( RESET, 1);
    delay(10);
    digitalWrite( RESET, 0);
    delay(10);
    digitalWrite( RESET, 1);
}

void initial()
{
  commandOutput(0xae);//Set Display OFF
  commandOutput(0x40);//Set Display Start Line
  commandOutput(0x81);//Set Contrast Control
  commandOutput(0x5e);//normal mode (type brightness)
  commandOutput(0xa1);//SEG_REMAP
  commandOutput(0xa4);// Entire Display Mode Off
  commandOutput(0xa6);//Set Normal Display
  commandOutput(0xa8);//Set Multiplex Ratio
  commandOutput(0x3F);// 64MUX
  commandOutput(0xc8);//Set COM Output Scan Direction
  commandOutput(0xd3);//Set Display Offset
  commandOutput(0x00);
  commandOutput(0xd5);//Set Display Clock Divide Ratio/Oscillator Frequency
  commandOutput(0xc0);//
  commandOutput(0xd9);//Set Phase Length
  commandOutput(0xf1);
  commandOutput(0xda);//Set COM Pins Hardware Configuration
  commandOutput(0x12);
  commandOutput(0xdb);//Set VCOMH Deselect Level
  commandOutput(0x40);
  commandOutput(0x8d);//Charge Pump
  commandOutput(0x14);
  allPixelSwitch(OFF);
  commandOutput(0xaf);//Set Display ON
}

void showP6x8Char(unsigned char ucIdxX, unsigned char ucIdxY, unsigned char ucData)
{
    unsigned char i, ucDataTmp;     
       
    ucDataTmp = ucData-32;
    if(ucIdxX > 122)
    {
        ucIdxX = 0;
        ucIdxY++;
    }
    
    LED_SetPos(ucIdxX, ucIdxY);
    
    for(i = 0; i < 6; i++)
    {     
        dataOutput(F6x8[ucDataTmp][i]);  
    }
}

void showP6x8String(unsigned char ucIdxX, unsigned char ucIdxY, unsigned char ucDataStr[])
{
    unsigned char i, j, ucDataTmp; 

    for (j = 0; ucDataStr[j] != '\0'; j++)
    {    
        ucDataTmp = ucDataStr[j] - 32;
        if(ucIdxX > 122)
        {
            ucIdxX = 0;
            ucIdxY++;
        }
        
        LED_SetPos(ucIdxX,ucIdxY); 
        
        for(i = 0; i < 6; i++)
        {     
            dataOutput(F6x8[ucDataTmp][i]);  
        }
        ucIdxX += 6;
    }

    return;
}

void LED_SetPos(unsigned char ucIdxX, unsigned char ucIdxY)
{ 
    commandOutput(0xb0 + ucIdxY);
    commandOutput(((ucIdxX & 0xf0) >> 4) | 0x10);
    commandOutput((ucIdxX & 0x0f) | 0x00); 
} 

void commandOutput( unsigned char command )
{
    digitalWrite( DC, 0);
    wiringPiSPIDataRW(0, &command, 1);
}

void dataOutput( unsigned char data )
{
    digitalWrite( DC, 1);
    wiringPiSPIDataRW(0, &data, 1);
    //delay(1);  //for debug
    digitalWrite( DC, 0);
}

void allPixelSwitch(unsigned char status)
{
  unsigned char i,j;
  for(i=0;i<8;i++)
   {
     commandOutput(0xb0+i);
     commandOutput(0x00);
     commandOutput(0x10);
     for(j=0;j<128;j++)
     {
       dataOutput(status);
     }
   }  
}

void CharacterDemo()
{
    allPixelSwitch(OFF);
    unsigned char Str[]="A095";
    showP6x8Char(0,0,'U');
    showP6x8Char(6,0,'S');
    showP6x8Char(12,0,'M');
    showP6x8Char(18,0,'P');


    showP6x8String(0,2,Str);
    showP6x8String(0,3,"Have a nice day");
    showP6x8String(0,5,"2016/12/09 :)");
    scroll();
}

void CharacterDemo2()
{
    allPixelSwitch(OFF);
    unsigned char Str[]="TEST TEST";
    showP6x8Char(0,0,'T');
    showP6x8Char(6,0,'E');
    showP6x8Char(12,0,'S');
    showP6x8Char(18,0,'T');


    showP6x8String(0,2,Str);
    showP6x8String(0,3,"Test Test Test");
    showP6x8String(0,5,"2016/07/26 :)");
    scroll();
}

void scroll()
{
    commandOutput(0x2E);
    commandOutput(0x29);
    commandOutput(0x00); //A
    commandOutput(0x00); //B
    commandOutput(0x00); //C
    commandOutput(0x07); //D
    commandOutput(0x00);
    commandOutput(0x00);
    commandOutput(0x7f);
    commandOutput(0x2f);
}

void OLED_SendCmdAndData(unsigned char command, unsigned char data)
{
    digitalWrite( DC, 0);
    wiringPiSPIDataRW(0, &command, 1);
    digitalWrite( DC, 1);
    wiringPiSPIDataRW(0, &data, 1);
    digitalWrite( DC, 0);
}

void OLED_SendCmd (unsigned char command)
{
    digitalWrite( DC, 0);
    wiringPiSPIDataRW(0, &command, 1);
}

void OLED_SendData (unsigned char data)
{
    digitalWrite( DC, 1);
    wiringPiSPIDataRW(0, &data, 1);
    digitalWrite( DC, 0);
}

void A095_test()
{
//int allPixel=3;
//unsigned char command = 0x2c;
//unsigned char data[allPixel];
////unsigned char data = 0xff;
//int i,j;
//
//    digitalWrite( DC, 0);
//    wiringPiSPIDataRW(0, &command, 1);
//    digitalWrite( DC, 1);
//    
////    getchar();  
//    for(j=0;j<540*3;j++)
//    {
//      data[0]=0xff;
//      data[1]=0xff;
//      data[2]=0xff;
//
//      wiringPiSPIDataRW(0, data, allPixel);
//    }
////    printf("[%d]\n", data[0]); 
////    printf("[%d]\n", data[1]); 
////    printf("[%d]\n", data[2]); 
//    digitalWrite( DC, 0);


int length=180*3*6;
unsigned char command = 0x2c;
unsigned char data[length];
int i,j;

    digitalWrite( DC, 0);
    wiringPiSPIDataRW(0, &command, 1);
    digitalWrite( DC, 1);
      
    for(j=0;j<20;j++)
    {
      for (i=0; i<(length);i++)
      {
        if (i%3==1)      //B
          data[i]=0x00;
        else if (i%3==2) //R
          data[i]=0x00;  
        else  
          data[i]=0xff;  //G
      }
      wiringPiSPIDataRW(0, data, length);
    }
    digitalWrite( DC, 0);


}
void A095_initial()
{
  delay(150);
 
	OLED_SendCmdAndData(0xFE,0x04);
	OLED_SendCmdAndData(0x00,0xdc);
	OLED_SendCmdAndData(0x01,0x00);
	OLED_SendCmdAndData(0x02,0x02);
	OLED_SendCmdAndData(0x03,0x00);
	OLED_SendCmdAndData(0x04,0x00);
	OLED_SendCmdAndData(0x05,0x03);
	OLED_SendCmdAndData(0x06,0xBC);
	OLED_SendCmdAndData(0x07,0xCD);
	OLED_SendCmdAndData(0x08,0x08);

	OLED_SendCmdAndData(0x09,0xdc);
	OLED_SendCmdAndData(0x0a,0x00);
	OLED_SendCmdAndData(0x0b,0x02);
	OLED_SendCmdAndData(0x0c,0x00);
	OLED_SendCmdAndData(0x0d,0x00);
	OLED_SendCmdAndData(0x0e,0x02);
	OLED_SendCmdAndData(0x0f,0xBC);
	OLED_SendCmdAndData(0x10,0xCD);
	OLED_SendCmdAndData(0x11,0x08);

	OLED_SendCmdAndData(0x12,0xC2);
	OLED_SendCmdAndData(0x13,0x00);
	OLED_SendCmdAndData(0x14,0x34);
	OLED_SendCmdAndData(0x15,0x05);
	OLED_SendCmdAndData(0x16,0x00);
	OLED_SendCmdAndData(0x17,0x03);
	OLED_SendCmdAndData(0x18,0x15);
	OLED_SendCmdAndData(0x19,0x41);
	OLED_SendCmdAndData(0x1a,0x00);

	OLED_SendCmdAndData(0x1b,0xdc);
	OLED_SendCmdAndData(0x1c,0x00);
	OLED_SendCmdAndData(0x1d,0x04);
	OLED_SendCmdAndData(0x1e,0x00);
	OLED_SendCmdAndData(0x1f,0x00);
	OLED_SendCmdAndData(0x20,0x03);
	OLED_SendCmdAndData(0x21,0xBC);
	OLED_SendCmdAndData(0x22,0xCD);
	OLED_SendCmdAndData(0x23,0x08);

	OLED_SendCmdAndData(0x24,0xdc);
	OLED_SendCmdAndData(0x25,0x00);
	OLED_SendCmdAndData(0x26,0x04);
	OLED_SendCmdAndData(0x27,0x00);
	OLED_SendCmdAndData(0x28,0x00);
	OLED_SendCmdAndData(0x29,0x01);
	OLED_SendCmdAndData(0x2a,0xBC);
	OLED_SendCmdAndData(0x2b,0xCD);
	OLED_SendCmdAndData(0x2d,0x08);

	OLED_SendCmdAndData(0x4c,0x99);
	OLED_SendCmdAndData(0x4d,0x00);
	OLED_SendCmdAndData(0x4e,0x00);
	OLED_SendCmdAndData(0x4f,0x00);
	OLED_SendCmdAndData(0x50,0x01);
	OLED_SendCmdAndData(0x51,0xB0);
	OLED_SendCmdAndData(0x52,0xB5);
	OLED_SendCmdAndData(0x5a,0xe4);

	OLED_SendCmdAndData(0x5e,0x77);
	OLED_SendCmdAndData(0x5f,0x77);
	OLED_SendCmdAndData(0x60,0x34);
	OLED_SendCmdAndData(0x61,0x02);
	OLED_SendCmdAndData(0x62,0x81);

	OLED_SendCmdAndData(0xFE,0x07);
	OLED_SendCmdAndData(0x07,0x4F);
	OLED_SendCmdAndData(0xFE,0x01);

	OLED_SendCmdAndData(0x04,0x80);
	OLED_SendCmdAndData(0x05,0x65);
	OLED_SendCmdAndData(0x06,0x1E);

	OLED_SendCmdAndData(0x0E,0x8B);
	OLED_SendCmdAndData(0x0F,0x8B);
	OLED_SendCmdAndData(0x10,0x11);
	OLED_SendCmdAndData(0x11,0xA2);
	OLED_SendCmdAndData(0x12,0x80);
	OLED_SendCmdAndData(0x14,0x81);
	OLED_SendCmdAndData(0x15,0x82);
	OLED_SendCmdAndData(0x18,0x47);
	OLED_SendCmdAndData(0x19,0x36);
	OLED_SendCmdAndData(0x1A,0x10);
	OLED_SendCmdAndData(0x1C,0x57);
	OLED_SendCmdAndData(0x1D,0x02);
	OLED_SendCmdAndData(0x21,0xF8);
	OLED_SendCmdAndData(0x22,0x90);
	OLED_SendCmdAndData(0x23,0x00);

	OLED_SendCmdAndData(0x25,0x0A);
	OLED_SendCmdAndData(0x26,0x46);


	OLED_SendCmdAndData(0x2A,0x47);
	OLED_SendCmdAndData(0x2B,0xFF);
	OLED_SendCmdAndData(0x2D,0xAE);
	OLED_SendCmdAndData(0x2F,0xA5);


	OLED_SendCmdAndData(0x37,0x0C);
	OLED_SendCmdAndData(0x3a,0xA0);
	OLED_SendCmdAndData(0x3b,0x20);
	OLED_SendCmdAndData(0x3d,0x03);
	OLED_SendCmdAndData(0x3f,0x15);
	OLED_SendCmdAndData(0x40,0x06);
	OLED_SendCmdAndData(0x41,0x03);

	OLED_SendCmdAndData(0x42,0x14);
	OLED_SendCmdAndData(0x43,0x41);
	OLED_SendCmdAndData(0x44,0x25);
	OLED_SendCmdAndData(0x45,0x52);
	OLED_SendCmdAndData(0x46,0x36);
	OLED_SendCmdAndData(0x47,0x63);

	OLED_SendCmdAndData(0x4c,0x41);
	OLED_SendCmdAndData(0x4d,0x14);
	OLED_SendCmdAndData(0x4e,0x52);
	OLED_SendCmdAndData(0x4f,0x25);
	OLED_SendCmdAndData(0x50,0x63);
	OLED_SendCmdAndData(0x51,0x36);


	OLED_SendCmdAndData(0x56,0x14);
	OLED_SendCmdAndData(0x58,0x41);
	OLED_SendCmdAndData(0x59,0x25);
	OLED_SendCmdAndData(0x5a,0x52);
	OLED_SendCmdAndData(0x5b,0x36);
	OLED_SendCmdAndData(0x5c,0x63);
	OLED_SendCmdAndData(0x61,0x41);
	OLED_SendCmdAndData(0x62,0x14);
	OLED_SendCmdAndData(0x63,0x52);
	OLED_SendCmdAndData(0x64,0x25);
	OLED_SendCmdAndData(0x65,0x63);
	OLED_SendCmdAndData(0x66,0x36);



	OLED_SendCmdAndData(0x6D,0x90);
	OLED_SendCmdAndData(0x6E,0x40);
	OLED_SendCmdAndData(0x70,0xA5);
	OLED_SendCmdAndData(0x72,0x04);
	OLED_SendCmdAndData(0x73,0x15);
	OLED_SendCmdAndData(0xFE,0x0A);
	OLED_SendCmdAndData(0x29,0x90);
	OLED_SendCmdAndData(0xFE,0x05);
	OLED_SendCmdAndData(0x05,0x01);
	OLED_SendCmdAndData(0xFE,0x00);
	OLED_SendCmdAndData(0x35,0x00);


	OLED_SendCmd(0x11);//
	delay(470);
  //getchar();
	OLED_SendCmd(0x29);//
  //OLED_SendCmd(0x23);//

	OLED_SendCmdAndData(0x3A,0x77);
	OLED_SendCmdAndData(0x53,0x20);         //disable dimming
  
 
}




