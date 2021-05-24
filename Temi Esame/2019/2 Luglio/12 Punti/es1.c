#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {

    int n = 5;
    //occhio a * perchè è un vettore di int
    int **matr = malloc(n*sizeof(int *));

    int a,b;

    for (a=0; a<n; a++) {
        matr[a] = malloc(n*sizeof(int));
        for (b=0; b<n; b++) {
            matr[a][b] = 0;
        }
    }
    int s = 0;
    a=0;
    b=0;

    while (a<n && b<n) {
        //siamo sulla diagonale principale e ci salviamo il punto di inizio dell'elemento successibo
        int nc = b+1;
        int counter = 1;
        while (nc<n) {
            matr[a][nc] = counter;
            nc++;
            counter++;
        }
        counter = 1;
        nc = b-1;
        while (nc>=0) {
            matr[a][nc] = counter;
            nc--;
            counter++;
        }
        a++;
        b++;
    }

    for (int r=0; r<n; r++) {
        for (int c=0; c<n; c++) {
            printf("%d ", matr[r][c]);
        }
        puts("\n");
    }
    return 0;
}