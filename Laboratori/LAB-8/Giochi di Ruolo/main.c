#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INV 50
//in una lista l'elenco dei personaggi
//vettore di strutture l'elenco di oggetti


//parte inventario
typedef struct stat_ {

    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;

} stat;

typedef struct elem_inv_ {

    //cosi non dobbiamo allocare noi
    char *nome; 
    char *tipo;
    stat statistiche;

} elem_inv, vett_equi;

typedef struct tab_inv_ {

    elem_inv *vett_inventario;
    int n;

} tab_inv;

//////////////////////////////////

typedef struct tab_equi_ {

    int inUso;
    vett_equi *vett_equipaggiamento;

} tab_equi;

typedef struct pers_ {

    char *codice;
    char *nome;
    char *classe;
    stat statistiche;
    tab_equi tab_equipaggiamento;

    struct pers_ *next;

} pers;

//wrapper della lista personaggi
typedef struct tab_pers_ {

    pers *head;
    pers *tail;
    int n_personaggi;

} tab_pers;

//////////////////////////////////////

tab_inv *carica_inventario(FILE *ptr, tab_inv *inventario);
tab_inv *crea_inventario();
void aggiungi_elemento_inventario(FILE *ptr, tab_inv *inventario, int a);
int lunghezza_stringa(char *stringa, int max);

///////////////////////////////////////
tab_pers *crea_tabella_personaggi();
void carica_personaggi_da_file( tab_pers *tabella_personaggi, FILE *file);
pers crea_pers_personalizzato();
pers *aggiungi_personaggio(pers personaggio, tab_pers *tab_personaggi, pers *aggiunto);
void formatta_stringhe_pers(pers *personaggio, char *codice, char *nome, char *classe);
//////////////////////////////////////


int main() {
    //caricare inventario
    tab_inv *tabella_inventario  = crea_inventario();

    FILE *file_inventario = fopen("inventario.txt", "r");


    tabella_inventario = carica_inventario(file_inventario,tabella_inventario);

    //era anche possibile nascondere il puntatore alla funzione main (vedere parte modularità)
    tab_pers *tabella_personaggi = crea_tabella_personaggi();

    FILE *file_personaggi = fopen("pg.txt", "r");

    carica_personaggi_da_file(tabella_personaggi,file_personaggi);

    //crea personaggio (puo' esere usata anche dalla carica personaggi)
    pers personaggio = crea_pers_personalizzato();

    //aggiungi personaggio
    aggiungi_personaggio(personaggio,tabella_personaggi, NULL);

    return 0;
}

pers crea_pers_personalizzato() {

    pers *personaggio = malloc(sizeof(pers));

    int n;

    char codice[MAX_INV];
    char nome[MAX_INV];
    char classe[MAX_INV];

    puts("Inserisci le seguenti informazioni:");
    puts("< Codice > < Nome > < Classe > < HP > < MP > < ATK > < DEF > < MAG > < SPR >");
    fflush(stdin);
    fscanf(stdin, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &personaggio->statistiche.hp, &personaggio->statistiche.mp, &personaggio->statistiche.atk, &personaggio->statistiche.def, &personaggio->statistiche.mag, &personaggio->statistiche.spr);
    formatta_stringhe_pers(personaggio,codice,nome,classe);
    return *personaggio;
}

//si occupa di prendere i dati da file, creare con essi un personaggio e farlo aggiungere alla funziona aggiungi personaggio
void carica_personaggi_da_file(tab_pers *tabella_personaggi, FILE *file) {

    //creiamo il primo personaggio
    pers *personaggio = malloc(sizeof(pers));
    pers *aggiunto = NULL;

    int n;

    char codice[MAX_INV];
    char nome[MAX_INV];
    char classe[MAX_INV];

    while (fscanf(file, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &personaggio->statistiche.hp, &personaggio->statistiche.mp, &personaggio->statistiche.atk, &personaggio->statistiche.def, &personaggio->statistiche.mag, &personaggio->statistiche.spr) != EOF)
    {
        formatta_stringhe_pers(personaggio,codice,nome,classe);
        aggiunto = aggiungi_personaggio(*personaggio, tabella_personaggi, aggiunto);
        free(personaggio);
        personaggio = malloc(sizeof(pers));
    }

    return;
}

