#include "grafo.h"
#include "list.h"
#include "../Strutture Dati/Coda Semplice/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//algoritmo di vista in profondità è ricorsivo
void dfsR(Grafo grafo, Arco arco, int *tempo, int *pre, int *post, int *st);
//algoritmo di vista in ampiezza è iterativo
void bfs(Grafo grafo, Arco arco, int *tempo, int *pre, int *st);

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

    int *pre, *post, *st, *tempo;
    //vettore tempo di scoperta
    pre = malloc(grafo->N*sizeof(int));
    //vettore tempo di fine elaborazione
    post = malloc(grafo->N*sizeof(int));
    //albero vista in profondita, ne basta uno per ciascun grafo, è un nuovo albero se nodo figlio di se stesso
    st = malloc(grafo->N*sizeof(int));
    //allocato dinamicamente perchè lo dobbiamo mantenere aggiornato tra piu' istanze della funzione ricorsiva
    tempo = malloc(sizeof(int));
    *tempo = 0;


    //inizializzazione pre e post
    for (int a=0; a<grafo->N; a++) {
        pre[a] = -1;
        post[a] = -1;
        st[a] = -1;
    }
    //aggiungere il for per ogni vertice TODO
    Lista corrente = grafo->vettore_di_liste[0];
    Arco arco = GetArco(corrente,0);
    //dobbiamo solo controllare che sia bianco quindi non ancora scoperto
    dfsR(grafo,ArcoInit(GetSource(arco),GetSource(arco),0),tempo,pre,post,st);
    //ciclo for
}

void dfsR(Grafo grafo, Arco arco, int *tempo, int *pre, int *post, int *st) {
    //arco utilizzato per definire quelli dopo
    Arco corrente;
    int c=0;

    //arco non dummy
    if (isDummy(arco) != 0) {
        //stampiamo arco dichiarando che è di tipo T perchè non è dummy
        printf("(%c %c): T\n", GetValue(BSTSearch(grafo->tabella_di_simboli,KeyScan(GetSource(arco)))), GetValue(BSTSearch(grafo->tabella_di_simboli,KeyScan(GetDestination(arco)))));
    }
    //nell'albero della visita in profondità scriviamo dentro il nodo che stiamo esaminando il fatto che viene da source quindi da un certo padre
    int D = GetDestination(arco);
    st[D] = GetSource(arco);
    pre[D] = (*tempo)++;
    //ci poniamo sul nodo corrente (source) ed esploriamo tutti i nodi della lista di adiacenza
    while (1) {
        corrente = GetArco(grafo->vettore_di_liste[D],c);
        if (corrente == NULL) {
            //fine lista terminiamo
            break;
        }
        //se arco non ancora visitato
        if (pre[GetDestination(corrente)] == -1) {
            dfsR(grafo,corrente,tempo,pre,post,st);
        }
        else {
            //stampo informazioni per altri tipi di archi
            if (pre[GetSource(arco)] < pre[GetDestination(corrente)]) {
                printf("(%c %c): F\n", GetValue(BSTSearch(grafo->tabella_di_simboli,KeyScan(GetSource(arco)))), GetValue(BSTSearch(grafo->tabella_di_simboli,KeyScan(GetDestination(corrente)))));
            }
        }
        c++;
    }
    post[D] = (*tempo)++;
}

void GRAPHbfs(Grafo grafo) {
    int *pre, *st, *tempo;
    //vettore tempo di scoperta
    pre = malloc(grafo->N*sizeof(int));
    //albero vista in ampiezza, rappresenta tutti i nodi raggiungibili da quello iniziale
    st = malloc(grafo->N*sizeof(int));
    //allocato dinamicamente perchè lo dobbiamo mantenere aggiornato tra piu' istanze della funzione ricorsiva
    tempo = malloc(sizeof(int));
    *tempo = 0;

    //inizializzazione pre e post
    for (int a=0; a<grafo->N; a++) {
        pre[a] = -1;
        st[a] = -1;
    }
    Arco arco = GetArco(grafo->vettore_di_liste[0],0);
    bfs(grafo,ArcoInit(GetSource(arco),GetSource(arco),0),tempo,pre,st);
    //stampiamo l'albero della visita in ampiezza risultante
    // for (int a=0; a<grafo->N; a++) {
    //     printf("%c padre di %c");
    // }
}

//algoritmo iterarivo di vistac in ampiezza
void bfs(Grafo grafo, Arco arco, int *tempo, int *pre, int *st) {
QueueInit(grafo->N);
QueuePut(arco);
//finche la coda non è vuota
while (QueueEmpty() != 0) {
    //vettore pre andiamo a prendere la sorgente dell'arco nella coda
    if (pre[ GetSource(arco = QueueGet())] == -1) {


        pre[GetSource(arco)] = (*tempo)++;
        st[GetSource(arco)] = GetDestination(arco);

        //dobbiamo implementarlo come lista delle adiacenze a differenza di come viene fatto sul libro
        int c=0;
        while (1) {
        arco = GetArco(grafo->vettore_di_liste[GetDestination(arco)],c);
        if (pre[GetDestination(arco)] == -1) {
            QueuePut(ArcoInit(GetSource(arco), GetDestination(arco),1));
        }
        }
    }
}
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

//puo' essere che non ci sia l'elenco di vertici all'inizio
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