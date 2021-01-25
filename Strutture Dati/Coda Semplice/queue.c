#include "queue.h"

//versione vettore con riferimenti a testa e coda
static Item *coda;
static int N, head, tail;

//una coda anche detta FIFO, si inserisce in coda e si estrae sempre dalla testa, quando realizziamo con vettore facciamo finta che la testa sia alla fine
void QueueInit(int maxn) {
    coda = malloc(sizeof(Item));
    //sumero elementi sopra-allocato
    N=maxn-1;
    head=N;
    tail=0;
}

void QueuePut(Item val) {
    
}
