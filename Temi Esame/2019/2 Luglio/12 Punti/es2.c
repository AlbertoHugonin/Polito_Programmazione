#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_ *lista;
typedef struct nodo_ *nodo;

struct lista_ {
    nodo Head;
    int n;
};

struct nodo_ {
    char campo;
    nodo Next;
};

nodo NodoInit(char c);
lista ListaInit();
lista InsertNodo(lista list,nodo elemento);
void PrintList(lista list);
void linkpurgeList(nodo testa);
void FreeNodo(nodo elemento);


int main() {

    lista list = ListaInit();
    InsertNodo(list,NodoInit('a'));
    InsertNodo(list,NodoInit('b'));
    InsertNodo(list,NodoInit('('));
    InsertNodo(list,NodoInit('a'));
    InsertNodo(list,NodoInit('c'));
    InsertNodo(list,NodoInit('g'));
    InsertNodo(list,NodoInit(')'));
    InsertNodo(list,NodoInit('b'));
    InsertNodo(list,NodoInit('e'));
    InsertNodo(list,NodoInit('('));
    InsertNodo(list,NodoInit(')'));
    InsertNodo(list,NodoInit('a'));
    InsertNodo(list,NodoInit('('));
    InsertNodo(list,NodoInit('x'));
    InsertNodo(list,NodoInit('x'));
    InsertNodo(list,NodoInit(')'));
    InsertNodo(list,NodoInit('f'));

    PrintList(list);
    puts("");
    linkpurgeList(list->Head);
    PrintList(list);
    return 0;

}

void linkpurgeList(nodo testa) {
    nodo corrente = testa;
    while (corrente != NULL) {
        if (corrente->campo == '(') {
            nodo partenza = corrente;
            while(corrente->campo != ')') {
                corrente=corrente->Next;
            }
            //adesso il nodo corrente rappresenta la fine
            //creiamo il nuovo nodo asterisco e lo colleghiamo al next del nodo partenza
            nodo nuovo = NodoInit('*');
            partenza->Next=nuovo;
            nuovo->Next=corrente;
        }
        corrente = corrente->Next;
    }
}

void FreeNodo(nodo elemento) {
    free(elemento);
    return;
}


void PrintList(lista list) {
    nodo corrente = list->Head;
    while (corrente != NULL) {
        printf("%c ", corrente->campo);
        corrente=corrente->Next;
    }
}


lista InsertNodo(lista list,nodo elemento) {

    //test di lista vuota valido se non voglio usare nodo sentinella

    if (list->Head == NULL) {
        list->Head=elemento;
        list->n++;
        return list;
    }

    nodo corrente = list->Head;
    while (corrente->Next != NULL) {
        corrente = corrente->Next;
    }
    corrente->Next=elemento;
    list->n++;
    return list;
}

nodo NodoInit(char c) {
    nodo corrente = malloc(sizeof(struct nodo_));
    corrente->campo=c;
    corrente->Next=NULL;
    return corrente;
}

lista ListaInit() {
    lista List = malloc(sizeof(struct lista_));
    List->Head = NULL;
    List->n=0;
}



