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

char *program_name;

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

static void server(SOCKET s, struct sockaddr_in *peerp)
{
    send(s, "hello world!\n", 14, 0);
}



int main(int argc, char **argv)
{
    struct sockaddr_in local;
    struct sockaddr_in peer;

    char *hname;
    char *sname;
    int peerlen;
    SOCKET sl;
    SOCKET s;
    const int on = 1;

    INIT();

    if (argc == 2)
    {
        hname = NULL;
        sname = argv[1];
    }
    else
    {
        hname = argv[1];
        sname = argv[2];
    }

    set_address( hname, sname, &local, "tcp");
    s = socket( AF_INET, SOCK_STREAM, 0);
    if (!isvalidsock(s))
        error(1, errno, "socket call failed");

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
        error(1, errno, "setsockopt failed");

    if (bind(s, (struct sockaddr *)&local, sizeof(local)))
        error(1, errno, "bind failed") ;

    if (listen(s, 5))
        error(1, errno, "listen failed") ;

    do
    {
        peerlen = sizeof(peer);
        sl = accept(s, (struct sockaddr *)&peer, &peerlen);
        if (!isvalidsock(sl))
            error(1, errno, "accept failed");
        server(sl, &peer);
        CLOSE(sl);

    }while(1);

    EXIT(0);
}