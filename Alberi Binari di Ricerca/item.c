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
    printf("Inserisci un Numero:");
    fscanf(ptr,"%d", &elem->n);
    return elem;
}

int ItemCompare(Item item1, Item item2) {
    return item1->n - item2->n;
}

int KeyCompare(Key key1, Key key2) {
    return key1->n - key2->n;
}

void ItemShow(Item item, FILE *ptr) {
    fprintf(ptr,"%d ", item->n);
}

Key Keyget(Item item) {
    return item;
}

void ItemFree(Item item) {
    free(item);
}