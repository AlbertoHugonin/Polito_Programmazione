#include<stdio.h>
#define k 20

int main() {

    int n,m;
    int somme[k] = {0};
    int mat[k][k] = {0};
    FILE *mat_file;
    int indice = 0;

    mat_file = fopen("mat.txt", "r");

    fscanf(mat_file, "%d %d", &n, &m);

    for (int a=0; a<n; a++) {
        for (int b=0; b<m; b++) {
            fscanf(mat_file, "%d", &mat[a][b]);
        }
    }

    for (int b=0; b<m; b++) {
        for (int a=0; a<n; a++) {
            somme[a] += mat[a][b];
            if (somme[indice] < somme[a]) {
                indice = a;
            }
        }
        //appena finita la giornata indico l'indice della squadra capolista
        printf("La squadra capolista alla giornata %d e' la numero %d\n", b+1, indice+1);
    }

    return 0;
}