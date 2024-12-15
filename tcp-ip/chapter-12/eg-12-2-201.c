#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;

    FD_ZERO(&reads);
    FD_SET(STDIN_FILENO, &reads);

    timeout.tv_sec = 5;

    while(1)
    {
        temps = reads;
        timeout.tv_sec = 2;
        result = select(1, &temps, 0, 0, &timeout);
        
        if (-1 == result)
        {
            puts("select() error");
            break;
        }
        else if(0 == result)
        {
            puts("select() timeout");
        }
        else
        {
            if (FD_ISSET(0, &temps))
            {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("msg:%s", buf);
            }
        }
    }

    return 0;
}