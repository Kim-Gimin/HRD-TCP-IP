#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(const char*);
int main(int argc, const char* argv[])
{
    int sock = 0;
    char message[BUFSIZ] =  {'\0',};
    ssize_t str_length = 0u;
    socklen_t addr_size = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in from_addr;   //dummy 충돌방지
    if(argc != 3)
    {
        error_handling("UDP_ECHO_CLIENT 127.0.0.1 9999 \r\n");
    }
    socket(PF_INET, SOCK_DGRAM /*UDO*/, 0);
    if(sock == -1) error_handling("socket() 오류");
    memset(&serv_addr, 0, sizeof serv_addr);
    memset(&from_addr, 0, sizeof from_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // "127.0.0.1"
    serv_addr.sin_port = htons(atoi(argv[2]));
    while(1)
    {
        fputs("Input Your Message(Q to Quit) : ", stdout);
        fgets(message, BUFSIZ, stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
        {
                puts("Good bye !! \r\n");
                break;
        }
        sendto(sock, message, strlen(message), 0, (struct sockaddr*)&serv_addr, sizeof serv_addr);
        addr_size = sizeof from_addr;   //dummy
        str_length = recvfrom(sock, message, BUFSIZ, 0, (struct sockaddr*)&from_addr, (socklen_t*)&addr_size);
        message[str_length] = '\0'; // 맨 뒤에 널 문자 삽입
        fprintf(stdout, "Message from server : %s\r\n", message);
    }
    close(sock);

    return 0;
    }
    
void error_handling(const char * _message)
{
    fputs(_message, stdout);
    fputs("\r\n", stdout);
    exit(1);
}

