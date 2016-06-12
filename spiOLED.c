#include "spiOLED.h"

void setPinMode()
{
  pinMode(RESET, 1);  //output =1
  pinMode(DC, 1);     //output =1
}

void reset()
{
    delay(1);
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








