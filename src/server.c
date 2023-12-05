#include "server.h"

// #include <arpa/inet.h>
// #include <netinet/in.h>

int get_status(int sfd)
{
    char buffer[2000];

    ssize_t bytes, total_bytes_read = 0;

    usleep(100000);
    while ((bytes = recv(sfd, buffer + total_bytes_read, sizeof buffer - total_bytes_read, 0)) > 0)
    {
        total_bytes_read += bytes;
        usleep(100000);
    };

    if (bytes < 0)
    {
        perror("recv");
        exit(EXIT_FAILURE);
    }
    buffer[bytes] = '\0';

    int status;
    if (sscanf(buffer, "%d", &status) != 1)
    {
        fprintf(stderr, "Invalid status line: %s\n", buffer);
        exit(EXIT_FAILURE);
    }
    printf("Full message:\n\"%s\"\n", buffer); // debug2
    printf("Status: %d\n\n", status);          // debug2

    return status;
}
// int get_status(int sfd)
// {
//     char buffer[2000];
//     ssize_t bytes = recv(sfd, buffer, sizeof buffer - 1, 0);
//     if (bytes < 0)
//     {
//         perror("recv");
//         exit(EXIT_FAILURE);
//     }
//     buffer[bytes] = '\0';

//     int status;
//     if (sscanf(buffer, "%d", &status) != 1)
//     {
//         fprintf(stderr, "Invalid status line: %s\n", buffer);
//         exit(EXIT_FAILURE);
//     }
//     printf("Full message:\n\"%s\"\n", buffer); // debug2
//     printf("Status: %d\n\n", status);          // debug2

//     return status;
// }

int get_connection(const char *hostname, const char *port)
{
    int sfd, s;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    // char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    s = getaddrinfo(hostname, port, &hints, &result);
    if (s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;

        close(sfd);
    }

    // struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
    // void *addr = &(ipv4->sin_addr);
    // inet_ntop(rp->ai_family, addr, ipstr, sizeof ipstr);
    // printf("Connected to %s:%s (%s)\n", hostname, port, ipstr);

    freeaddrinfo(result);

    if (rp == NULL)
    {
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }

    return sfd;
}

void auth(int sfd, const char *username, const char *password)
{
    char buf[266];
    int command_length;

    printf("1 Step -------------- (check if service ready for new user) | =220\n"); // debug1
    if (get_status(sfd) != SERVER_LOGIN_READY)
    {
        fprintf(stderr, "Service not ready for new user.\n");
        exit(EXIT_FAILURE);
    }

    printf("2 Step ------------------------------------- (sending user) | \n"); // debug1
    command_length = snprintf(buf, 266, "user %s\n", username);
    if (send(sfd, buf, command_length, 0) < 0)
    {
        fprintf(stderr, "Error sending username (%s).\n", username);
        exit(EXIT_FAILURE);
    }

    printf("3 Step ------------------ (check if service needs password) | =331\n"); // debug1
    if (get_status(sfd) == SERVER_PASSWORD_REQUIRED)
    {
        printf("4 Step -------------------------------- (send password) |\n"); // debug1
        command_length = snprintf(buf, 266, "pass %s\n", password);
        if (send(sfd, buf, command_length, 0) < 0)
        {
            fprintf(stderr, "Error sending password (%s).\n", password);
            exit(EXIT_FAILURE);
        }
    }

    printf("5 Step -------------------- (check if login was successful) | =230\n"); // debug1
    if (get_status(sfd) != SERVER_LOGIN_SUCCESS)
    {
        fprintf(stderr, "Login failed.\n");
        exit(EXIT_FAILURE);
    }
}

void get_passive(int sfd, char *host, char *port)
{
    char *in_buf = "pasv\n", out_buf[256];

    if (send(sfd, in_buf, strlen(in_buf), 0) < 0)
    {
        fprintf(stderr, "Error sending passive command.\n");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes = recv(sfd, out_buf, sizeof out_buf - 1, 0);
    if (bytes < 0)
    {
        perror("recv");
        exit(EXIT_FAILURE);
    }
    out_buf[bytes] = '\0';

    int code;
    uint8_t h1, h2, h3, h4, p1, p2;
    sscanf(out_buf, "%d %*[^(](%hhu, %hhu, %hhu, %hhu, %hhu, %hhu)\n", &code, &h1, &h2, &h3, &h4, &p1, &p2);
    if (code != SERVER_PASSIVE_READY)
    {
        fprintf(stderr, "Error entering passive mode.\n");
        exit(EXIT_FAILURE);
    }

    sprintf(host, "%hhu.%hhu.%hhu.%hhu", h1, h2, h3, h4);
    sprintf(port, "%hu", p1 * 256 + p2);
}

void request_file(int sfd, const char *path)
{
    char buf[266];
    int command_length;

    command_length = snprintf(buf, 266, "retr %s\n", path);
    if (send(sfd, buf, command_length, 0) < 0)
    {
        fprintf(stderr, "Error sending file request (%s).\n", path);
        exit(EXIT_FAILURE);
    }

    int status = get_status(sfd);
    if (status == FILE_STATUS_OKAY || status == CLOSING_DATA_CONNECTION)
    {
        printf("File ok.\n");
        return;
    }
    else
    {
        fprintf(stderr, "File unavailable.\n");
        exit(EXIT_FAILURE);
    }
}

void get_file(int psfd, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file (%s).\n", filename);
        exit(EXIT_FAILURE);
    }

    char buf[256];
    ssize_t bytes;
    while ((bytes = recv(psfd, buf, sizeof buf - 1, 0)) > 0)
    {
        buf[bytes] = '\0';
        fprintf(fp, "%s", buf);
    }

    fclose(fp);
}
