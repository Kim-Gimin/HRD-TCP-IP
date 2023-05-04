#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define RLT_SIZE 4
#define OPSZ 4 // 피연산자는 4까지

int main(int argc, const char* argv[])
{
    int sock = 0;
    char op_message[BUFSIZ] = {'\0',};
    int result = 0;
    int opand_count = 0;
    struct sockaddr_in serv_addr;
    if(argc != 3)
    {
        puts("OP_CLIENT 127.0.0.1 9999");
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        puts("socket() 함수, 오류\r\n");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof serv_addr);

    // IPM PORT넣기
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof serv_addr) == - 1)
    {
            puts("connect() 함수 오류\r\n");
            exit(1);
    }
    else
    {
            puts("Connected .... \r\n");
    }
    fputs("Operand count : ", stdout);
    scanf("%d", &opand_count);
    op_message[0] = (char)opand_count;
    for(int i = 0; i < opand_count; ++i)
    {
        printf("operator : ");
        scanf("%d", (int*)&op_message[i * OPSZ + 1]);
    }
    fgetc(stdin);
    fputs("Operator : ", stdout);
    scanf("%c", &op_message[opand_count * OPSZ + 1]);
    write(sock, op_message, opand_count * OPSZ + 2);
    read(sock, &result, RLT_SIZE);
    printf("Operation result : %d\r\n", result);
    close(sock);

    return 0;
}


