#include "inventario.h"

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


tab_pers *crea_tabella_personaggi();
void carica_personaggi_da_file( tab_pers *tabella_personaggi, FILE *file);

pers crea_pers_personalizzato();

pers *aggiungi_personaggio(pers personaggio, tab_pers *tab_personaggi, pers *aggiunto);
pers elimina_personaggio(tab_pers *tab_personaggi, char *codice_pers);

void aggiungi_equipaggiamento(tab_pers *tab_personaggi, tab_inv *tab_inventario, char *codice_pers, char *nome_oggetto);
void elimina_equipaggiamento(tab_pers *tab_personaggi, char *codice_pers, char *nome_oggetto);

void calcola_statistiche(tab_pers *tab_personaggi, char *codice_pers);


pers *trova_personaggio(tab_pers *tab_personaggi, char *codice_pers);
int trova_oggetto_equipaggiamento(pers *personaggio, char *nome_oggetto);


void formatta_stringhe_pers(pers *personaggio, char *codice, char *nome, char *classe);