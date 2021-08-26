#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main() {

    FILE *input = fopen("grafo.txt", "r");
    graph grafo = graphinit();
    grafo = GRAPHload(grafo,input);
    return 0;
}