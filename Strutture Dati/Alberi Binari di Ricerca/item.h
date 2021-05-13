typedef struct item_ *Item;
typedef int *Key;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Item ItemInit();
Item ItemScan(FILE *ptr, Key key);

int ItemCompare(Item item1, Item item2);
int KeyCompare(Key key1, Key key2);

void ItemShow(Item item, FILE *ptr);

//ritorna chiave dell'elemento (in questo caso coincide con il value)
Key Keyget(Item item);

void ItemFree(Item item);

//ritorna la chiave a partire da un intero
Key KeyScan(int k);

char GetValue(Item item);