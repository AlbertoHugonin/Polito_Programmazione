#include "item.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct item_ {
    Key key;
    char val;
};

Item ItemInit() {
    Item cache = malloc(sizeof(Item));
    return cache;
}
//item scan di tutto il file
Item ItemScan(FILE *ptr, Key key) {
    Item elem = ItemInit();
    if (ptr == stdin) {
        printf("Inserisci un Char:");
    }
    //controllo di errore se il file è vuoto o finito
    if (fscanf(ptr," %c", &elem->val) == EOF) {
        return NULL;
    }
    fflush(stdin);
    elem->key = key;
    return elem;
}

char GetValue(Item item) {
    return item->val;
}

int ItemCompare(Item item1, Item item2) {
    return item1->val - item2->val;
}

int KeyCompare(Key key1, Key key2) {
    return (int) *key1 - (int) *key2;
}

void ItemShow(Item item, FILE *ptr) {
    fprintf(ptr,"%c ", item->val);
}

Key Keyget(Item item) {
    return item->key;
}

void ItemFree(Item item) {
    free(item);
}

Key KeyScan(int k) {
    Key chiave = malloc(sizeof(Key));
    *chiave=k;
    return chiave;
}