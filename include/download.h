#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#include "util.h"

enum url_read_state
{
    PROTOCOL,
    USER,
    HOST,
    PORT,
    PATH,
};

struct URL
{
    char protocol[16];
    char username[256];
    char password[256];
    char hostname[256];
    char ip[256];
    char port[16];
    char path[256];
};

int parse_url(const char *arg, struct URL *url);
int download(const char *url);

#endif
