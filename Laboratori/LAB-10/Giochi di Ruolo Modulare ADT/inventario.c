#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"


struct tab_inv_ {

    elem_inv *vett_inventario;
    int n;

};


tab_inv crea_inventario() {

    tab_inv inventario = malloc (sizeof(tab_inv));

    inventario->n=0;
    inventario->vett_inventario=NULL;

    return inventario;
}

tab_inv carica_inventario(FILE *ptr, tab_inv inventario) {

    int n_elementi;
    fscanf(ptr, "%d", &n_elementi);

    //allocazione vett inventario
    inventario->vett_inventario = malloc(n_elementi*sizeof(elem_inv));

    for (int a=0; a<n_elementi; a++) {
        read_elem_inv(ptr,&inventario->vett_inventario[a]);
        inventario->n++;
    }

    return inventario;

}

int trova_oggetto_inventario(tab_inv tab_inventario, char *nome_oggetto) {

    int pos;
    for (pos = 0; pos<tab_inventario->n; pos++) {
        if (strcmp(tab_inventario->vett_inventario[pos].nome,nome_oggetto) == 0) {
            return pos;
        }
    }
    return -1;

}