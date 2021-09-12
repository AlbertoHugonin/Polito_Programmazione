#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

#include "heap.h"

int main() {

    ITEM *vett = malloc(MAX*sizeof(ITEM));
    HEAP heap = HeapInit(MAX+10);

    for (int a=0; a<MAX; a++) {
        vett[a] = ItemScan();
        HeapInsert(heap,vett[a]);
    }
    return 0;
}
