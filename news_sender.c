#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define TTL 64

void error_handling(const char*);
/**
 * Server => sender
 * Receiver => Client
 */

int main(int argc, const char** argv)
{
        int send_sock = 0; // socket() 연결을 위한 변수
        int time_live = TTL;

        /* HDD File 클라이언트들에게 일방적으로 전송
         * FILE 구조체 : 주소는 HDD
         * fp
         */
        FILE * fp = NULL;
        char buffer[BUFSIZ] = {'\0',};
        struct sockaddr_in multi_addr;
        memset(&multi_addr, 0, sizeof multi_addr); // 초기화

        if(argc != 3)
        {
                error_handling("./NEWS_SENDER 192.168.0.1 9999");
        }
        // socket() 함수 연결
        send_sock = socket(PF_INET, SOCK_DGRAM, 0);
        if(send_sock == -1) error_handling("socket() error");
        multi_addr.sin_family = AF_INET;
        multi_addr.sin_addr.s_addr = inet_addr(argv[1]); // "192.168.0.1 <- 32bit
        multi_addr.sin_port = htons(atoi(argv[2])); // 16bit
        
        // TTL 설정, setsockopt() 함수를 사용해서 설정 변경
        setsockopt(send_sock, IPPROTO_IP, IP_MULTICAST_TTL, (void*)&time_live/*TTL*/, sizeof time_live);
        if((fp = fopen("news.txt", "r")) == NULL) error_handling("찾을 수 없슈");
        while(!feof(fp)) // EndOfFile => eof
        {
                fgets(buffer, BUFSIZ, fp); //stdin => keyboard, fp => file(news.txt)
                // sendto() 전송
                sendto(send_sock, buffer, strlen(buffer), 0, (struct sockaddr*)&multi_addr, sizeof multi_addr);
                sleep(2); // 2초 딜레이
        }
        fclose(fp); // 파일 리소스 해제
        close(send_sock); // 소켓 닫기

        
        return 0;
}
void error_handling(const char* _message)
{
        // 오류 출력
        //stderr -> 2
        fputs(_message, stderr);
        fputs("\r\n", stderr);
        exit(1);
}


