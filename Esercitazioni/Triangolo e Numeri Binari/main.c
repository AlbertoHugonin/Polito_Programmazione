#include <stdio.h>
#include <stdlib.h>

void triangolo_decrescente(int A[], int n);
void triangolo_crescente(int A[], int n);
void numeri_binari(int *B, int n, int pos);
int controllo_numeri_binari(int *B, int n);
int conta_uni(int *B, int l, int r);

int main() {

    int A[] = {1,2,3,4,5};
    // triangolo_crescente(A,5);
    // puts("\n");
    // triangolo_decrescente(A,5);
    int n = 3;
    int *B = malloc((n) * sizeof(int));
    numeri_binari(B,n,0);

}


//conta il numero di uni di un vettore in un determinato intervallo
int conta_uni(int *B, int l, int r) {
    int count = 0;
    for (int c=l; c<=r; c++) {
        if (B[c] == 1) {
            count++;
        }
    }
    return count;
}

//si occupa di controllare che il numero di uni sia uguale nella parte destra e sinistra di un vettore dato
int controllo_numeri_binari(int *B, int n) {
    int l=0, r = n-1, m = (l+r)/2;
    int count_s, count_d;
    //dobbiamo vedere il caso n pari o n dispari
    //n%2 resto della divisione per 2 di n
    if ((n%2) == 0) {
        count_s = conta_uni(B, l, m);
        count_d = conta_uni(B, m+1, r);
    }
    else {
        //se il numero è dispari non guardiamo l'elemento m
        count_s = conta_uni(B, l, m-1);
        count_d = conta_uni(B, m+1, r);
    }
    if (count_s == count_d) {
        return 1;
    }
    else {
        return 0;
    }
}

//funzione ricorsiva dei numeri binari
void numeri_binari(int *B, int n, int pos) {
    if (pos >= n) {
        //condizione di terminazione,controllo se soluzione va bene se si la stampo
        if(controllo_numeri_binari(B,n) == 1) {
            for (int a=0; a<n; a++) {
            printf("%d", B[a]);
        }
        puts("\n");
        }
        return;
    }
    B[pos] = 0;
    numeri_binari(B,n,pos+1);
    B[pos] = 1;
    numeri_binari(B,n,pos+1);
}


//////////////////////////////////////////////////////////////
void triangolo_decrescente(int A[], int n) {
    for (int a=0; a<n; a++) {
        printf("%d ", A[a]);
    }
    puts("\n");
    //condizione di terminazione
    if(n < 1) {
        return;
    }
    int *B = malloc((n-1) * sizeof(int));
    //calcoliamo il vettore successivo
    for (int a=0; a<n-1; a++) {
        B[a] = A[a] + A[a+1];
    }
    triangolo_decrescente(B,n-1);

}

//todo
void triangolo_crescente(int A[], int n) {
    //condizione di terminazione
    if(n < 1) {
        return;
    }
    int *B = malloc((n-1) * sizeof(int));
    //calcoliamo il vettore successivo
    for (int a=0; a<n-1; a++) {
        B[a] = A[a] + A[a+1];
    }
    triangolo_crescente(B,n-1);
    for (int a=0; a<n; a++) {
        printf("%d ", A[a]);
    }
    puts("\n");
}