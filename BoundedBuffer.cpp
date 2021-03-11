#include "BoundedBuffer.h"

void P(sem_t* s) { sem_wait(s); }
void V(sem_t* s) { sem_post(s); }

void sbuf_init(Sbuf_t* sp, int n) {
    sp->buf = (int*)calloc(n, sizeof(int));
    sp->n = n;
    sp->front = sp->rear = 0;
    sem_init(&sp->mutex, 0, 1);
    sem_init(&sp->slots, 0, n);
    sem_init(&sp->items, 0, 0);
}

void sbuf_deinit(Sbuf_t* sp) { free(sp->buf); }

void sbuf_insert(Sbuf_t* sp, int item) {
    P(&sp->slots);
    P(&sp->mutex);
    sp->buf[(++sp->rear) % (sp->n)] = item;
    V(&sp->mutex);
    V(&sp->items);
}

int sbuf_remove(Sbuf_t* sp) {
    int item;
    P(&sp->items);
    P(&sp->mutex);
    item = sp->buf[(++sp->front) % (sp->n)];
    V(&sp->mutex);
    V(&sp->slots);
    return item;
}