#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

} elem_inv;

typedef struct tab_inv_ {

    elem_inv *vett_inventario;
    int n;

} tab_inv;


//////////////////////////////////////

tab_inv *carica_inventario(FILE *ptr, tab_inv *inventario);
tab_inv *crea_inventario();
void aggiungi_elemento_inventario(FILE *ptr, tab_inv *inventario, int a);
int lunghezza_stringa(char *stringa, int max);

//////////////////////////////////////


int main() {
    //caricare inventario
    tab_inv *tabella_inventario  = crea_inventario();

    FILE *file_inventario = fopen("inventario.txt", "r");


    tabella_inventario = carica_inventario(file_inventario,tabella_inventario);

    return 0;
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
    char cache[50];

    fscanf(ptr,"%s", &cache);
    n = lunghezza_stringa(cache,50);
    corrente->nome = malloc(n*sizeof(char));
    memcpy(corrente->nome,cache,n*sizeof(char));

    fscanf(ptr,"%s", &cache);
    n = lunghezza_stringa(cache,50);
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