#ifndef NETWORK_H
#define NETWORK_H

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>

constexpr int LISTENQ = 1024;

int open_clientfd(char* hostname, char* port);

#endif