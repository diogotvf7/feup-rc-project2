#include "download.h"

// int parse_url(const char *url, char *protocol, char *username, char *password, char *host, char *port, char *path)
int parse_url(const char *arg, struct URL *url)
{
    int state = PROTOCOL;

    while (1)
    {
        int n = 0;
        switch (state)
        {
        case PROTOCOL:
            if (sscanf(arg, "%15[^:@/]://%n", url->protocol, &n) && n > 0)
            {
                state = USER;
                arg += n;
            }
            else
            {
                return 1;
            }
            break;
        case USER:
            if (sscanf(arg, "%255[^:@/]:%255[^:@/]@%n", url->username, url->password, &n) && n > 0)
            {
                arg += n;
            }
            else if (sscanf(arg, "%255[^:@/]@%n", url->username, &n) && n > 0)
            {
                arg += n;
                url->password[0] = '\0';
            }
            else
            {
                url->username[0] = '\0';
                url->password[0] = '\0';
            }
            state = HOST;
            break;
        case HOST:
            if (sscanf(arg, "%255[^:@/]:%n", url->hostname, &n) && n > 0)
            {
                state = PORT;
                arg += n;
            }
            else if (sscanf(arg, "%255[^:@/]/%n", url->hostname, &n) && n > 0)
            {
                url->port[0] = '\0';
                state = PATH;
                arg += n;
            }
            else if (sscanf(arg, "%255[^:/@]%n", url->hostname, &n) && n > 0)
            {
                url->port[0] = '\0';
                url->path[0] = '\0';
                return 0;
            }
            else
            {
                return 1;
            }

            break;
        case PORT:
            if (sscanf(arg, "%5[0123456789]/%n", url->port, &n) && n > 0)
            {
                state = PATH;
                arg += n;
            }
            else if (sscanf(arg, "%5[0123456789]%n", url->port, &n) && n > 0)
            {
                url->path[0] = '\0';
                return 0;
            }
            else
            {
                url->port[0] = '\0';
                return 1;
            }
            break;
        case PATH:
            if (sscanf(arg, "%255[^:@]%n", url->path, &n) && n > 0)
            {
                return 0;
            }
            else
            {
                url->path[0] = '\0';
                return 0;
            }
            break;
        };
    }

    return 0;
}

// int connect()
// {
//     struct addrinfo;
//     return 0;
// }

// int auth()
// {
//     return 0;
// }

int download(const char *arg)
{
    // ---------------------------------------------- PARSE URL
    struct URL url;

    parse_url(arg, &url);

    printf("protocol: %s\n", url.protocol);
    printf("username: %s\n", url.username);
    printf("password: %s\n", url.password);
    printf("host: %s\n", url.hostname);
    printf("port: %s\n", url.port);
    printf("path: %s\n", url.path);
    // ---------------------------------------------- PARSE URL

    // ---------------------------------------------- GET HOST IP

    struct hostent *h = malloc(sizeof(struct hostent));
    hostname_to_ip(url.hostname, h);
    printf("Hello world!\n");

    strcpy(url.ip, inet_ntoa(*((struct in_addr *)h->h_addr)));

    printf("ip: %s\n", url.ip);

    return 0;
}
