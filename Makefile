main:main.o spiOLED.o font.o ShowImage.o BluetoothThread.o
	gcc -lwiringPi -lpthread -lbluetooth -o main main.o spiOLED.o font.o ShowImage.o BluetoothThread.o
main.o:main.c main.h
	gcc -lwiringPi -c main.c
spiOLED.o:spiOLED.c spiOLED.h
	gcc -lwiringPi -c spiOLED.c
font.o:font.c font.h
	gcc -lwiringPi -c font.c
ShowImage.o:ShowImage.c ShowImage.h
	gcc -lwiringPi -c ShowImage.c
BluetoothThread.o:BluetoothThread.c BluetoothThread.h
	gcc -lpthread -lbluetooth -c BluetoothThread.c
