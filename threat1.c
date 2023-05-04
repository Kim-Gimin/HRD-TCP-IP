#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void* thread_main(void* args)
{
    int param = *((int *)args);
    for(int i = 0; i < param; ++i)
    {
        sleep(1);
        puts(" I'm 그루트\r\n");
    }
    return NULL;
}
int main()
{
    pthread_t pt_id = 0u;
    int thread_param = 10;
    int state = pthread_create(&pt_id/* os가 줄 값 */ , NULL, thread_main/*함수 포인터*/, (void*)&thread_param);
    if(state != 0)
    {
        fputs("Thread 고장\r\n",stderr);
        exit(1);
    }
    sleep(20);

    return 0;
}
