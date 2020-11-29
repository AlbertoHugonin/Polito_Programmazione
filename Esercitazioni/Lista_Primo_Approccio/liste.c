#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 30


struct riga {
    char *stringa;
    struct riga *next;
};

typedef struct database_stringhe_ {
    struct riga *testa;
    int num;
} database_stringhe;


int inserisci_in_lista (database_stringhe *cache, char *elemento);
database_stringhe *carica_lista();


int main() {


    database_stringhe *lista = carica_lista();


    return 0;
}



database_stringhe *carica_lista() {

    FILE *ptr = fopen("lista_stringhe", "r");

    char *elemento = malloc(MAX_N * sizeof(char));
    database_stringhe *cache = malloc(sizeof(database_stringhe));
    cache->testa = NULL;
    cache->num=0;
    //inserimento primo elemento
    fscanf(ptr,"%s", elemento);
    inserisci_in_lista(cache, elemento);
    fscanf(ptr,"%s", elemento);
    inserisci_in_lista(cache, elemento);
    return cache;
}




int inserisci_in_lista (database_stringhe *cache, char *elemento) {

    //prepara il nuovo nodo con la sua stringa
    struct riga *nodo = (struct riga *) malloc (sizeof(struct riga));
    nodo->stringa = malloc(sizeof(elemento) * sizeof(char));

    for (int a=0; a<sizeof(elemento); a++) {
        nodo->stringa[a] = elemento[a];
    }

    struct riga *corrente = cache->testa;
    struct riga *precedente = NULL;

    //se l'elemento corrente è nullo vuol dire che la lista e vuota o siamo arrivati alla fine
    if (corrente == NULL) {
        nodo->next=NULL;
        cache->testa = nodo;
    }
    else {
        //inserimenti successivi
        while (corrente != NULL && strcmp(elemento,corrente->stringa) < 0)  {
            //siamo ad elemento e prima di esso ci va questo
            
            nodo->next=rif;

            return 1;
        }
        
    }
    cache->num++;
    return 1;
}