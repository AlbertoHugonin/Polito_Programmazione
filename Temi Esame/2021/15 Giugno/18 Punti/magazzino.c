#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "magazzino.h"

struct Magazzino_ {

    //numero corridoi
    int C;
    //vettore di corridoi
    Corridoio *corridoi;
};

Magazzino MagazzinoInit() {
    Magazzino magazzino = malloc(sizeof(struct Magazzino_ *));
    magazzino->corridoi = NULL;
    magazzino->C=0;
    return magazzino;
}

Magazzino MagazzinoScan(FILE *struttura) {
    //prende il file e lo carica creando la struttura del magazzino
}

Magazzino MagazzinoScanPacco(FILE *pacchi) {
    
}