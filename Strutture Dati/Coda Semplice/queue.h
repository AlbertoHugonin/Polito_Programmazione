#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

//variante senza variabile globale quindi non posso creare tipi di dato Quasi - ADT

void QueueInit(int maxn);

void QueuePut(Item val);
Item QueueGet();
void QueueFill(FILE *ptr);