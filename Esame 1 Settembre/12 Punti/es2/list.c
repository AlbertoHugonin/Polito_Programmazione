//LIST.c
//scrivere qui il codice
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct nodo_ *link;

struct nodo_ {
    int k;
    link next;
    link prev;
    };
    
struct lista_ {
    //puntatori
    link testa;
    link coda;
};

LIST listacreate() {

    LIST list = malloc(sizeof(struct lista_ *));
    list->testa = malloc(sizeof(struct nodo_ *));
    list->testa->k = 1;
    list->testa->prev=NULL;
    link corrente = list->testa;
    for (int a=2; a<5; a++) {
        corrente->next = malloc(sizeof(struct nodo_ *));
        corrente->next->k = a;
        corrente->next->prev=corrente;
        corrente=corrente->next;
    }
    corrente->next=NULL;
    list->coda=corrente;
    return list;
}

void purge(LIST l, int div) {
    
    //inizialmente pensavo di aggiungere un intero per tenere conto degli elementi poi ho scartato
    //l'idea quindi devo mettere l->testa ==

    if (l->testa == NULL) { return; }
    link corrente = l->testa;
    //se la divisione per div ritorna del resto allora cancelliamo il nodo testa
    if (l->testa->k%div != 0) {
        l->testa->next->prev = NULL;
        l->testa = corrente->next;
        if (corrente == l->coda) {
            l->coda = l->testa;
        }
    free(corrente);
    }
    corrente = l->testa;
    while (corrente->next != NULL) {
        corrente = corrente->next;
        link back = corrente;
        if (corrente->k%div != 0) {
            //possiamo essere per forza al centro della lista, l'ultimo elemento non viene m
            //ai preso in considerazione dal ciclo
            corrente->next->prev = corrente->prev;
            corrente->prev->next = corrente->next;
            corrente = back->next;
            free(back);
        }
    }
    if (corrente->k%div == 0) {
        return;
    }

    //il ciclo esce all'ultimo elemento che dobbiamo cancellarlo a parte
    free(corrente->next);
    corrente->next = NULL;
    l->coda = corrente;
    return;
}