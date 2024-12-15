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

#define NLISTEN 5


char *program_name;

/// @brief 错误打印
/// @param status 打印错误后，非0则退出程序，否则返回
/// @param err 错误码，非0则打印错误码对应的错误信息
/// @param fmt 额外的打印
/// @param  
void error(int status, int err, char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s: ", program_name);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    if (err)
        fprintf(stderr, ": %s (%d)\n", strerror(err), err);
    if (status)
        EXIT(status);
}

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

/// @brief 占位程序，稍作修改即可
/// @param s 
/// @param peerp 
static void server(SOCKET s, struct sockaddr_in *peerp)
{
    send(s, "hello world!\n", 14, 0);
}


/// @brief 
/// @param host 指向一个字符串，可以是主机名，也可以是ip地址
/// @param port 指向一个字符串，可以是符号形式的服务器名，也可以是一个ASCII端口号
/// @return 
SOCKET tcp_server(char *host, char *port)
{
    struct sockaddr_in local;
    SOCKET s;
    const int on = 1;

    s = socket( AF_INET, SOCK_STREAM, 0);
    set_address( host, port, &local, "tcp");
    if (!isvalidsock(s))
        error(1, errno, "socket call failed");

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
        error(1, errno, "setsockopt failed");

    if (bind(s, (struct sockaddr *)&local, sizeof(local)))
        error(1, errno, "bind failed") ;

    if (listen(s, NLISTEN))
        error(1, errno, "listen failed") ;

    return s;
}