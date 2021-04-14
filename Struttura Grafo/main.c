#include "grafo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    FILE *file = fopen("grafo.txt","r");

    Grafo grafo = GRAPHload(file);
    PrintAdj(grafo);

    return 0;

}