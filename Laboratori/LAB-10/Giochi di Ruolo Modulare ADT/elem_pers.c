#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elem_pers.h"

int pers_read(FILE *ptr, pers *personaggio) {

    char codice[MAX_INV];
    char nome[MAX_INV];
    char classe[MAX_INV];

    if (fscanf(ptr, "%s %s %s ", codice, nome, classe) != EOF) {
        personaggio->array_equipaggiamento = equip_array_init();
        stat_read(ptr, &personaggio->statistiche);
        //%d %d %d %d %d %d&personaggio->statistiche.hp, &personaggio->statistiche.mp, &personaggio->statistiche.atk, &personaggio->statistiche.def, &personaggio->statistiche.mag, &personaggio->statistiche.spr
        personaggio->codice = strdup(codice);
        ///////
        personaggio->nome = strdup(nome);
        ///////
        personaggio->classe = strdup(classe);
        return 1;
    }
    return 0;
}