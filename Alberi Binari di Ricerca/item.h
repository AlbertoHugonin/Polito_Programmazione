typedef struct item_ *Item, *Key;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Item ItemInit();
Item ItemScan(FILE *ptr);

int ItemCompare(Item item1, Item item2);
int KeyCompare(Key key1, Key key2);

void ItemShow(Item item, FILE *ptr);

//ritorna chiave dell'elemento (in questo caso coincide con il value)
Key Keyget(Item item);