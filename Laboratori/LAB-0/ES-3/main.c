#include <stdio.h>
#define MaxN 30

void ruota(int v[MaxN], int N, int P, int dir);


int main() {

    int N;
    int vett[MaxN] = {0};

    puts("Dimmi il numero di elementi del vettore");
    scanf("%d", &N);
    puts("Dimmi gli elementi");
    for (int a=0; a<N; a++) {
        scanf("%d", &vett[a]);
    }
    ruota(vett, N, 4, +1); //direzione destra
    for (int a=0; a<N; a++) {
        printf("%d ", vett[a]);
    }
    puts("\n");
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