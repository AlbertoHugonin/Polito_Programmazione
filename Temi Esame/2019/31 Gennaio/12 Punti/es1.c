#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define R 4
#define C 3

int minmaxdiff(int **A, int n, int m);

int minmaxdiff(int **A, int n, int m) {

    int best = 0;
    int best_rel = 0;

    int best_previous = 0;
    int best_i = 0;

    int r = 0;
    int c = 0;

     for (r=0; r<n; r++) {
        for (c=0; c<m; c++) {
            printf("%d ", A[r][c]);  
        }
        puts("");
     }

    for (c=0; c<C; c++) {
        for (r=0; r<R-1; r++) {
            if (best == 0) {
                best = A[r][c] - A[r+1][c];
                if (best < 0) {
                    best = best * -1;
                }
            } else {
                best_rel = A[r][c] - A[r+1][c];
                if (best_rel < 0) {
                    best_rel = best_rel * -1;
                }
                //massimizziamo la differenza nella colonna
                if (best_rel>best) {
                    best = best_rel;
                }
            }
        }
        //in best è contenuto il migliore della riga
        if (best_previous == 0 || best < best_previous) {
            best_previous = best;
            best_i = c;
        }
        best = 0;
        best_rel = 0;
    }

    printf("Colonna n: %d\n", best_i+1);
}

int main() {

    //4 righe 3 colonne
    int **A = malloc(R*sizeof(int));
    for (int a=0; a<R; a++) {
        A[a] = malloc(C*sizeof(int));
    } 

    A[0][0]=15;
    A[0][1]=12;
    A[0][2]=7;
    A[1][0]=6;
    A[1][1]=18;
    A[1][2]=4;
    A[2][0]=11;
    A[2][1]=4;
    A[2][2]=12;
    A[3][0]=13;
    A[3][1]=9;
    A[3][2]=5;



    minmaxdiff(A,R,C);
    
}