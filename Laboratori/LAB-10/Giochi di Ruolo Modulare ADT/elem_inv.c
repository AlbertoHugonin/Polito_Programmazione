#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elem_inv.h"


void read_elem_inv(FILE *ptr, elem_inv *corrente) {

    char cache[MAX_INV];

    fscanf(ptr,"%s", cache);

    corrente->nome = strdup(cache);

    fscanf(ptr,"%s", cache);

    corrente->tipo = strdup(cache);

    stat *ptr_stat = &corrente->statistiche;

    stat_read(ptr,ptr_stat);

    return;
}


void stat_read(FILE *fp, stat *ptr_stat) {
    fscanf(fp, "%d %d %d %d %d %d", &ptr_stat->hp, &ptr_stat->mp, &ptr_stat->atk, &ptr_stat->def, &ptr_stat->mag, &ptr_stat->spr);
}

