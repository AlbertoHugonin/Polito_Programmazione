#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxN 30

void ruota(int v[MaxN], int N, int P, int dir);



int main() {

    FILE *file = fopen("mat.txt", "r");

    int mat[MaxN][MaxN] = {0};

    int nr, nc;

    fscanf(file, "%d %d", &nr, &nc);

    for (int a=0; a<nr; a++) {
        for (int b=0; b<nc; b++) {
            fscanf(file, "%d", &mat[a][b]);
        }
    }

    //in base alle richieste creiamo il vettore da mandare alla funziona che lo ruota
    char comando[4][25];
    

    while (scanf("%s %s %s %s", &comando[0], &comando[1], &comando[2], &comando[3]) != EOF) {

        //gestione terminazione
        if (strcmp(comando[0], "fine") == 0) {
            puts("TERMINO");
            return 0;
        }

        //gestione spostamenti per riga
        if (strcmp(comando[0], "riga") == 0) {
            if (strcmp(comando[2], "destra") == 0) {
                //passimo solo la riga intera
                ruota(mat[atoi(comando[1])-1], nc, atoi(comando[3]), -1);
            }
            else {
                ruota(mat[atoi(comando[1])], nc, atoi(comando[3]), 1);
            }
        }

        //gestione spostamenti colonna
        if (strcmp(comando[0], "colonna") == 0) {

            //creiamo un vettore facilmente lavorabile
            int vett[30] = {0};
            for (int a=0; a<nr; a++) {
                vett[a] = mat[a][atoi(comando[1])-1];
            }            

            if (strcmp(comando[2], "destra") == 0) {
                ruota(vett, nr, atoi(comando[3]), -1);
            }
            else {
                ruota(vett, nr, atoi(comando[3]), 1);
            }
            
            //adesso dobbiamo riscrivere il vettore nuovo dentro quello vecchio
            for (int a=0; a<nr; a++) {
                mat[a][atoi(comando[1])-1] = vett[a];
            }

        } 
        puts("\nRisultato:\n");       
        for (int a=0; a<nr; a++) {
            for (int b=0; b<nc; b++) {
                printf("%d ", mat[a][b]);
            }
            puts("\n");
        }
        puts("\n");
    }

    return 0;
}



void ruota(int v[MaxN], int N, int P, int dir) {

    //nel caso di rotazioni a sinistra

    if (dir == 1) {
        P = N - P;
    }

    int supp[N];

    int rif = 0;

    for (int a=P; a<N; a++) {
        supp[a] = v[rif];
        rif += 1;
    }
    for (int a=0; a<P; a++) {
        supp[a] = v[rif];
        rif += 1;
    }

    //viene fatto utilizzo che i vettori vengono passati per riferimento
    for (int a=0; a<N; a++) {
        v[a] = supp[a];
    }
    return;
}