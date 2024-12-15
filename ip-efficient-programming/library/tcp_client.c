/*
 * @Author: ddupup 2287887780@qq.com
 * @Date: 2024-12-15 22:27:25
 * @LastEditors: ddupup 2287887780@qq.com
 * @LastEditTime: 2024-12-15 22:43:33
 * @FilePath: /tcp-ip-socket/ip-efficient-programming/library/tcp_client.c
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

#include "tcp_server.h"

#define NLISTEN 5


char *program_name;

/// @brief 将sockaddr_in结构体清零，并将地址族设置为AF_INET
/// @param hname 
/// @param sname 
/// @param sap 
/// @param protocol 
static void set_address(char *hname, char *sname, struct sockaddr_in *sap, char *protocol)
{
    struct servent *sp;
    struct hostent *hp;
    char *endptr;
    short port;

    bzero(sap, sizeof(*sap));
    sap->sin_family = AF_INET;
    if (hname != NULL)
    {
        if (!inet_aton(hname, &sap->sin_addr))
        {
            hp = gethostbyname(hname);
            if ( hp == NULL)
            {
                error(1, 0, "unknow host:%s\n", hname);
            }
            sap->sin_addr.s_addr = (struct sockaddr *)hp->h_addr_list;
        }
    } 
    else
    {
        sap->sin_addr.s_addr = htonl(INADDR_ANY);
    }

    port = strtol(sname, &endptr, 0);
    if (*endptr == '\0')
        sap->sin_port = htons(port);
    else
    {
        sp = getservbyname(sname, protocol);
        if (sp == NULL) 
            error(1, 0, "unknow server:%s\n", hname);
        sap->sin_port = sp->s_port;
    }
}

SOCKET tcp_client(char *hname, char *sname)
{
    struct sockaddr_in peer;
    SOCKET s;


    set_address(hname, sname, &peer, sizeof(peer));
    s = socket( AF_INET, SOCK_STREAM, 0);

    if (!isvalidsock(s))
        error(1, errno, "socket call failed");

    if (connect(s, (struct sockaddr *)&peer, sizeof(peer)))
        error(1, errno, "connect failed");
    
    // client(s, &peer);1

    return s;
}
