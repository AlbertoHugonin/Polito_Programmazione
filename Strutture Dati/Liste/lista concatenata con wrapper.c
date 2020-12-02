#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo_ {

   int id;
   char *Nome;

   struct Nodo_ *next;
   struct Nodo_ *last;

} Nodo;

//struttura wrapper
typedef struct Lista_ {
    
    Nodo *testa;
    Nodo *coda;
    int num_elementi;

} Lista;


Lista *inserimento_in_coda(Lista *lista, int id, char *Nome);
Lista *inserimento_in_ordine_crescente (Lista *lista, int id, char *Nome);
void stampa_lista(Lista *lista, int ordine);


int main() {

    Lista *lista = malloc(sizeof(Lista));    //creiamo una lista vuota
    lista->num_elementi=0;
    lista->testa=NULL;
    lista->coda=NULL;

    int id;
    char Nome[10];
    
    printf("Inserisci ID e il Nome, quando vuoi terminare scrivi id e Nome (0)\n");

    while (1) {
        puts("ID:");
        scanf("%d", &id);
        if (id == 0) {
            break;
        }
        puts("Nome:");
        scanf("%s", Nome); 
        lista = inserimento_in_ordine_crescente(lista,id,Nome); //inserisci gli elementi nella lista e ritorna per comodità il numero di elementi
        puts("\n");
    }
    //ordine crescente
    stampa_lista(lista, 1);
    //ordine decrescente
    stampa_lista(lista,-1);
}

void stampa_lista(Lista *lista, int ordine) {

    puts("\n");
    
    if (lista->num_elementi == 0) {
        puts("Lista Vuota\n");
    }

    if (ordine == 1) {

        Nodo *elemento_corrente = lista->testa;
        for (int a=0; a<lista->num_elementi; a++) {
            printf("ID: %d - Nome: %s\n", elemento_corrente->id, elemento_corrente->Nome);
            elemento_corrente=elemento_corrente->next;
        }
        puts("\n");

    }
    else {

        Nodo *elemento_corrente = lista->coda;
        for (int a=0; a<lista->num_elementi; a++) {
            printf("ID: %d - Nome: %s\n", elemento_corrente->id, elemento_corrente->Nome);
            elemento_corrente=elemento_corrente->last;
        }
    puts("\n");

    }
}

//versione inserimento in coda e in mezzo
Lista *inserimento_in_ordine_crescente (Lista *lista, int id, char *Nome) {

    Nodo *nuovo_nodo = malloc(sizeof(Nodo));
    nuovo_nodo->id=id;
    nuovo_nodo->Nome=strdup(Nome);

    Nodo *nodo_corrente = lista->testa;
    Nodo *nodo_precedente = NULL; 

    int a = 0;

    for (a=0; a<lista->num_elementi; a++) {
        if (id < nodo_corrente->id) {
            break;
        }
        nodo_precedente = nodo_corrente;
        nodo_corrente = nodo_corrente->next;
    }

    if (a == lista->num_elementi) {
        lista = inserimento_in_coda(lista,id,Nome);
        return lista;
    }

    //aggiunta in mezzo (primo caso inizio)
    if (a==0) {
        lista->testa=nuovo_nodo;
        nuovo_nodo->last=NULL;
    }
    else {
        nodo_precedente->next=nuovo_nodo;
        nuovo_nodo->last=nodo_precedente;
    }

    nodo_corrente->last=nuovo_nodo;
    nuovo_nodo->next=nodo_corrente;

    lista->num_elementi++;
    return lista;
}

Lista *inserimento_in_coda (Lista *lista, int id, char *Nome) {


    Nodo *nuovo_nodo = malloc(sizeof(Nodo));
    nuovo_nodo->id=id;
    nuovo_nodo->Nome=strdup(Nome);

    Nodo *nodo_corrente = lista->testa;
    Nodo *nodo_precedente = NULL; 

    int a = 0;

    for (a=0; a<lista->num_elementi; a++) {
        nodo_precedente = nodo_corrente;
        nodo_corrente = nodo_corrente->next;
    }

    if (a == 0) {
        lista->testa=nuovo_nodo;
        lista->coda=nuovo_nodo;

    }
    else {
//ricordiamoci sempre che cosi'facendo va avanti di uno di troppo cosi che nodo_corrente è uguale a null quindi bisogna prima fare nodo_corrente=nuovo_nodo
        nodo_corrente=nuovo_nodo;
        nodo_precedente->next=nodo_corrente;
        nodo_corrente->last=nodo_precedente;
        lista->coda=nodo_corrente;
    }
    lista->num_elementi++;
    return lista;
}