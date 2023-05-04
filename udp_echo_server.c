#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(const char*);
int main(int argc, const char* argv[])
{
    int serv_sock = 0;
    char message[BUFSIZ] = {'\0'};
    ssize_t str_length = 0u;
    socklen_t clnt_addr_size = 0u;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    memset(&serv_addr, 0, sizeof serv_addr); //구조체 0으로 초기화.
    memset(&clnt_addr, 0, sizeof clnt_addr); //구조체 0으로 초기화.
    if(argc != 2)
    {
        error_handling("UDP_ECHO_SERVER 9999 \r\n");
    }    
    serv_sock = socket(PF_INET, SOCK_DGRAM/*UDP*/, 0);
    if(serv_sock == -1) 
    { 
        error_handling("socket() 오류 \r\n");
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // MY IP or 127.0.0.1
    serv_addr.sin_port = htons(atoi(argv[1]));

    if((bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof serv_addr)) == - 1)
    {
        error_handling("bind() 오류 \r\n");
    }
    while(1)
    {
        clnt_addr_size = sizeof clnt_addr;
        str_length = recvfrom(serv_sock, message, BUFSIZ, 0, (struct sockaddr*)&clnt_addr,(socklen_t*) &clnt_addr_size);
        sendto(serv_sock, message, str_length, 0, (struct sockaddr*)&clnt_addr, clnt_addr_size);
    }
    close(serv_sock);


        return 0;
}
void error_handling(const char* _message)
{
        fputs(_message, stdout);
        fputs("\r\n", stdout);
        exit(1);
}

    
