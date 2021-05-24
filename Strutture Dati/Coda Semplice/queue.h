#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef ITEM
#include "item.h"
#else
#include "../../Struttura Grafo/arco.h"
typedef struct Arco_ *Item;
#endif
//variante senza variabile globale quindi non posso creare tipi di dato, si classifica come Quasi - ADT

void QueueInit(int maxn);

void QueuePut(Item val);

Item QueueGet();

int QueueEmpty();

void QueueFill(FILE *ptr);