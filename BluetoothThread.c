#include "BluetoothThread.h"

unsigned char demoMode = 'a';

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
    int scosock;

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
    
   	handle_connection(client, scosock);
//    memset(buf, 0, sizeof(buf)); 
//
//    // read data from the client
//    bytes_read = read(client, buf, sizeof(buf));
//    if( bytes_read > 0 ) {
//        printf("received [%s]\n", buf);
//    }
//    demoMode = buf[0];

    // close connection
    //close(client);
    //close(s);
    //return 0;    
}

int handle_connection(int rfcommsock, int scosock)
{
  char hello_str[] = "SPP Server: Hello, Client !!";
	char rfcommbuffer[255];
	int len;    
    // Server 端傳??hello 字串??Client �?
    len = send(rfcommsock, hello_str, sizeof(hello_str), 0);
    if( len < 0 )
    {
        perror("rfcomm send ");
        return -1;
    }    
	while (1)
	{
   printf("here 1");
		len = recv(rfcommsock, rfcommbuffer, 255, 0);

		// EWOULDBLOCK indicates the socket would block if we had a
		// blocking socket.  we'll safely continue if we receive that
		// error.  treat all other errors as fatal
		if (len < 0 && errno != EWOULDBLOCK)
		{
			perror("rfcomm recv ");
			break;
		}
		else if (len > 0)
		{
			rfcommbuffer[len] = '\0';

			printf("rfcomm received: %s\n", rfcommbuffer);
			send(rfcommsock, "ATOK\r\n", 6, 0);
		} 
   if (len == 1)
   {
     demoMode = rfcommbuffer[0];
   } 
      printf("here 2");
	}
    printf("here 3");
	close(rfcommsock);
	printf("client disconnected\n");
	return 0;
}