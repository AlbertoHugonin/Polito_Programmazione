#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tabella_simboli_ *tabella_simboli;

/////////////ADT Tabella di Simboli
struct tabella_simboli_ {
    char **tabella;
    int N;
};

tabella_simboli simboltableinit() {
    
}


struct grafo_ {
    //matrice delle adiacenze
    int **adj;
    char **tabella_simboli;
    int N_nodi;
    int N_archi;
};

graph graphinit() {
    graph grafo = malloc(sizeof(struct grafo_ *));
    //per adesso non allochiamo la matrice delle adiacenze
    return grafo;
}

graph GRAPHload(graph grafo, FILE *file) {

    FILE *inizio = file;

    ///////////inizializzazione nodi nella tabella di simboli
    int N = 1;
    grafo->tabella_simboli = malloc((N)*sizeof(char));
    for (int a=0; a<N; a++) {
        grafo->tabella_simboli[a] = malloc(20*sizeof(char));
    }

    char nodo;
    int find_nodo = 0;

    while(fscanf(file,"%s ", &nodo) != EOF) {

        find_nodo = 0;
        //grafo->tabella_simboli[N-1]
        for (int n=0; n<N; n++) {
            // if (grafo->tabella_simboli[n] == nodo) {
            //     find_nodo=1;
            // }
        }
        if (find_nodo == 0) {
            // grafo->tabella_simboli[N-1] = nodo;
            N++;
            grafo->N_nodi++;
            //alla fine c'è ne uno in piu'
            void *c = realloc(grafo->tabella_simboli, N*sizeof(char));
        }
    }
    //////////////// allochiamo per eccesso la matrice
    file = inizio;
    grafo->adj = malloc(grafo->N_nodi*sizeof(int)); //numero righe tabella
    for (int a=0; a<grafo->N_nodi; a++) {
        grafo->adj[a] = malloc(grafo->N_nodi*sizeof(int));
    }
    //////////////////
    rewind(file);
    char nodo2;

    while(fscanf(file,"%c %c ", &nodo, &nodo2) != EOF) {
        //cercare intero dentro tabella di simboli //1 ora e 10

        grafo->adj[nodo][nodo2] = 1;
    }
    //stampiamo matrice adj
    for (int a=0; a<grafo->N_nodi; a++) {
        for (int b=0; b<grafo->N_nodi; b++) {
            printf("%d ", grafo->adj[a][b]);
        }
        puts("");
    }
    return grafo;
}