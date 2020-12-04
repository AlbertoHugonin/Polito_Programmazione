#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    FILE *file = fopen("matrice collegamenti.txt", "r");

    int nr,nc;

    fscanf(file, "%d", &nr);
    fscanf(file, "%d", &nc);

    int **matrice = malloc(nr*sizeof(int));

    for (int r=0; r<nr; r++) {
        matrice[r] = malloc(nc*sizeof(int));
        for (int c=0; c<nc; c++) {
            fscanf(file, "%d", &matrice[r][c]);
        }
    }

    //stampa matrice
    // for (int r=0; r<nr; r++) {
    //     for (int c=0; c<nc; c++) {
    //         printf("%d ", matrice[r][c]);
    //     }
    //     puts("\n");
    // }

    

    return 0;
}