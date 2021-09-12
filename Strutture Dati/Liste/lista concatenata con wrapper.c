/*
1- typedef struct Lista_ .... Lista per la struttura wrapper, non farlo per il nodo cosi da vedere nel debugger la lista per intero
2- ricordarsi di ritornare la lista fino a che non si opera a livello dei nodi
3- non è necessario usare il doppio puntatore al nodo quando si opera su lista->head
4- è necessario usare il doppio puntatore solo quando si vuole dereferenziare il puntatore ricevuto ad esempio lista e spostarlo da un altra parte ad esempio caricare
la lista da un altra parte
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo_ {

   int id;
   char *Nome;

   struct Nodo_ *next;
   struct Nodo_ *last;

} Nodo, *link;

//struttura wrapper
typedef struct Lista_ {
    
    Nodo *testa;
    Nodo *coda;
    int num_elementi;

} *Lista;



Lista inserimento_in_coda(Lista lista, int id, char *Nome);
Lista inserimento_in_ordine_crescente (Lista lista, int id, char *Nome);
void stampa_lista(Lista lista, int ordine);
Lista inverti_lista(Lista lista);
link inverti_listaR(link corrente, link nuova_coda, link *nuova_testa);
Lista inserimento_in_ordine_crescente_con_puntatori(Lista lista, int id, char *Nome);

Lista inverti_lista(Lista lista) {
    
    link elemento_corrente_lista_inversa = NULL;

    link corrente=lista->testa;
    link successivo = corrente->next;
    link back;




    while (successivo!=NULL) {

        elemento_corrente_lista_inversa = corrente;
        

        back = successivo->next;


        successivo->next=elemento_corrente_lista_inversa;

        //
        elemento_corrente_lista_inversa->last=NULL;
        //

        corrente=successivo;
        successivo = back;


        continue;


    }

    lista->testa=corrente;

    //
    lista->testa->last=NULL;
    //

    //VERSIONE RICORSIVA
    //link nuova_coda;
    //link *nuova_testa = malloc(sizeof(link));
    // nuova_coda = inverti_listaR(lista->testa,nuova_coda,nuova_testa);
    // (*nuova_testa)->last=NULL;
    // nuova_coda->next=NULL;
    // lista->testa=*nuova_testa;
    // //se con coda
    // lista->coda=nuova_coda;

    return lista;


}

link inverti_listaR(link corrente, link nuova_coda, link *nuova_testa) {

    if (corrente->next==NULL) {
        nuova_coda = corrente;
        *nuova_testa=nuova_coda;
        return nuova_coda;
    }
    nuova_coda = inverti_listaR(corrente->next, nuova_coda, nuova_testa);
    nuova_coda->next=corrente;
    /// se doppio linkata
    corrente->last=nuova_coda;
    ///
    nuova_coda=nuova_coda->next;
}
  

int main() {

    Lista lista = malloc(sizeof(*lista));    //creiamo una lista vuota
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
        lista = inserimento_in_ordine_crescente_con_puntatori(lista,id,Nome); //inserisci gli elementi nella lista e ritorna per comodità il numero di elementi
        puts("\n");
    }
    //ordine crescente
    stampa_lista(lista, 1);
    //ordine decrescente
    //stampa_lista(lista,-1);
    //
    inverti_lista(lista);
    stampa_lista(lista, 1);
    //stampa_lista(lista, -1);
    return 0;
}

void stampa_lista(Lista lista, int ordine) {

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

Lista inserimento_in_ordine_crescente_con_puntatori(Lista lista, int id, char *Nome) {

    Nodo *nuovo_nodo = malloc(sizeof(Nodo));
    nuovo_nodo->id=id;
    nuovo_nodo->Nome=strdup(Nome);
    nuovo_nodo->next=NULL;

    Nodo *nodo_corrente = lista->testa;
    Nodo *nodo_precedente = NULL;

    while(nodo_corrente!=NULL) {
        nodo_precedente=nodo_corrente;
        if (nodo_corrente->next!=NULL) {
            if (nuovo_nodo->id - nodo_precedente->id > 0 && nuovo_nodo->id - nodo_corrente->next->id < 0 ) {
                break;
            }
        }
        nodo_corrente=nodo_corrente->next;
    }

    //ci troviamo nella condizioni di avere in nodo_precedente elemento dopo il quale salvare, nodo_corrente dovrebbe essere sempre null
    if (nodo_precedente == NULL) {
        lista->testa=nuovo_nodo;
    }
    else {
        //ci possiamo trovare o alla fine o in mezzo, se siamo in mezzo doppiamo inseire dopo nodo_precedente
        if (nodo_corrente!=NULL) {
            nuovo_nodo->next=nodo_corrente;
        }
        //inserimento alla fine
        nodo_precedente->next=nuovo_nodo;
        }

    lista->num_elementi++;
    return lista;
    

}

//versione inserimento in coda e in mezzo
Lista inserimento_in_ordine_crescente (Lista lista, int id, char *Nome) {

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

Lista inserimento_in_coda (Lista lista, int id, char *Nome) {


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