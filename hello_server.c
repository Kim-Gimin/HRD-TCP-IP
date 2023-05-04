#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // linux library
#include <arpa/inet.h> // arpa library
#include <sys/socket.h> //socket library

void error_handling(const char* ); // function proto-type
int main(int argc, const char* argv[])
{
        int serv_sock = 0;
        int clnt_sock = 0;
        struct sockaddr_in serv_addr;
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size = 0u;
        char message[] = {"Hello world!"};
        if(argc != 2)
        {
                fprintf(stdout, "Usage : %s PORT \r\n", argv[0]);
                exit(1);
        }
        serv_sock = socket(PF_INET/*IPv4*/, SOCK_STREAM/*TCP*/, 0);
        if(serv_sock == -1) {
                error_handling("socket() error"); //:u, :redo
                exit(1);        
        }
        memset(&serv_addr, 0, sizeof serv_addr); // struct sockaddr_in initializing
        serv_addr.sin_family = AF_INET; //IPv4
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(atoi(argv[1]));
        
        int bind_state = bind(serv_sock, (struct sockaddr*)&serv_addr,sizeof serv_addr);
        
        if(bind_state == -1) {
                error_handling("bind() error");
                exit(1);
        }
        int listen_state = listen(serv_sock, 5);
        if(listen_state == -1)
        {
                error_handling("listen() error");
                exit(1);
        }
        clnt_addr_size = sizeof clnt_addr;
        clnt_sock = accept(serv_sock, (struct sockaddr*)&serv_addr, &clnt_addr_size);
        
        if(clnt_sock == -1) {
                error_handling("accept() error");
                exit(1);
        }

        write(clnt_sock, message, sizeof message);
        close(clnt_sock);
        close(serv_sock);


        return 0;
}
void error_handling(const char* _message)
{
    fputs(_message, stdout);
    fputs("\r\n", stdout);
    return;

}
