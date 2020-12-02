#include <stdio.h>
#include <stdlib.h>


int main() {

    FILE *matrice;
    int nr, nc = 0;
    int Matrice[20][20] = { 0 };
    
    matrice = fopen("mat.txt", "r");

    fscanf(matrice, "%d %d", &nr, &nc);

    //salvataggio matrice
    for (int a=0; a<nr; a++) {
        for (int b=0; b<nc; b++) {
            fscanf(matrice, "%d", &Matrice[a][b]);
        }
    }

    fclose(matrice);


    //imposta la dimensione
    int dim = 3;


    int somma = 0;
    int val = 0;
    int x,y = 0;

    for (int a=0; a<nr; a++) {
        for (int b=0; b<nc; b++) {

            //controllo contorni matrice
            if (b+dim > nc || a+dim > nr) {
            break;
            }
            //offset
            for (int r=0; r<dim; r++) {
                for (int c=0; c<dim; c++) {
                    printf("%d ", Matrice[a+r][b+c]);
                    fflush(stdout);
                    val = val + Matrice[a+r][b+c];
                }
                printf("\n");
            }
            printf("\n");
            //prendo le coordinate della tabella vincente
            if (val > somma) {
                somma = val;
                x = a;
                y = b;
            }
            val = 0;
        }
    }

    //leggo matrice grande

    printf("La matrice con la somma piu' grande (%d) e': \n", somma);
    for (int a=x; a<x+dim; a++) {
        for (int b=y; b<y+dim; b++) {
            printf("%d ", Matrice[a][b]);
        }
        printf("\n");
    }


    return 0;
}