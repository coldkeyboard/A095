main:main.o spiOLED.o font.o ShowImage.o
	gcc -lwiringPi -o main main.o spiOLED.o font.o ShowImage.o
main.o:main.c main.h
	gcc -lwiringPi -c main.c
spiOLED.o:spiOLED.c spiOLED.h
	gcc -lwiringPi -c spiOLED.c
font.o:font.c font.h
	gcc -lwiringPi -c font.c
ShowImage.o:ShowImage.c ShowImage.h
	gcc -lwiringPi -c ShowImage.c
