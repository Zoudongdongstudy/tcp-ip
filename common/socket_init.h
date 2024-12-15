#ifndef SOCKET_INTI_H
#define SOCKET_INTI_H

#include "head.h"

int init_socket(int type, int *fd, const char *ip, int port, int protocol_type)
{
    *fd = socket(PF_INET, SOCK_STREAM, 0);
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family        = AF_INET;
    recv_addr.sin_addr.s_addr   = inet_addr(argv[1]);
    recv_addr.sin_port          = htons(argv[2]);
} 

#endif // SOCKET_INTI_H