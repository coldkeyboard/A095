#ifndef __SPIOLED_H__
#define __SPIOLED_H__

#include <stdio.h>
#include "font.h"




#define RESET    15
#define DC       16
#define ON       0xff //for allPixelSwitch
#define OFF      0x00 //for allPixelSwitch

void SetupSPI();
void setPinMode();
void reset();
void initial();
void commandOutput( unsigned char command );
void dataOutput( unsigned char data );
void allPixelSwitch(unsigned char status);
void showP6x8Char(unsigned char ucIdxX, unsigned char ucIdxY, unsigned char ucData);
void showP6x8String(unsigned char ucIdxX, unsigned char ucIdxY, unsigned char ucDataStr[]);
void LED_SetPos(unsigned char ucIdxX, unsigned char ucIdxY);
void CharacterDemo();
void CharacterDemo2();
void scroll();
void A095_initial();
void OLED_SendCmdAndData(unsigned char command, unsigned char data);
void OLED_SendCmd (unsigned char command);
void OLED_SendData (unsigned char data);
void A095_test();
void ReadRegister();


#endif