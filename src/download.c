#include <stdio.h>
#include <string.h>
// ftp://[<user>:<password>@]<host>[:port][/<url-path>]

enum url_read_state
{
    PROTOCOL,
    USER,
    HOST,
    PORT,
    PATH,
};

int parse_url(const char *url, char *protocol, char *username, char *password, char *host, char *port, char *path)
{
    int state = PROTOCOL;

    while (1)
    {
        int n = 0;
        switch (state)
        {
        case PROTOCOL:
            printf("PROTOCOL\n");
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
            printf("USER\n");
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
            printf("HOST\n");
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
            printf("PORT\n");
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
            printf("PATH\n");
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

int main(int argc, char **argv)
{
    char protocol[16];
    char username[255];
    char password[255];
    char host[255];
    char port[6];
    char path[255];

    const char *url = "ftp://user:password@host:21/path/to/file";
    // const char *url = "ftp://user@host:21/path/to/file";
    // const char *url = "ftp://host:21/path/to/file";
    // const char *url = "ftp://host/path/to/file";
    // const char *url = "ftp://user@host";
    // const char *url = "ftp://user:password@host";

    parse_url(url, protocol, username, password, host, port, path);

    printf("\n");

    printf("protocol: %s\n", protocol);
    printf("username: %s\n", username);
    printf("password: %s\n", password);
    printf("host: %s\n", host);
    printf("port: %s\n", port);
    printf("path: %s\n", path);

    return 0;
}
