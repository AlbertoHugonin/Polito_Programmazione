typedef struct item_ *Item;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Item itemInit();
Item itemScan(FILE *ptr);
//item1 > item2 = return > 0
int itemCompare(Item item1, Item item2);