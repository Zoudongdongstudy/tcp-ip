/*
 * @Author: ddupup 2287887780@qq.com
 * @Date: 2024-12-15 22:29:50
 * @LastEditors: ddupup 2287887780@qq.com
 * @LastEditTime: 2024-12-15 22:35:45
 * @FilePath: /tcp-ip-socket/ip-efficient-programming/tcpclient.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "skel.h"

// #include "library/tcp_server.c"
#include "library/tcp_client.c"

static void client(SOCKET s, struct sockaddr_in *peerp)
{
    int rc;
    char buf[120];

    for ( ; ; )
    {
        rc = recv(s, buf, sizeof(buf), 0);
        if (rc <= 0)
        {
            break;
        }
        
        write(1, buf, rc);
    }
}

int main(int argc, char **argv)
{
    struct sockaddr_in peer;
    SOCKET s;
    testInfo;
    INIT();

    s = tcp_client(argv[1], argv[2]);

    client(s, &peer);

    EXIT(0);
}