#include "../Strutture Dati/Alberi Binari di Ricerca/bst.h"

typedef struct Grafo_ *Grafo;

//inizializza il grado tenendo conto del numero di vertici
Grafo GRAPHinit(int N);
//carica il grafo da un file strutturato
Grafo GRAPHload(FILE *file);
void PrintAdj(Grafo grafo);

//visita in profondità grafo
void GRAPHdfs(Grafo grafo);