void formatta_stringhe_pers(pers *personaggio, char *codice, char *nome, char *classe)
{
    int n;
    n = lunghezza_stringa(codice, MAX_INV);
    personaggio->codice = malloc(n * sizeof(char));
    memcpy(personaggio->codice, codice, n * sizeof(char));
    ///////
    n = lunghezza_stringa(nome, MAX_INV);
    personaggio->nome = malloc(n * sizeof(char));
    memcpy(personaggio->nome, nome, n * sizeof(char));
    ///////
    n = lunghezza_stringa(classe, MAX_INV);
    personaggio->classe = malloc(n * sizeof(char));
    memcpy(personaggio->classe, classe, n * sizeof(char));
    personaggio->next = NULL;
}

pers *aggiungi_personaggio(pers personaggio, tab_pers *tab_personaggi, pers *aggiunto) {

    //questa malloc risolve tutto, senza memcpy è come se copiasse il puntatore e non il contenuto (non è la strdup che f anche la malloc)
    pers *nodo = malloc(sizeof(pers));
    memcpy(nodo,&personaggio,sizeof(pers));
    nodo->next=NULL;

    if (tab_personaggi->head == NULL) {
        tab_personaggi->head=nodo;
        tab_personaggi->tail=nodo;
        tab_personaggi->n_personaggi++;
        return nodo;
    }
    else {
        //versione solo inserimento in coda
        if (aggiunto != NULL) {
            //usiamo il riferimento
            aggiunto->next=nodo;
            tab_personaggi->tail=nodo;
            tab_personaggi->n_personaggi++;
            return nodo;
        } else {
            //allora dobbiamo scorrere la lista
            pers *corrente = tab_personaggi->head;
            while (corrente->next != NULL) {
                corrente = corrente->next;
            }
            corrente->next=nodo;
            tab_personaggi->tail=nodo;
            tab_personaggi->n_personaggi++;
            return nodo;
        }

    }

}



tab_pers *crea_tabella_personaggi() {
    
    tab_pers *tab_personaggi = malloc(sizeof(tab_pers));
    
    tab_personaggi->n_personaggi = 0;
    tab_personaggi->head = NULL;
    tab_personaggi->tail = NULL;

    return tab_personaggi;
}


tab_inv *crea_inventario() {

    tab_inv *inventario = malloc (sizeof(tab_inv));

    inventario->n=0;
    inventario->vett_inventario=NULL;

    return inventario;
}

tab_inv *carica_inventario(FILE *ptr, tab_inv *inventario) {

    int n_elementi;
    fscanf(ptr, "%d", &n_elementi);

    //allocazione vett inventario
    inventario->vett_inventario = malloc(n_elementi*sizeof(elem_inv));

    for (int a=0; a<n_elementi; a++) {
        aggiungi_elemento_inventario(ptr,inventario,a);
    }

    return inventario;

}

void aggiungi_elemento_inventario(FILE *ptr, tab_inv *inventario, int a) {

    elem_inv *corrente = inventario->vett_inventario+a;

    int n;
    char cache[MAX_INV];

    fscanf(ptr,"%s", cache);
    n = lunghezza_stringa(cache,MAX_INV);
    corrente->nome = malloc(n*sizeof(char));
    memcpy(corrente->nome,cache,n*sizeof(char));

    fscanf(ptr,"%s", cache);
    n = lunghezza_stringa(cache,MAX_INV);
    corrente->tipo = malloc(n*sizeof(char));
    memcpy(corrente->tipo,cache,n*sizeof(char));

    stat *ptr_stat = &corrente->statistiche;

    //il simbolo & fa riferimento all'ultimo nella sequenza ->sdddf->atk (è l'unica spiegazione)
    fscanf(ptr, "%d %d %d %d %d %d", &ptr_stat->hp, &ptr_stat->mp, &ptr_stat->atk, &ptr_stat->def, &ptr_stat->mag, &ptr_stat->spr);

    inventario->n++;
    return;
}


int lunghezza_stringa(char *stringa, int max) {

    int n = 0;
    for (int a=0; a<max; a++) {
        if (stringa[a] != '\0') {
            n++;
        } else {
            break;
        }
    }
    return n;
}