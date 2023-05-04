#include <stdio.h>
#include <arpa/inet.h>
int main()
{
    const char* str1 = "1.2.3.4";
    const char* str2 = "1.23.4.255";
    unsigned long convert_value = inet_addr(str1);
    if(convert_value == INADDR_NONE)
    {
            puts("Convert Error\r\n");
    }
    else
    {
            printf("Convert Value : %lu\r\n", convert_value);
    }
    convert_value = inet_addr(str2);

 
    if(convert_value == INADDR_NONE)
    {
            puts("Convert Error\r\n");
    }
    else
    {
            printf("Convert Value : %lu#x\r\n", convert_value);
    }



return 0;
}
