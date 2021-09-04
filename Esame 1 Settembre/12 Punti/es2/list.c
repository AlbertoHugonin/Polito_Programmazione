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

LIST listacreate(int a, int b) {

    LIST list = malloc(sizeof(struct lista_ *));
    list->testa = malloc(sizeof(struct nodo_ *));
    list->testa->k = a;
    list->testa->prev=NULL;
    link corrente = list->testa;
    for (a; a<b; a++) {
        corrente->next = malloc(sizeof(struct nodo_ *));
        corrente->next->k = a+1;
        corrente->next->prev=corrente;
        corrente=corrente->next;
    }
    corrente->next=NULL;
    list->coda=corrente;
    return list;
}

void StampaLista(LIST lista) {
    if (lista->testa==NULL) {
        return;
    }
    link corrente = lista->testa;
    while (corrente != NULL) {
        printf("%d", corrente->k);
        if (corrente->next!=NULL) {
            printf("->");
        }
        corrente=corrente->next;
    }
    puts("");
    fflush(stdout);
    return;
}

void purge(LIST l, int div) {

    if (l->testa == NULL) { return; }
    link corrente = l->testa;
    //se la divisione per div ritorna del resto allora cancelliamo il nodo testa
    if ((l->testa->k)%div != 0) {

        if (l->testa->next == NULL) {
            free(l->testa);
            l->testa=NULL;
            l->coda=NULL;
            return;
        }

        l->testa->next->prev = NULL;
        l->testa = corrente->next;

        if (corrente == l->coda) {
            l->coda = l->testa;
        }
        free(corrente);
    }
    corrente = l->testa;

    if (l->testa->next != NULL) {
        corrente = l->testa->next;
    } 
    
    while (corrente->next != NULL) {

        link back = corrente;
        if (corrente->k%div != 0) {
            //possiamo essere per forza al centro della lista, l'ultimo elemento non viene mai preso in considerazione dal ciclo
            corrente->next->prev = corrente->prev;
            corrente->prev->next = corrente->next;
            corrente = back->next;
            free(back);
            continue;
        }
        corrente = back->next;

    }
    if (corrente->k%div == 0) {
        return;
    }

    //il ciclo esce all'ultimo elemento che dobbiamo cancellarlo a parte
    corrente->prev->next=NULL;
    l->coda=corrente->prev;
    free(corrente);
    return;
}