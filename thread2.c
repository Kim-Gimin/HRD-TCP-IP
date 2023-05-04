#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
// task function

void* thread_main(void*);
int main()
{
    pthread_t pt_id = 0ul;
    int thread_param = 10;
    void* thread_return = NULL; 
    // thread_main task 끝났을 때 받을 값
    if(pthread_create(&pt_id, NULL, thread_main, (void*)&thread_param) != 0)
    {
        fputs("thread creadte() error\r\n",stderr);
        exit(1);
    }
    if(pthread_join(pt_id, &thread_return) != 0)
    {
        fputs("pthread_join() error\r\n", stderr);
        exit(1);
    }
    fprintf(stdout, "Returned message %s\r\n", (const char*)thread_return);
    free(thread_return); //heap memory 해제
    thread_return = NULL;

    return 0;
}

void* thread_main(void* args)
{
    int param = *((int*)args);
    char* message = (char*)malloc(sizeof (char) *50);
    strcpy(message, "안녕 나는 빡빡이야\r\n");
    for(int i = 0; i < param; ++i)
    {
        sleep(1);
        puts("나는 빡빡이다.\r\n");
    }
    return (void*)message;
    

}

