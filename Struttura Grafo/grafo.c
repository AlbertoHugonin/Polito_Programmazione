#include "grafo.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void dfsR(Grafo grafo, Arco arco, int *tempo, int *pre);

struct Grafo_ {
    //numero nodi grafo
    int N;
    //numero archi grafo;
    int C;
    //lista di adiacenza con vettore di liste cosi da avere accesso diretto, visto che sappiamo il numero di nodi
    Lista *vettore_di_liste;
    //tabella che contiene la corrispondenza nodo intero
    BST tabella_di_simboli;
};


void GRAPHdfs(Grafo grafo) {
    int *pre, *tempo;
    pre = malloc(grafo->N*sizeof(int));
    tempo = malloc(sizeof(int));
    *tempo = 0;

    for (int a=0; a<grafo->N; a++) {
        pre[a] = -1;
    }

    Lista corrente = grafo->vettore_di_liste[0];
    Arco arco = GetArco(corrente,0);
    dfsR(grafo,ArcoInit(GetSource(arco),GetSource(arco),0),tempo,pre);
}

void dfsR(Grafo grafo, Arco arco, int *tempo, int *pre) {

}



Grafo GRAPHinit(int N) {
    Grafo grafo = malloc(sizeof(grafo));
    grafo->N=N;
    grafo->C=0;
    grafo->vettore_di_liste=malloc(N*sizeof(Lista));
    //numero di adiacenze iniziali
    for (int a=0; a<N; a++) {
        grafo->vettore_di_liste[a] = ListaInit(grafo->vettore_di_liste[a]);
    }
    return grafo;
}

Grafo GRAPHload(FILE *file) {
    
    int N;
    fscanf(file,"%d",&N);
    Grafo grafo = GRAPHinit(N);
    Item item;
    grafo->tabella_di_simboli = BstInit();
    puts("Lettura Vertici:\n");
    //inserimento nella tabella di simboli
    for (int a=0; a<N; a++) {
        item = ItemScan(file,KeyScan(a));
        //inserimento con chiave crescente, la tabella di simboli diventa una lista tutta sulla destra bisogna bilanciarla
        BSTInsertR(grafo->tabella_di_simboli,item);
        printf("%d\n", a);
    }
    
    //trovare la chiave dell'elemento da inserire
    Arco arco;
    //sorgente destinazione dell'arco;
    int S,D;
    int peso;
    puts("\nLettura Archi:\n");
    while (1) {
        //cerchiamo un item per valore con chiave fittizia
        item = ItemScan(file,KeyScan(0));
        //uscita strutturata se siamo arrivati alla fine del file
        if (item == NULL) {
            break;
        }
        S = *BSTSearchKey(grafo->tabella_di_simboli,item);
        item = ItemScan(file,KeyScan(0));
        D = *BSTSearchKey(grafo->tabella_di_simboli,item);
        fscanf(file,"%d", &peso);
        //trovata la chiave vado a prenderla nell'vettore delle liste di adiacenza
        printf("%d, %d e peso:%d\n", S, D, peso);
        arco = ArcoInit(S,D,peso);
        //da vedere
        InsertL(grafo->vettore_di_liste[S], arco);
        grafo->C++;
    }


    return grafo;

}




void PrintAdj(Grafo grafo) {
    puts("\nStampa Lista Adiacenze:\n");
    Nodo_l corrente;


    for (int a=0; a<grafo->N; a++) {
        printf("%d", a);
        PrintList(grafo->vettore_di_liste[a]);
        puts("");
    }
}