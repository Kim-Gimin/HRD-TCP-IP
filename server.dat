#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

static void error_handling(const char *);
int main(int argc, const char* argv[])
{
    int serv_sd = 0;
    int clnt_sd = 0;
    FILE * fp = NULL;
    char buf[BUFSIZ] = {'\0',};
    int read_count = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    memset(&serv_addr, 0, sizeof serv_addr);
    memset(&clnt_addr, 0, sizeof clnt_addr);
    socklen_t clnt_size = 0u;
    if(argc != 2)
    {
        error_handling("FILE_SERVER 9999\r\n");
    }
    fp = fopen("file_server.c", "rb"); //HDD에서 FLIE연결해오
    
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sd == -1) error_handling("socket() 오류\r\n");
    serv_addr.sin_family = AF_INET; //IPv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1])); //PORT
    if(bind(serv_sd, (struct sockaddr*)&serv_addr, sizeof serv_addr) == -1) error_handling("bind() 오류\r\n");
    if(listen(serv_sd, 5) == -1) error_handling("listen()오류\r\n");
    clnt_size = sizeof clnt_addr;
    clnt_sd = accept(serv_sd, (struct sockaddr*)&clnt_addr, (socklen_t*)&clnt_size);
    
    while(1) // 파일 전송을 위한 구문
    {
        read_count = fread((void*)buf, 1, BUFSIZ, fp); // fp를 통해서 바이트 써주기
        if(read_count < BUFSIZ) {
            write(clnt_sd, buf, read_count);
            break;
        }
        write(clnt_sd, buf, BUFSIZ);
   
    }
    shutdown(clnt_sd, SHUT_WR); //파일 전송(write mode) 완료후 서버 닫기

    read(clnt_sd, buf, BUFSIZ);
    fprintf(stdout, "Message from client : %s\r\n", buf);

    fclose(fp); // 리소스해제
    close(clnt_sd);
    close(serv_sd);


    return 0;
}

void error_handling(const char* _message)
{
        fputs(_message, stdout);
        fputs("\r\n", stdout);
        exit(1);
}
