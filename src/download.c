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

    printf("----------------------------------------\n"); // OPEN PASSIVE MODE
    char psv_hostname[INET6_ADDRSTRLEN], psv_port[6];
    get_passive(sfd, psv_hostname, psv_port);
    printf("Passive mode address: %s:%s\n", psv_hostname, psv_port);

    printf("----------------------------------------\n"); // CONNECT TO PASSIVE
    int psfd = get_connection(psv_hostname, psv_port);
    printf("Connected to passive (socket fd: %d)\n", psfd);

    printf("----------------------------------------\n"); // DOWNLOAD FILE
    const char *filename = get_filename(url.path);
    printf("Requesting file %s\n", url.path);
    request_file(sfd, url.path);
    printf("Starting download of %s\n", filename);
    get_file(psfd, filename);

    printf("----------------------------------------\n"); // CLOSE CONNECTIONS
    close(sfd);
    printf("Closed connection to server\n");
    close(psfd);
    printf("Closed connection to passive\n");

    return 0;
}
