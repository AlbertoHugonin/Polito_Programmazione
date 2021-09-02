#include <stdio.h>
#include <stdlib.h>

//////////LIST OF FIXES
//1- nel for a++ in i++ 
//2- modificati parametri funzione da **matr a ***matr (puntatore a puntatore)
//3- aggiunti i relativi cast nelle malloc e printf

void f(int *v1, int *v2, int d1, int d2, int ***matr);


int **matr;

int main() {

    int v1[] = {2,4,6};
    int d1 = 3;
    int v2[] = {1,3,5,7};
    int d2 = 4;
    int **matr;
    f(v1,v2,d1,d2,&matr);
    fflush(stdout);
    //print matrice
    for (int i=0; i<d1; i++) {
        for (int j=0; j<d2; j++) {
            printf("%d ", matr[i][j]);
        }
    puts("");
}
    return 0;
}




void f(int *v1, int *v2, int d1, int d2, int ***matr) {
int i = 0;
int j=0;
//allochiamo il numero di righe della matrice
*matr = malloc(d1*sizeof(int *));
//allochiamo le colonne
for (i=0; i<d1; i++) { (*matr)[i] = malloc(d2*sizeof(int)); }

for (i=0; i<d1; i++) {
   for (j=0; j<d2; j++) {
       (*matr)[i][j] = v1[i]+v2[j];
       printf("%d ", (*matr)[i][j]);
   }
   puts("");
}
}