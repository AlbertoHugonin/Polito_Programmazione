/*
1- typedef struct Nodo_ .... Nodo
2- definire la lista come puntatore al primo nodo Nodo *lista;
3- passare l'indirizzo della lista alla funzione crea lista e aggiungi elemento &lista
4- definire tutte le funzioni con il doppio puntatore **lista
5- se si devono fare modifiche al primo elemento HEAD modificare il contenuto della variabile lista (*lista) con l'indirizzo della variabile nuovo_nodo
6- PROFIT, senza uso di return,strutture wrapper e altre shenanigans, è necessario di tenere conto di altre variabili nel main
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo_ {

   int id;
   char *Nome;

   struct Nodo_ *next;
   struct Nodo_ *last;

} Nodo;


int inserimento_ordinato_id(Nodo **lista, int num_elementi, int id, char *Nome);
void stampa_lista(Nodo **lista, int num_elementi);


int main() {

    Nodo *lista;    //creiamo una lista vuota con un nodo allocato, server pe far funzionare la mancanza di un puntatore testa con wrapper
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
        num_elementi = inserimento_ordinato_id(&lista,num_elementi,id,Nome); //inserisci gli elementi nella lista e ritorna per comodità il numero di elementi
        puts("\n");
    }

    //stampiamo la lista
    stampa_lista(&lista,num_elementi);
    
    return 0;
}

//ordinamento è piu' complicato rispetto all'uso di una struttura wrapper
int inserimento_ordinato_id(Nodo **lista, int num_elementi, int id, char *Nome) {

    Nodo *nuovo_nodo = malloc(sizeof(Nodo));
    nuovo_nodo->id=id;
    nuovo_nodo->Nome=strdup(Nome);

    if (num_elementi == 0) {
        nuovo_nodo->next=NULL;
        //modifico il contenuto della variabile lista con l'indirizzo della variabile nuovo_nodo
        *lista = nuovo_nodo;
        return num_elementi+1;
    }

    Nodo *elemento_corrente = *lista;
    Nodo *elemento_precedente = NULL;

    int a = 0;

    for (a=0; a<num_elementi; a++) {
        if (id < elemento_corrente->id) {
            break;
        }
        elemento_precedente = elemento_corrente;
        elemento_corrente = elemento_corrente->next;
    }

    if ( elemento_corrente==NULL) {
        //in questo caso sarebbe l'ultimo elemento
        elemento_precedente->next=nuovo_nodo;
    }
    else {
        //in questo caso sarebbe il penultimo elemento
        if (elemento_precedente==NULL) {
            nuovo_nodo->next=elemento_corrente;
            //modifico il contenuto della variabile lista con l'indirizzo della variabile nuovo_nodo
            *lista=nuovo_nodo;
            return num_elementi+1;
        }
        elemento_precedente->next = nuovo_nodo;
        nuovo_nodo->next=elemento_corrente;

    }
    return num_elementi+=1;
}

void stampa_lista(Nodo **lista, int num_elementi) {

    Nodo *elemento_corrente = *lista;
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