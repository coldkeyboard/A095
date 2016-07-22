#include "BluetoothThread.h"

unsigned demoMode = 0;

void CreateThread()
{
   pthread_t id;
   int i,ret;
   ret = pthread_create(&id,NULL,(void *)Thread,NULL);
   if (ret != 0)
   {
        printf("Create thread error!\r\n");
   }
   else
   {
        printf("Thread is created!\r\n");
   }
   
//   for (i=0;i<5;i++)
//   {
//       printf("This is the main thread %d .\r\n",i);
//       sleep(i);
//   }
   //pthread_join(id,NULL);
   //return(0);
}

void Thread()
{
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // read data from the client
    bytes_read = read(client, buf, sizeof(buf));
    if( bytes_read > 0 ) {
        printf("received [%s]\n", buf);
    }

    // close connection
    close(client);
    close(s);
    //return 0;
    
    
}