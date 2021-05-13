#include "arco.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Arco_ {

    //source
    int S;
    //destination
    int D;
    //peso del link utile per le reti, 
    int P;

};

Arco ArcoInit(int S, int D, int P) {

    Arco arco = malloc(sizeof(Arco));

    arco->D=D;
    arco->S=S;
    arco->P=P;

    return arco;
}

void PrintArco(Arco arco) {
    printf("%d (%d)", arco->D, arco->P);
}

int GetSource(Arco arco) {
    return arco->S;
}

int isDummy(Arco arco) {
    return arco->S - arco->D;
}

int GetDestination(Arco arco) {
    return arco->D;
}