#include <stdio.h>
#include <stdlib.h>

void powerset(int sol[], int A[], int scontri[], int n, int pos, int sol_ottima[], int *diff);
int controllo_equilibrio_cardinalita(int sol[], int A[], int n);

int main() {

    int A[] = {0,1,0,0,1,0};
    int n = 6;
    int *B = malloc((n) * sizeof(int));
    int scontri[6] = {0};
    int sol_ottima[6];
    int diff = n;
    //0 e poi 1 sono la sequenza di scontro
    //mantenimento scontro, equilibrio, cardinalità minima
    //come numeri binari ma dobbiamo rispettare le 3 richieste
    
    //troviamo gli scontri e codifichiamoli
    for (int a=0; a<n; a++) {
        B[a] =A[a];
        if (A[a] == 0 && A[a+1] == 1) {
            //abbiamo trovato uno scontro
            scontri[a] = 1;
            scontri[a+1] = 1;
        }
    }
    powerset(A,B,scontri,n,0,sol_ottima,&diff);

    //stampiamo la soluzione ottimale
    for (int a=0; a<n; a++) {
            printf("%d ", sol_ottima[a]);
        }
    return 0;
}

int controllo_equilibrio_cardinalita(int sol[], int A[], int n) {

    int count_s, count_d, diff = 0;

    for (int a=0; a<n; a++) {
        //troviamo lo scontro
        if (sol[a] == 0 && sol[a+1] == 1) {
            //contiamo a sinistra finchè torivamo un 1 o inizio del vettore
            for (int b=a; b>=0; b--) {
                if (sol[b] == 0) {
                    count_s++;
                }
                else {
                    break;
                }
            }
            //contiamo a destro fino alla fine del vettore o fino a che non incontriamo uno 0
            for (int b=a+1; b<n; b++) {
                if (sol[b] == 1) {
                    count_d++;
                }
                else {
                    break;
                }
            }
            if (count_s != count_d) {
                return 0;
            }
            count_s, count_d = 0;
        }
    }
    //calcoliamo il numero di diff e ritorniamolo
    for (int a=0; a<n; a++) {
        if (sol[a] != A[a]) {
            diff++;
        }
    }
    return diff;
}

//variabili globali per il controllo cardinalità soluzione, sol_ottima e diff sono variabili globali
void powerset(int sol[], int A[], int scontri[], int n, int pos, int sol_ottima[], int *diff) {

    if (pos >= n) {
        //condizione di terminazione,controllo se soluzione va bene se si la stampo
        int count = controllo_equilibrio_cardinalita(sol,A,n);
        if (count > 0) {
            if (count < *diff) {
                *diff = count;
                for (int a=0; a<n; a++) {
                    sol_ottima[a] = sol[a];
                }
            }
        }
        return;
    }
    //cambiamo l'orientamento delle frecce senza modificare gli scontri
    if (scontri[pos] == 0) {
        sol[pos] = 0;
        powerset(sol,A,scontri,n,pos+1, sol_ottima, diff);
        sol[pos] = 1;
        powerset(sol,A,scontri,n,pos+1, sol_ottima, diff);
    }
    else {
        powerset(sol,A,scontri,n,pos+1, sol_ottima, diff);
    }
}