#include <stdio.h>

typedef struct grafo_ *graph;


graph graphinit();
//da file di archi
graph GRAPHload(graph grafo, FILE *file);