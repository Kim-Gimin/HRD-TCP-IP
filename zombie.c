#include <stdio.h>
#include <unistd.h> //fork() 함수 사용
int main()
{
    pid_t pid = fork();
    if(pid == 0) // pid가 0이면 자식프로세스
    {
        //자식프로세스
        puts("Hello, this is child proces. \r\n");
    }
    else
    {
        //부모프로세스
        printf("The child process PID : %d\r\n", pid);
        sleep(30); // 30 seconds 쉬어라.
    }
    if(pid == 0)
    {
        puts("End child process\r\n");
    }
    else
    {
        puts("End parent process \r\n");
    }
    return 0;
}
