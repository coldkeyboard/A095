#include <stdio.h>
#include <pthread.h>
 
void thread()
{
    int i;
    for (i=0;i<3;i++)
    {
        printf("This is thread %d .\r\n",i);
        sleep(i);
     }
 }
 
int main()
{
   pthread_t id;
   int i,ret;
   ret = pthread_create(&id,NULL,(void *)thread,NULL);
   if (ret != 0)
   {
        printf("Create thread error!\r\n");
        //exit(1);
   }
   for (i=0;i<3;i++)
   {
       printf("This is the main thread %d .\r\n",i);
       sleep(i);
   }
   pthread_join(id,NULL);
   return(0);
}