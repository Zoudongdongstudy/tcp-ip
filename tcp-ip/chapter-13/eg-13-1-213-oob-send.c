
#include "../common/head.h"
#include "../common/error_handing.h"

#define BUF_SIZE 30

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in recv_addr;

    if (3 != argc)
    {
        printf("Usage:%s <ip> <port>\n", argv[0]);
        exit(1);
    } 

    printf("ip:%s, port:%s\n", argv[1],argv[2]);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family        = AF_INET;
    recv_addr.sin_addr.s_addr   = inet_addr(argv[1]);
    recv_addr.sin_port          = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr)) == -1)
    {
        error_handing("connect() error!");
    }

    write(sock, "123\n", strlen("123\n"));
    send(sock, "4\n", strlen("4\n"), MSG_OOB);
    write(sock, "567\n", strlen("567\n"));
    send(sock, "890\n", strlen("890\n"), MSG_OOB);
    close(sock);

    return 0;
}



