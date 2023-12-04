#include "url.h"

struct URL parse_url(const char *arg)
{
    int state = PROTOCOL;
    struct URL url = {"", "", "", "", "", "", ""};

    while (state != END)
    {
        int n = 0;
        switch (state)
        {
        case PROTOCOL:
            // printf("PROTOCOL: %s\n", arg);
            if (sscanf(arg, "%15[^:@/]://%n", url.protocol, &n) && n > 0)
            {
                state = USER;
                arg += n;
            }
            else
            {
                // fprintf(stderr, "error: protocol not found for url: %s\n", arg);
                exit(EXIT_FAILURE);
            }
            break;
        case USER:
            // printf("USER: %s\n", arg);
            if (sscanf(arg, "%255[^:@/]:%255[^:@/]@%n", url.username, url.password, &n) && n > 0)
            {
                arg += n;
            }
            else if (sscanf(arg, "%255[^:@/]@%n", url.username, &n) && n > 0)
            {
                url.password[0] = '\0';
                arg += n;
            }
            else
            {
                url.username[0] = '\0';
                url.password[0] = '\0';
            }
            state = HOST;
            break;
        case HOST:
            // printf("HOST: %s\n", arg);
            if (sscanf(arg, "%255[^:/]:%n", url.hostname, &n) && n > 0)
            {
                state = PORT;
            }
            else if (sscanf(arg, "%255[^:/]/%n", url.hostname, &n) && n > 0)
            {
                state = PATH;
            }
            else if (sscanf(arg, "%255[^:/]%n", url.hostname, &n) && n > 0)
            {
                state = END;
            }
            else
            {
                // fprintf(stderr, "error: host not found for url: %s\n", arg);
                exit(EXIT_FAILURE);
            }
            arg += n;
            break;
        case PORT:
            // printf("PORT: %s\n", arg);
            if (sscanf(arg, "%5[0123456789]/%n", url.port, &n) && n > 0)
            {
                state = PATH;
            }
            else if (sscanf(arg, "%5[0123456789]%n", url.port, &n) && n > 0)
            {
                state = END;
            }
            else
            {
                // fprintf(stderr, "error: port not found for url: %s\n", arg);
                exit(EXIT_FAILURE);
            }
            arg += n;
            break;
        case PATH:
            // printf("PATH: %s\n", arg);
            if (sscanf(arg, "%255[^:@]%n", url.path, &n) == -1)
            {
                exit(EXIT_FAILURE);
            }
            arg += n;
            state = END;
            break;
        }
    }
    if (strlen(arg) > 0) // If there is something left in arg, it is an error
    {
        exit(EXIT_FAILURE);
    }
    if (strlen(url.username) == 0) // If username is empty, set it to anonymous
    {
        strcpy(url.username, "anonymous");
    }
    if (strlen(url.port) == 0) // If port is empty, set it to 21
    {
        strcpy(url.port, "21");
    }
    return url;
}

void print_url(struct URL url)
{
    printf("protocol: %s\n", url.protocol);
    printf("username: %s\n", url.username);
    printf("password: %s\n", url.password);
    printf("host: %s\n", url.hostname);
    printf("port: %s\n", url.port);
    printf("path: %s\n", url.path);
}