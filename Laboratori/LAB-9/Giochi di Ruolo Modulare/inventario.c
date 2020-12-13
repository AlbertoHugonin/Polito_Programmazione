#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
#define MAX_INV 50

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

int trova_oggetto_inventario(tab_inv *tab_inventario, char *nome_oggetto) {

    int pos;
    for (pos = 0; pos<tab_inventario->n; pos++) {
        if (strcmp(tab_inventario->vett_inventario[pos].nome,nome_oggetto) == 0) {
            return pos;
        }
    }
    return -1;

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