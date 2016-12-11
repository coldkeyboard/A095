#include "main.h"

extern unsigned char demoMode;
void main (void)
{
    unsigned char currentMode= 'a';
    SetupSPI();    
    setPinMode();
    //getchar();
    reset();
    A095_initial();
    A095_test();
    while(1)
    {
    }
    //initial();   
    //CreateThread();
    //demoMode=2;
//    while(1)
//    {
//        currentMode = demoMode; 
//        printf("demoMode [%d]\n", demoMode);    
//        printf("currentMode [%d]\n", currentMode);     
//        switch (demoMode) 
//        {
//            case 'a':
//              CharacterDemo(); 
//              printf("currentMode [%d]\n", currentMode);
//              break;
//            case 'b':
//              CharacterDemo2();
//              break;
//            case 'c':
//              ShowImage("/home/pi/Jimmy/MyOLED/RPI_OLED/7.bmp");
//              break;
//            default:
//              ShowImage("/home/pi/Jimmy/MyOLED/RPI_OLED/6.bmp");
//              break;             
//        }    
//        while(demoMode == currentMode);
//    }
    //allPixelSwitch(OFF);

}