#ifndef RIO_H
#define RIO_H

#include <errno.h>
#include <unistd.h>

constexpr int RIO_BUFSIZE = 8192;

struct Rio_t {
    int rio_fd;
    int rio_cnt;
    char* rio_bufptr;
    char rio_buf[RIO_BUFSIZE];
};

void rio_readinitb(Rio_t* rp, int fd);
ssize_t rio_readn(int fd, char* usrbuf, size_t n);
ssize_t rio_written(int fd, char* usrbuf, size_t n);

#endif