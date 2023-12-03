#include "util.h"

int hostname_to_ip(const char *hostname, struct hostent *h)
{
    if ((h = gethostbyname(hostname)) == NULL)
    {
        herror("gethostbyname()");
        exit(-1);
    }

    return 0;
}
