#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void error_handling(const char*);
int main(int argc, const char * argv[])
{
    int sock_sd = 0;
    FILE * fp = fopen("server.dat", "wb"); // flie 이름을 server.dat로 하겠다.
    char buf[BUFSIZ] = {'\0'};
    int read_count = 0;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof serv_addr);
    if(argc != 3)
    {
        error_handling("FILE_CLIENT 127.0.0.1 9999");
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    sock_sd = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_sd == -1) error_handling("socket()함수 에러");
    if(connect(sock_sd, (const struct sockaddr*)&serv_addr, sizeof serv_addr) == -1) \
            error_handling("connect() 에러");
    while((read_count = read(sock_sd, buf, BUFSIZ)) != 0)
    {
        fwrite((void*)buf, 1, read_count, fp);
    }
    puts("A file received.. \r\n");
    fclose(fp);
    close(sock_sd);
    return 0;
}
void error_handling(const char* _message)
{
    fputs(_message, stdout);
    fputs("\r\n", stdout);
    exit(1);
}

