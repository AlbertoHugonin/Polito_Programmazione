#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void powerset_combinazioni_semplici( int *sol, int *val, int n, int k, int pos, int start, int **matrice, int nc, int *trovata);
int controllo(int *sol, int k, int **matrice, int nr, int nc);

int main() {

    FILE *file = fopen("matrice collegamenti.txt", "r");

    int nr,nc;

    int i;

    fscanf(file, "%d", &nr);
    fscanf(file, "%d", &nc);

    int **matrice = malloc(nr*sizeof(int));

    for (int r=0; r<nr; r++) {
        matrice[r] = malloc(nc*sizeof(int));
        for (int c=0; c<nc; c++) {
            fscanf(file, "%d", &matrice[r][c]);
        }
    }

    int *val = malloc(nr * sizeof(int));
    int *sol = malloc(nr * sizeof(int));

    for (i=0; i<nr; i++) {
        val[i] = i;
    }

    int trovata = 0;

    for (i=1; i<=nr; i++) {
        powerset_combinazioni_semplici(sol,val,nr,i,0,0, matrice,nc,&trovata);
        if (trovata == 1) {
            break;
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

void powerset_combinazioni_semplici( int *sol, int *val, int n, int k, int pos, int start, int **matrice, int nc, int *trovata) {

    int i;

    if (pos >= k) {
        //controllo
        printf("{ ");
            for (i=0; i<k; i++) {
                printf("%d ", sol[i]);
            }
            printf("}");
        if (controllo(sol,k,matrice,n,nc) == 1) {
            puts(" SOLUZIONE CORRETTA");
            *trovata = 1;
            return;
        }else {
            puts("");
        }
        return;
    }
    for (i=start; i<n; i++) {
        sol[pos] = val[i];
        //le scelte che precedono l'indice start non sono piu' disponibili cosi da forzare l'ordine
        powerset_combinazioni_semplici(sol,val,n,k,pos+1,i+1, matrice,nc,trovata);
    }
}

//funzione di controllo che prende la matrice, le sue dimensioni e il vettore soluzione con la sua dimensione
int controllo(int *sol, int k, int **matrice, int nr, int nc) {

    int count;

    for (int c=0; c<nc; c++) {
        count = 0;
        for (int r=0; r<nr; r++) {
            for (int indice=0; indice<k; indice++) {
                if (matrice[r][c] == 1 && sol[indice] == r) {
                    count++;
                }
            }
        }
        if (count%2 == 0) {
            //se da resto vuol dire che è dispari quindi la luce è accesa, se pari non è la soluzione
            return 0;
        }
    }
    return 1;
}
