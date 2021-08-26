#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//per comodità definisco tutto qui e faccio attenzione a trattare la lista come adt

typedef struct nodo_ *link;
typedef struct lista_ *lista;

struct nodo_ {
    //per semplicità è una lista di numeri
    int a;
    link next;
};

struct lista_ {
    link testa;
    //num elementi lista
    int n;
};

lista listainit();
lista listaInsert(int a, lista list, int start);
void listfree(lista list); 
//elimina nodo n
link listDelete(lista list, int n);
void splice (lista L1, lista L2, int start, int num);

lista listainit() {
    lista list = malloc(sizeof(struct lista_ *));
    list->n=0;
    list->testa=NULL;
}

//1 se elemento non eliminato, 0 se eliminato correttamente
link listDelete(lista list, int n) {
    link corrente = list->testa;
    link old;
    if(list->testa==NULL || n>list->n) {
        return NULL;
    } else {
        for (int a=1; a<n-1; a++) {
            corrente=corrente->next;
        }
        //cancellazione in testa
        if (corrente==list->testa) {
            list->testa = corrente->next;
            corrente->next= NULL;
            list->n--;
            return corrente;
        }
        //quello successivo è quello da eliminare
        old = corrente->next;
        //bypass del nodo
        corrente->next=old->next;
        list->n--;
        old->next=NULL;
        return old;
    }
}

//se start -1 fa inserimento in testa, se no inserisce in mezzo o alla fine se il numero è maggiore di n
lista listaInsert(int a, lista list, int start) {

    link nuovo = malloc(sizeof(struct nodo_ *));
    nuovo->a=a;
    //inserimento in testa
    if(start <= 0) {
        if (list->testa == NULL) {
            list->testa=nuovo;
        } else {
            nuovo->next=list->testa;
            list->testa=nuovo;
        }
        list->n++;
        return list;
    } else {
        //se stat >= 1
        link corrente = list->testa;
        int pos=1;
        for (pos=1; pos<start && pos<list->n-1; pos++) {
            corrente = corrente->next;
        }
        //verificare se siamo alla fine o in mezzo
        if (corrente->next==NULL) {
            corrente->next=nuovo;
        } else {
            nuovo->next = corrente->next;
            corrente->next=nuovo;
        }
        list->n++;
        return list;
    }

}

void splice (lista L1, lista L2, int start, int num) {
    link corrente;
    for (int a=0; a<num; a++) {
        //estraiamo dalla testa elemento
        corrente = listDelete(L2,0);
        //lo inseriamo a partire da start incrementato di a
        listaInsert(corrente->a,L1,start+a);
        free(corrente);
    }
}

///////////////FINE ADT
  
int main() {

    //entrambe liste da 10 elementi
    lista list1 = listainit();
    for (int a=0; a<10; a++) {
        list1 = listaInsert(a,list1,0);
    }
    lista list2 = listainit();
    for (int a=11; a<20; a++) {
        list2 = listaInsert(a,list2,0);
    }
    splice(list1,list2,0,3);
    return 0;
}

















///////////////////////////