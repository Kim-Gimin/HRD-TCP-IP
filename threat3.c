#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
void* thread_summation(void*);
//void* thread2(void*);
int sum = 0;

int main()
{
    pthread_t pt_1 = 0ul;
    pthread_t pt_2 = 0ul;
    int range1[] = {1, 5};
    int range2[] = {6, 10};
    if(pthread_create(&pt_1, NULL, thread_summation, (void*)range1) != 0)
    {
        fputs("create() errorr\r\n",stderr);
        exit(1);
    }
    if(pthread_create(&pt_2, NULL, thread_summation, (void*)range2) != 0)     
    {
        fputs("create() errorr\r\n",stderr);
        exit(1);
    }
    pthread_join(pt_1, NULL);
    pthread_join(pt_2, NULL);
    fprintf(stdout, "Summation : %d\r\n",sum);
    return 0;
}

void* thread_summation(void* args)
{
    int start = *((int*)args + 0);
    int end = *((int*)args + 1);
    while (start <= end)
    {
        sum += start;
        ++ start;

    }
    return NULL;
}
