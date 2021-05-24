#include "queue.h"

//versione vettore con riferimenti a testa e coda
static Item *coda;

//i riferimenti sono degli indici
static int N, head, tail;

//una coda anche detta FIFO, si inserisce in coda e si estrae sempre dalla testa, quando realizziamo con vettore facciamo finta che la testa sia alla fine
//è un buffr circolare per poter garantire inserimento O(1) perchè se no dovremmo muovere tutte le volte il vettore

void QueueInit(int maxn) {
    coda = malloc(sizeof(Item));
    //sumero elementi sopra-allocato
    N=maxn-1;
    head=N;
    tail=0;
}

void QueuePut(Item val) {
    //prima piazzi poi incrementi tail
    coda[tail++] = val;
    tail=tail%N;
}

Item QueueGet() {
    head=head%N;
    return coda[head++];
}

int QueueEmpty() {
    return head%N == tail;
}
