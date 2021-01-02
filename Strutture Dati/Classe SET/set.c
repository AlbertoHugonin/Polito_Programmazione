#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "set.h"


//funzioni interne
int Min(int N1, int N2);
void quick_sort(Item v[], int l, int r);
int partition(Item v[], int l, int r);
void swap(Item v[], int l, int r);

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

//inserimento non ordinato
void SetInsert(SET s, Item Val) {
    s->V[s->N] = Val;
    s->N++;
}

void SetFill(SET s, FILE *ptr) {

    int n;

    fscanf(ptr, "%d", &n);

    Item elemento;

    for (int a=0; a<n; a++) {
        elemento = ItemScan(ptr);
        SetInsert(s,elemento);
    }

    SetQuickSort(s);
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
        else if (ItemCompare(s1->V[i], s2->V[j]) < 0) s->V[k] = s2->V[j++];
        //se s1 è minore di s2 prendi s1
        else if (ItemCompare(s1->V[i], s2->V[j]) > 0) s->V[k] = s1->V[i++];
        //se sono uguali prendi uno dei due, dobbiamo aumentare si i che j
        else { s->V[k] = s1->V[i++]; j++; }
    }
    s->N = k;

    SetQuickSort(s);
    return s;
}

SET SetInter(SET s1, SET s2) {

    int min = Min(s1->N,s2->N);
    SET s = SetInit(min);
    int i = 0, j = 0, k = 0;

    //ci fermiamo quando uno dei due è finito
    while ( (i<s1->N) && (j<s2->N) ) {
        //se sono uguali prendiamo uno dei due e incrementiamo entrambi gli indici
        if (ItemCompare( s1->V[i], s2->V[j] ) == 0) {
            s->V[k++] = s1->V[i++];
            j++;
        }
        //se v[i] < v[j] allora non prendiamo nulla e incrementiamo i
        else if (ItemCompare( s1->V[i], s2->V[j] ) < 0) i++;
        else j++;
    }
    s->N = k;

    SetQuickSort(s);
    return s;
}

void SetSave(SET s, FILE *ptr) {
    fprintf(ptr,"N.Elementi: %d", s->N);
    fprintf(ptr,"\nElementi insieme: ");
    for (int a=0; a<s->N; a++) {
        ItemShow(s->V[a],ptr);
    }
    fprintf(ptr,"\n");
}

void SetQuickSort(SET s) {
    quick_sort(s->V,0,s->N-1);
}

//////////////////////////////////////

int Min(int N1, int N2) {
    if (N1 > N2) return N2;
    else {return N1;}
}

void quick_sort(Item v[], int l, int r) {
    
    if (r<=l) {
        //condizione di terminazione, 1 elemento o 0 elementi è un vettore ordinato
        return;
    }
    //dato il vettore v e i suoi estremi viene partizionato in due parti di dimensioni diverse, con q elemento pivot di mezzo, la scelta del pivot non cambia il caso medio, ma cambia il possibile caso peggiore
    int q = partition(v,l,r);
    //chiamata funzione ricorsiva per ciascuna parte del vettore
    quick_sort(v,l,q-1);
    quick_sort(v,q+1, r);
}

//centro dell'algoritmo
int partition(Item v[], int l, int r) {

    //facciamo prima incrementi poi leggiamo quindi i è valido
    int i = l-1;
    int j = r;
    Item x = v[r];
    //ciclo infinito
    for (; ;) {
        //ciclo che sale che trova il primo elemento maggiore di x
        while(ItemCompare(v[++i],x) < 0);
        //ciclo che scende che trova il primo elemento minore di x
        while(ItemCompare(v[--j],x) > 0) {
            //identifichiamo quindi una coppia di elementi fuori posto che deve essere scambiata
            if ( j == l)
                //significa che abbiamo iterato su tutti gli elementi dei sottovettori
                break;
        }
        if ( i >= j)
            //se i scavalca j allora esco
            break;
        //adesso scambio gli elementi
        swap(v,i,j);
    }
    swap(v,i,r);
    return i;
}

void swap(Item v[], int l, int r) {
    Item x = v[l];
    v[l] = v[r];
    v[r] = x;
    return;
}