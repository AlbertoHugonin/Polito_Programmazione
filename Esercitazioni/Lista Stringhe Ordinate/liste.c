#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//massima lunghezza stringa
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
int aggiungi (database_stringhe *lista);


int main() {


    database_stringhe *lista = carica_lista();
    //se la lista contiene numeri
    int n = aggiungi(lista);

    return n;
}

//solo per stringe con numeri tra 1 e 9 a causa dell'uso di strcmp
int aggiungi (database_stringhe *lista) {

    int count = 0;

    //salviamo l'inizio della lista e il numero degli elementi
    struct riga *precedente = NULL;
    struct riga *corrente = lista->testa;
    int num_elementi = lista->num;
    char *elemento = malloc(MAX_N * sizeof(char));

    //troviamo il primo numero in testa
    int valore_precedente;
    int valore_corrente;

    struct riga *ripresa;

    //iteriamo tutti gli elementi successivi
    

    while (corrente != NULL && corrente->next != NULL) {

        //testa
        valore_precedente = atoi(corrente->stringa);
        precedente = corrente;
        //successivo
        corrente = corrente->next;
        valore_corrente = atoi(corrente->stringa);

        if (valore_corrente-valore_precedente > 1) {

            for (int b=valore_precedente+1; b<valore_corrente; b++) {

                sprintf(elemento, "%d", b);
                inserisci_in_lista(lista,elemento);
                count += 1;
            }
            corrente = precedente;
        }
    }

    return count;
}


database_stringhe *carica_lista() {

    FILE *ptr = fopen("lista_stringhe", "r");

    char *elemento = malloc(MAX_N * sizeof(char));
    database_stringhe *cache = (database_stringhe *)malloc(sizeof(database_stringhe));
    cache->testa = NULL;
    cache->num=0;
    //inserimento primo elemento
    while (fscanf(ptr,"%s", elemento) == 1) {
        inserisci_in_lista(cache, elemento);
    }
    return cache;
}




int inserisci_in_lista (database_stringhe *cache, char *elemento) {

    //prepara il nuovo nodo con la sua stringa
    struct riga *nodo = (struct riga *) malloc (sizeof(struct riga));
    nodo->stringa = strdup(elemento);
    struct riga *corrente = cache->testa;
    struct riga *precedente = NULL;

    //se l'elemento corrente è nullo vuol dire che la lista e vuota o siamo arrivati alla fine
    if (corrente == NULL) {
        nodo->next=NULL;
        cache->testa = nodo;
    }
    else {
        //continuiamo a scorrere la lista finche non troviamo l'elemento giusto
        while (corrente != NULL && strcmp(elemento,corrente->stringa) > 0)  {
            precedente = corrente;
            corrente = corrente->next;
        }
        //trovato il posto giusto facciamo distinzione se siamo al primo elemento dopo la testa o no
        if (precedente==NULL) {
            cache->testa = nodo;
            nodo->next=corrente;
        }
        else {
            //caso generale centrale
            precedente->next=nodo;
            nodo->next=corrente;
        }
    }
    cache->num++;
    return 1;
}