#include "server.h"

// #include <arpa/inet.h>
// #include <netinet/in.h>

int get_status(int sfd)
{
    char buffer[256];
    ssize_t bytes = recv(sfd, buffer, sizeof buffer - 1, 0);
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

    return status;
}

int get_connection(const char *hostname, const char *port)
{
    int sfd, s;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    // char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
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

    if (get_status(sfd) != SERVER_LOGIN_READY)
    {
        fprintf(stderr, "Service not ready for new user.\n");
        exit(EXIT_FAILURE);
    }

    command_length = snprintf(buf, 266, "user %s\n", username);
    if (send(sfd, buf, command_length, 0) < 0)
    {
        fprintf(stderr, "Error sending username (%s).\n", username);
        exit(EXIT_FAILURE);
    }

    if (get_status(sfd) == SERVER_PASSWORD_REQUIRED)
    {
        command_length = snprintf(buf, 266, "pass %s\n", password);
        if (send(sfd, buf, command_length, 0) < 0)
        {
            fprintf(stderr, "Error sending password (%s).\n", password);
            exit(EXIT_FAILURE);
        }
    }

    if (get_status(sfd) != SERVER_LOGIN_SUCCESS)
    {
        fprintf(stderr, "Login failed.\n");
        exit(EXIT_FAILURE);
    }
}
