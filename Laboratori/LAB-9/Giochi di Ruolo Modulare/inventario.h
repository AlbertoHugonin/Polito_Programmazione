//controllo di inclusione multipla, occorre se il main prova a includere sia inventario che personaggi
#ifndef INV_H
#define INV_H

//solo per far star zitto visual studio code
#include <stdio.h>
//

typedef struct stat_ {

    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;

} stat;

typedef struct elem_inv_ {

    char *nome; 
    char *tipo;
    stat statistiche;

} elem_inv, vett_equi;

typedef struct tab_inv_ {

    elem_inv *vett_inventario;
    int n;

} tab_inv;


tab_inv *crea_inventario();

tab_inv *carica_inventario(FILE *ptr, tab_inv *inventario);

void aggiungi_elemento_inventario(FILE *ptr, tab_inv *inventario, int a);

int trova_oggetto_inventario(tab_inv *tab_inventario, char *nome_oggetto);

int lunghezza_stringa(char *stringa, int max);
#endif