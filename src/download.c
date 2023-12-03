#include "download.h"

int parse_url(const char *url, char *protocol, char *username, char *password, char *host, char *port, char *path)
{
    int state = PROTOCOL;

    while (1)
    {
        int n = 0;
        switch (state)
        {
        case PROTOCOL:
            if (sscanf(url, "%15[^:@/]://%n", protocol, &n) && n > 0)
            {
                state = USER;
                url += n;
            }
            else
            {
                return 1;
            }
            break;
        case USER:
            if (sscanf(url, "%255[^:@/]:%255[^:@/]@%n", username, password, &n) && n > 0)
            {
                url += n;
            }
            else if (sscanf(url, "%255[^:@/]@%n", username, &n) && n > 0)
            {
                url += n;
                password[0] = '\0';
            }
            else
            {
                username[0] = '\0';
                password[0] = '\0';
            }
            state = HOST;
            break;
        case HOST:
            if (sscanf(url, "%255[^:@/]:%n", host, &n) && n > 0)
            {
                state = PORT;
                url += n;
            }
            else if (sscanf(url, "%255[^:@/]/%n", host, &n) && n > 0)
            {
                port[0] = '\0';
                state = PATH;
                url += n;
            }
            else if (sscanf(url, "%255[^:/@]%n", host, &n) && n > 0)
            {
                port[0] = '\0';
                path[0] = '\0';
                return 0;
            }
            else
            {
                return 1;
            }
            break;
        case PORT:
            if (sscanf(url, "%5[0123456789]/%n", port, &n) && n > 0)
            {
                state = PATH;
                url += n;
            }
            else if (sscanf(url, "%5[0123456789]%n", port, &n) && n > 0)
            {
                path[0] = '\0';
                return 0;
            }
            else
            {
                port[0] = '\0';
                return 1;
            }
            break;
        case PATH:
            if (sscanf(url, "%255[^:@]%n", path, &n) && n > 0)
            {
                return 0;
            }
            else
            {
                path[0] = '\0';
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

int download(const char *url)
{
    char protocol[16],
        username[255],
        password[255],
        host[255],
        port[6],
        path[255];

    parse_url(url, protocol, username, password, host, port, path);

    printf("protocol: %s\n", protocol);
    printf("username: %s\n", username);
    printf("password: %s\n", password);
    printf("host: %s\n", host);
    printf("port: %s\n", port);
    printf("path: %s\n", path);

    return 0;
}
