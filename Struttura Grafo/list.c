#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Nodo_l_ {

    Arco arco;

    Nodo_l next;
};

struct Lista_ {

    Nodo_l testa;
    Nodo_l coda;
    //numero di adiacenze del nodo
    int NA;

};

static Nodo_l InsertR (Nodo_l corrente, Arco arco);

Lista ListaInit(Lista lista) {

    lista = malloc(sizeof(Lista));
    lista->NA=0;
    lista->testa = NULL;
    lista->coda = NULL;
    return lista;
}

Arco GetArco(Lista lista, int n) {
    //nel caso che n non sia valido o la lista sia vuota
    if (lista->NA < n || lista->NA == 0) {
        return NULL;
    }
    Nodo_l corrente = lista->testa;
    for (int a=1; a<=n; a++) {
        corrente = corrente->next;
        //da sistemare
        if (corrente == NULL) {
            return NULL;
        }
    }
    return corrente->arco;
}


Nodo_l NodoInit(Arco arco) {

    Nodo_l nodo = malloc(sizeof(Nodo_l));

    nodo->arco = arco;
    nodo->next=NULL;

    return nodo;
}

//funzione piu' generale possibile
Lista InsertL( Lista lista, Arco arco) {
    lista->testa = InsertR(lista->testa,arco);
    lista->NA++;
    return lista;
}

static Nodo_l InsertR (Nodo_l corrente, Arco arco) {
    //caso terminale
    if (corrente == NULL) {
        return NodoInit(arco);
    }
    corrente->next = InsertR(corrente->next,arco);
    return corrente;
}

void PrintList(Lista lista) {
Nodo_l corrente = lista->testa;
for (int b=0; b<lista->NA; b++) {
    printf(" -> ");
    PrintArco(corrente->arco);
        corrente=corrente->next;
            if(corrente==NULL) {
                break;
        }
    }
}