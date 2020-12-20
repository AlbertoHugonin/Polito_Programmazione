#include "elem_inv.h"

#include "equip_array.h"

typedef struct pers_ {

    char *codice;
    char *nome;
    char *classe;
    stat statistiche;
    equip_array array_equipaggiamento;

    struct pers_ *next;

} pers;

pers *pg_init();
int pers_read(FILE *ptr, pers *personaggio);