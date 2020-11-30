#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct elemento_ {
    int n;
    int n_col;
} elemento;


typedef struct riga_ {
    int count;
    elemento *elementi;

} riga;

riga *CreaMatrice (int r, int c, int *matrice);

int main() {

    FILE *tabella = fopen("matrice.txt", "r");
    //prendiamo le dimensioni della matrice

    int r,c;

    fscanf(tabella,"%d", &r);
    fscanf(tabella,"%d", &c);

    //matrice di supporto con vettore dinamico
    int *matrice = malloc (r * c * (sizeof(int)));

    for (int a=0; a<r; a++) {
        for (int b=0; b<c; b++) {
            fscanf(tabella, "%d", &matrice[c*a + b]);
        }
    }

    CreaMatrice (r,c,matrice);

    return 0;
}

riga *CreaMatrice (int r, int c, int *matrice) {

    //andiamo a creare un vettore di righe che indica tutte le rige
    riga *vett_righe = (riga *) malloc (r * sizeof(riga));

    //partiamo riga per riga
    for (int a=0; a<r; a++) {

        int count = 0;

        for (int b=0; b<c; b++) {
            if (matrice[c*a + b] != 0) {
                count++;
            }
        }

        elemento *vett_elementi = (elemento *) malloc (count * sizeof(elemento));

        int indice = 0;

        for (int b=0; b<c; b++) {
            if (matrice[c*a + b] != 0) {
                //inserimento in vett_elementi
                vett_elementi[indice].n_col=b;
                vett_elementi[indice].n = matrice[c*a + b];
                indice++;
            }
        }
        vett_righe->count=count;
        vett_righe->elementi=vett_elementi;
    }
    
    return vett_righe;
}