#include "main.h"

extern unsigned demoMode;
void main (void)
{
    unsigned currentMode=0;
    SetupSPI();    
    setPinMode();
    reset();
    initial();   
    CreateThread();
    //demoMode=2;
    while(1)
    {        
        switch (demoMode) 
        {
            case 0:
              CharacterDemo(); 
              break;
            case 1:
              ShowImage("7.bmp");
              break;
            default:
              ShowImage("6.bmp");
              break;             
        }    
        while(demoMode == currentMode);
    }
    //allPixelSwitch(OFF);

}