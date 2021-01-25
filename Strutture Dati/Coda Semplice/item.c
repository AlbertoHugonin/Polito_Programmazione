#include "item.h"

struct item_ {
    int n;
};

Item ItemInit() {
    Item cache = malloc(sizeof(Item));
    return cache;
}
//item scan di tutto il file
Item ItemScan(FILE *ptr) {
    Item elem = ItemInit();
    fscanf(ptr,"%d", &elem->n);
    return elem;
}

int ItemCompare(Item item1, Item item2) {
    return item1->n - item2->n;
}

void ItemShow(Item item, FILE *ptr) {
    fprintf(ptr,"%d ", item->n);
}

int Keyget(Item item) {
    return item->n;
}