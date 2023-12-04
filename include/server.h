#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

/**
 * https://man7.org/linux/man-pages/man3/getaddrinfo.3.html
 */

// Server Status Codes
#define SERVER_LOGIN_READY 220
#define SERVER_PASSWORD_REQUIRED 331
#define SERVER_LOGIN_SUCCESS 230

int get_status(int sfd);

int get_connection(const char *hostname, const char *port);

void auth(int sfd, const char *username, const char *password);

#endif