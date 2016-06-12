main:main.o spiOLED.o font.o
	gcc -lwiringPi -o main main.o spiOLED.o font.o
main.o:main.c main.h
	gcc -lwiringPi -c main.c
spiOLED.o:spiOLED.c spiOLED.h
	gcc -lwiringPi -c spiOLED.c
font.o:font.c font.h
	gcc -lwiringPi -c font.c
