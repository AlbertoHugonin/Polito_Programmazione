#include "item.h"

struct item_ {
    int n;
};


Item itemInit() {
    Item cache = malloc(sizeof(Item));
    return cache;
}
//item scan di tutto il file
Item itemScan(FILE *ptr) {
    Item elem = itemInit();
    fscanf(ptr,"%d", &elem->n);
    return elem;
}

int itemCompare(Item item1, Item item2) {
    return item1->n - item2->n;
}