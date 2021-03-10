#ifndef NETWORK_H
#define NETWORK_H

#include <fcntl.h>
#include <netdb.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Rio.h"

constexpr int LISTENQ = 1024;
constexpr int MAXLINE = 10240;
constexpr int MAXBUF = 10240;

int open_clientfd(char* hostname, char* port);
int open_listenfd(char* port);

void doit(int fd);
void read_requesthdrs(Rio_t* rp);
int parse_uri(char* uri, char* filename, char* cgiargs);
void serve_static(int fd, char* filename, int filesize);
void get_filetype(char* filename, char* filetype);
void serve_dynamic(int fd, char* filename, char* cgiargs);
void clienterror(int fd, const char* cause, const char* errnum, const char* shortmsg, const char* longmsg);

#endif