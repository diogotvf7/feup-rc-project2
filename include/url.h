#ifndef URL_H
#define URL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum url_read_state
{
    PROTOCOL,
    USER,
    HOST,
    PORT,
    PATH,
    END,
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

struct URL parse_url(const char *arg);

void print_url(struct URL url);

#endif