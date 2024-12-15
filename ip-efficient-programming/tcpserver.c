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

#include "library/tcp_server.c"


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

    s = socket( AF_INET, SOCK_STREAM, 0);
    s = tcp_server(hname, sname);

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