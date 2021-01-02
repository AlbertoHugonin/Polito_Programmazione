#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "set.h"

//Versione con SET ADT 1 Classe struct definita qui

struct set_ {
    Item *V;
    int N;
};


SET SetInit(int MAX_N) {

    SET cache = malloc(sizeof(* cache));
    cache->N=0;
    cache->V = calloc(MAX_N,MAX_N * sizeof(Item));
    return cache;
}

void SetFill(SET s, Item Val) {
    s->V[s->N] = Val;
    s->N++;
}

SET SetUnion(SET s1, SET s2) {

    SET s = SetInit(s1->N+s2->N);

    //k indice vett risultato, i indice vett s1, j indice vett s2
    int k = 0, i = 0, j = 0;

    // [i++] significa che prima usa il valore di i poi lo incrementa
    for (k=0; (i < s1->N) || (j <s2->N); k++) {
        if ( i >= s1->N) s->V[k] = s2->V[j++];
        else if ( j >= s2->N) s->V[k] = s1->V[i++];
        //se s2 è minore di s1 prendi s2
        else if (itemCompare(s1->V[i], s2->V[j]) < 0) s->V[k] = s2->V[j++];
        //se s1 è minore di s2 prendi s1
        else if (itemCompare(s1->V[i], s2->V[j]) > 0) s->V[k] = s1->V[i++];
        //se sono uguali prendi uno dei due, dobbiamo aumentare si i che j
        else { s->V[k] = s1->V[i++]; j++; }
        s->N = k;
    }
    return s;
}
//salva su file
void SetSave(SET s, FILE *ptr) {
    fprintf(ptr,"N.Elementi: %d", s->N);
}