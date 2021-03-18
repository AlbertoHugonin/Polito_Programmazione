typedef struct item_ *Item;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Item ItemInit();
Item ItemScan(FILE *ptr);

int ItemCompare(Item item1, Item item2);

void ItemShow(Item item, FILE *ptr);

//ritorna chiave dell'elemento (in questo caso coincide con il value)
int Keyget(Item item);