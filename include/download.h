#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

enum url_read_state
{
    PROTOCOL,
    USER,
    HOST,
    PORT,
    PATH,
};

int parse_url(const char *url, char *protocol, char *username, char *password, char *host, char *port, char *path);
int download(const char *url);

#endif
