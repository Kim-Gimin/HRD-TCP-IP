#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int _signal)
{
    if(_signal == SIGALRM)
    {
        puts("Time out \r\n");
    }
    alarm(2);
}

int main()
{
    struct sigaction act;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask); // sigemptyset() 함수가
    //sa_mask를 초기화해주는 함수.
    act.sa_flags = 0; //기본이 0으로 초기화.
    sigaction(SIGALRM, &act, 0); //sigaction()함수에 구조체 변수 전달
    alarm(2);
    for(int i = 0; i < 3; ++i)
    {
        puts("wait .. \r\n");
        sleep(100);
    }
    return 0;
}

