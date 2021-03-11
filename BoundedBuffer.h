#ifndef BOUNDEDBUFFER_H
#define BOUNDEDBUFFER_H

#include <semaphore.h>

#include <cstdlib>

void P(sem_t* s);
void V(sem_t* s);

struct Sbuf_t {
    int* buf;
    int n;
    int front;
    int rear;
    sem_t mutex;  // protects accesses to buf
    sem_t slots;  // counts available slots
    sem_t items;  // counts available items
};

void sbuf_init(Sbuf_t* sp, int n);
void sbuf_deinit(Sbuf_t* sp);
void sbuf_insert(Sbuf_t* sp, int item);
int sbuf_remove(Sbuf_t* sp);

#endif