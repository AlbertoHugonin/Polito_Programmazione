#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo_ {

   int id;
   char *Nome;

   struct Nodo_ *next;
   struct Nodo_ *last;

} Nodo;


int inserimento_in_coda(Nodo *lista, int num_elementi, int id, char *Nome);
int inserimento_ordinato_id(Nodo *lista, int num_elementi, int id, char *Nome);
void stampa_lista(Nodo *lista, int num_elementi);


int main() {

    Nodo *lista = malloc(sizeof(Nodo));    //creiamo una lista vuota con un nodo allocato, server pe far funzionare la mancanza di un puntatore testa con wrapper
    int id;
    char Nome[10];

    //esempio di inseritmento_in_coda
    int num_elementi = 0;
    
    printf("Inserisci ID e il Nome, quando vuoi terminare scrivi id e Nome (0)\n");

    while (1) {
        puts("ID:");
        scanf("%d", &id);
        if (id == 0) {
            break;
        }
        puts("Nome:");
        scanf("%s", Nome); 
        num_elementi = inserimento_ordinato_id(lista,num_elementi,id,Nome); //inserisci gli elementi nella lista e ritorna per comodità il numero di elementi
        puts("\n");
    }

    //stampiamo la lista
    stampa_lista(lista,num_elementi);
    
    return 0;
}

void stampa_lista(Nodo *lista, int num_elementi) {

    Nodo *elemento_corrente = lista;
    puts("\n");
    
    if (num_elementi == 0) {
        puts("Lista Vuota\n");
    }

    for (int a=0; a<num_elementi; a++) {
        printf("ID: %d - Nome: %s\n", elemento_corrente->id, elemento_corrente->Nome);
        elemento_corrente=elemento_corrente->next;
    }
    puts("\n");
}


int inserimento_in_coda(Nodo *lista, int num_elementi, int id, char *Nome) {

    Nodo *elemento_corrente = lista;
    Nodo *elemento_precedente = NULL;

    for (int a=0; a<num_elementi; a++) {
        elemento_precedente = elemento_corrente;
        elemento_corrente = elemento_corrente->next;
    }

        elemento_corrente->id = id;
        elemento_corrente->Nome = strdup(Nome);

        if (elemento_precedente != NULL) {
            elemento_corrente->last=elemento_precedente;
            elemento_precedente->next=elemento_corrente;
        }

        //allochiamo già il nodo successivo
        elemento_corrente->next = malloc(sizeof(Nodo));

    return num_elementi+=1;
}
//ordinamento è piu' complicato rispetto all'uso di una struttura wrapper
int inserimento_ordinato_id(Nodo *lista, int num_elementi, int id, char *Nome) {

    
    Nodo *elemento_corrente = lista;
    Nodo *elemento_precedente = NULL;

    int a = 0;

    for (a=0; a<num_elementi; a++) {
        if (id < elemento_corrente->id) {
            break;
        }
        elemento_precedente = elemento_corrente;
        elemento_corrente = elemento_corrente->next;
    }

    if ( a == num_elementi || a == 0) {
        inserimento_in_coda(lista,num_elementi,id,Nome);
    }
    else {

        //inserimento in mezzo
        elemento_precedente->next=NULL;
        elemento_precedente->next=malloc(sizeof(Nodo));

        elemento_precedente->next->id=id;
        elemento_precedente->next->Nome=strdup(Nome);
        elemento_precedente->next->next=elemento_corrente;
        //non funziona quando ci sono due nodi

    }
    return num_elementi+=1;
}