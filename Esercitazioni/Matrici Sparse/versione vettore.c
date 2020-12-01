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
int accediMatr(riga *matrice_sparsa, int x, int y, int r, int c);

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

    riga *matrice_sparsa = CreaMatrice (r,c,matrice);

 
    //stampa matrice sparsa e relazioni interne (solo valori diversi da zero);
    for (int a=0; a<r; a++) {
        printf("Num elementi riga n.%d sono: %d\n\n", a+1, matrice_sparsa[a].count);
        for (int b=0; b<matrice_sparsa[a].count; b++) {
            printf("\tElemento indice n.%d e': %d\n", matrice_sparsa[a].elementi[b].n_col + 1, matrice_sparsa[a].elementi[b].n);
        }
        puts("\n");
    }
    puts("\n");
    
    //richiediamo tutti gli elementi della matrice
    for (int a=0; a<r; a++) {
        for (int b=0; b<c; b++) {
            printf("%d ", accediMatr(matrice_sparsa,a,b,r,c));
        }
        puts("\n");
    }

    return 0;
}

int accediMatr(riga *matrice_sparsa, int x, int y, int r, int c) {

    if (x>=r || y >= c || x<0 || y<0) {
        return 0;
    }
    for (int b=0; b<matrice_sparsa[x].count; b++) {
        if (matrice_sparsa[x].elementi[b].n_col == y) {
            return matrice_sparsa[x].elementi[b].n;
        }
    }
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

        vett_righe[a].elementi = (elemento *) malloc (count * sizeof(elemento));
        vett_righe[a].count = count;

        int indice = 0;

        for (int b=0; b<c; b++) {
            if (matrice[c*a + b] != 0) {
                //inserimento in vett_elementi
                vett_righe[a].elementi[indice].n_col=b;
                vett_righe[a].elementi[indice].n = matrice[c*a + b];
                indice++;
            }
        }
    }
    
    return vett_righe;
}