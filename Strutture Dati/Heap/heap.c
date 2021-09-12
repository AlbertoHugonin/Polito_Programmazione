#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

static int ReturnL(int i);
static int ReturnPadre(int i);
static int ReturnR(int i);

struct HEAP_ {

    ITEM *vett;
    //dimensione corrente heap
    int heap_size;

};


HEAP HeapInit(int maxN) {

    HEAP heap = malloc(sizeof(*heap));
    heap->heap_size=0;
    heap->vett = malloc(maxN*sizeof(ITEM));
    return heap;

}


ITEM ItemScan() {

    ITEM tmp = {-1};
    tmp.chiave = 100*(1.0 * rand()/RAND_MAX);
    return tmp;

}


void HeapInsert(HEAP heap, ITEM k) {
    
    heap->vett[heap->heap_size++] = k;
    //chiamiamo heapify dopo che l'ho fatta
    Heapify(heap,0);
    return;

}

void Heapify(HEAP heap, int k) {

    int l = ReturnL(k);
    int r = ReturnR(k);

    int max = k;

    //se sinistra esiste controlliamo a sinistra
    if (l<heap->heap_size) {
        if ( KeyCompare(KeyGet(heap->vett[l]) , KeyGet(heap->vett[k]) < 0) ) {
            max = l;
        }
    }
    if (r<heap->heap_size) {
        if (KeyCompare(KeyGet(heap->vett[r]),KeyGet(heap->vett[k]) < 0)) {
            max = r;
        }
    }
    if (max == k) {
        return;
    }
    //facciamo lo scambio e iteriamo
    ITEM tmp;
    tmp = heap->vett[k];
    heap->vett[k] = heap->vett[max];
    heap->vett[max] = tmp;
    Heapify(heap,max);
}

static int ReturnPadre(int i) {
    return (i-1)/2;
}
static int ReturnL(int i) {
    return 2*i+1;
}
static int ReturnR(int i) {
    return 2*i+2;
}

Key KeyGet(ITEM item) {
    return item.chiave;
}

int KeyCompare(Key a, Key b) {
    return b-a;
}