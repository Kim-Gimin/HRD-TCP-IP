#include <stdio.h>
#include <unistd.h>
#include <signal.h>
//signal(정수, 함수)
//O/S 이벤트가 발생하면 함수를 호출해준다.

void timeout(int _signal)
{
    if(_signal == SIGALRM) // 14
    {
        puts("Time out!!");
    }
    alarm(2);   // 2초 후에 울린다.
}

void keycontrol(int _signal)
{
    if(_signal == SIGINT)
    {
        puts("Ctrl + c pressed.. \r\n");
    }
}

int main()
{
    signal(SIGALRM /*14*/, timeout);
    signal(SIGINT /*2*/, keycontrol);
    alarm(2);

    for(int i = 0; i < 3; ++i)
    {
            puts("wait... \r\n");
            sleep(100);
    }
    return 0;

}

