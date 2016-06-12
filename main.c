#include "main.h"

static int myFd ;


void spiSetup (int speed)
{
  if ((myFd = wiringPiSPISetup (SPI_CHAN, speed)) < 0)
  {
    fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
    exit (EXIT_FAILURE) ;
  }
}

void main (void)
{
    int spi1;    
    int spiChannel = 0;
    int clock = 1000000;
    unsigned char Str[]="Hello Jimmy";
    //unsigned char test = '~';
    //printf("SPI is ready, spi1=%d\n", test);    

    printf("Starting SPI Test\n");
    wiringPiSetup();    
    spi1 = wiringPiSPISetup(spiChannel,clock);    
    if(spi1!=-1)
      printf("SPI is ready, spi1=%d\n", spi1);
    else
      printf("SPI Setup Fail, spi1=%d\n", spi1);
    
    setPinMode();
    reset();
    initial();        
    //allPixelSwitch(ON);
    showP6x8Char(0,0,'U');
    showP6x8Char(6,0,'S');
    showP6x8Char(12,0,'M');
    showP6x8Char(18,0,'P');


    showP6x8String(0,2,Str);
    showP6x8String(0,3,"Have a nice day");
    showP6x8String(0,5,"2016/06/10 :)");
    scroll();

    //allPixelSwitch(OFF);

}