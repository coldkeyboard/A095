#ifndef __BLUETOOTHTHREAD_H__
#define __BLUETOOTHTHREAD_H__

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
void CreateThread();
void Thread();
int handle_connection(int rfcommsock, int scosock);

#endif