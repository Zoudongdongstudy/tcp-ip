#include <signal.h>
#include <netinet/in.h>
#include <fcntl.h>

#include "../common/head.h"
#include "../common/error_handing.h"
#define BUF_SIZE 30

void urg_handler(int signo);

int acpt_sock;
int recv_sock;

int main(int argc, char* argv[])
{
    struct sockaddr_in recv_addr, serv_addr;
    int str_len, state;
    struct sigaction act;


    return 0;
}


void urg_handler(int signo)
{
    int str_len;
    char buf[BUF_SIZE];\
    str_len = recv(recv_sock, buf, sizeof(buf) - 1, MSG_OOB);
    buf[str_len] = 0;
    printf("Urgent msg:%s \n", buf);
}