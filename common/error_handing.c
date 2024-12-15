#include "head.h"
#include "error_handing.h"




void error_handing(char *buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}
