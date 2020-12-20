//controllo di inclusione multipla, occorre se il main prova a includere sia inventario che personaggi
#ifndef INV_H
#define INV_H

//solo per far star zitto visual studio code
#include <stdio.h>
//

#include "elem_inv.h"

typedef struct tab_inv_ *tab_inv;

tab_inv crea_inventario();

tab_inv carica_inventario(FILE *ptr, tab_inv inventario);

int trova_oggetto_inventario(tab_inv tab_inventario, char *nome_oggetto);

int lunghezza_stringa(char *stringa, int max);
#endif