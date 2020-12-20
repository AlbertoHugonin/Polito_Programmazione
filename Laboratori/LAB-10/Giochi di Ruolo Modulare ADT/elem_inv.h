#ifndef ELEM_INV
#define ELEM_INV
#define MAX_INV 30

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

} elem_inv;


void read_elem_inv(FILE *ptr, elem_inv *corrente);
void *print_elem_inv();

void stat_read(FILE *fp, stat *ptr_stat);
#endif