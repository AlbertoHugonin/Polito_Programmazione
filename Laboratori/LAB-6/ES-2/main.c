#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **malloc2dR(FILE *file, int nr, int nc);
void separa(int **mat, int nr, int nc, int **w, int **b, int *nw, int *nb);

int main() {

    FILE *file = fopen("mat.txt","r");

    int nr,nc,elem_bianchi,elem_neri,**vett_bianchi,**vett_neri;

    fscanf(file,"%d", &nr);
    fscanf(file,"%d", &nc);

    int **mat = malloc2dR(file,nr,nc);

    //stampa la matrice
    for (int r=0; r<nr; r++) {
        for (int c=0; c<nc; c++) {
            printf("%d ", mat[r][c]);
        }
        puts("\n");
    }

    separa(&mat,&nr,&nc,&vett_bianchi,&vett_neri,&elem_bianchi,&elem_neri);

    return 0;
}


void separa(int **mat, int nr, int nc, int **w, int **b, int *nw, int *nb) {

  int i, j, wcnt = 0, bcnt = 0, sq = nr*nc;
  *nw = sq/2;
  *nb = sq/2 + sq%2;
  *w = (int*) calloc(*nw, sizeof(int));
  *b = (int*) calloc(*nb, sizeof(int));
  for(i=0;i<nr;i++) {
    for(j=0;j<nc;j++) {
      if ((i+j)%2) {
        (*w)[wcnt++] = mat[i][j];
      } else
        (*b)[bcnt++] = mat[i][j];
    }
  }
}

int **malloc2dR(FILE *file, int nr, int nc) {

    int **matrice = malloc(nr*sizeof(int *));

    for (int r=0; r<nr; r++) {
        matrice[r] = malloc(nc*sizeof(int));
        for (int c=0; c<nc; c++) {
            fscanf(file, "%d", &matrice[r][c]);
        }
    }

    return matrice;

}