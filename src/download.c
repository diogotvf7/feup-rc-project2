#include "download.h"

int download(const char *arg)
{
    printf("----------------------------------------\n"); // PARSE URL
    struct URL url = parse_url(arg);
    print_url(url);

    printf("----------------------------------------\n"); // CONNECT TO SERVER
    int sfd = get_connection(url.hostname, url.port);
    printf("Connected to server (socket fd: %d)\n", sfd);

    printf("----------------------------------------\n"); // AUTHENTICATE
    auth(sfd, url.username, url.password);
    printf("Successfully authenticated as %s\n", url.username);

    return 0;
}
