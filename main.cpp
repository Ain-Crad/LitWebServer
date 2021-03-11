#include <pthread.h>

#include <iostream>

#include "BoundedBuffer.h"
#include "Network.h"
#include "Rio.h"

constexpr int NTHREADS = 4;
constexpr int SBUFSIZE = 16;

Sbuf_t sbuf;

void* thread(void* varg);

int main(int argc, char* argv[]) {
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    listenfd = open_listenfd(argv[1]);

    sbuf_init(&sbuf, SBUFSIZE);
    for (int i = 0; i < NTHREADS; ++i) {
        pthread_create(&tid, nullptr, thread, nullptr);
    }

    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd, (sockaddr*)&clientaddr, &clientlen);
        sbuf_insert(&sbuf, connfd);
        getnameinfo((sockaddr*)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
    }

    return 0;
}

void* thread(void* vargp) {
    pthread_detach(pthread_self());
    while (1) {
        int connfd = sbuf_remove(&sbuf);
        doit(connfd);
        close(connfd);
    }
}