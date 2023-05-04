#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

void* reading(void*);   //read()
void* accumulate(void*);

int number = 0;
sem_t sem_one;
sem_t sem_two;
int main()
{
    pthread_t pt_id1 = 0ul;
    pthread_t pt_id2 = 0ul;
    /*
     * semaphore 초기화
     *
     */
    sem_init(&sem_one, 0, 0/*key_value*/);  //sem_one key = 0;
    sem_init(&sem_two, 0, 1/*key_value*/);  //sem_two key = 0;

    pthread_create(&pt_id1, NULL, reading, NULL);
    pthread_create(&pt_id2, NULL, accumulate, NULL);


    pthread_join(pt_id1, NULL);
    pthread_join(pt_id2, NULL);
    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;
}

void* reading(void* args)
{
    for(int i = 0; i < 5; ++i)
    {
        sem_wait(&sem_two);
        scanf("%d", &number);
        sem_post(&sem_one);
    }
    return NULL;
}
void* accumulate(void* args)
{
    int summation = 0;
    for(int i = 0; i < 5; ++i)
    {
        sem_wait(&sem_one);
        summation += number;
        sem_post(&sem_two);
    }
    fprintf(stdout, "RESULT : %d\r\n", summation);
    return NULL;
}

