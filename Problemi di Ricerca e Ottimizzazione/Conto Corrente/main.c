#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 10

int permuzazioni_semplici(int *val, int *sol, int *mark, int n, int pos, int *best_sol, int *best_diff, FILE *result, int *count);
int check(int *sol, int n, int *best_sol, int *best_diff);

int main() {

    FILE *result = fopen("risultato.txt","w");
    int val[N] = {-1,-6,3,14,-5,16,7,8,-9,120};
    
    int *sol = malloc(N*sizeof(int));
    int *best_sol = malloc(N*sizeof(int));

    //impostato sul massimo cosi' se troviamo una differenza minore possiamo sovrascriverla
    int best_diff = INT_MAX;

    int count = 0;

    int *mark = malloc(N*sizeof(int));

    for (int a=0; a<N; a++) {
        mark[a] = 0;
    }
    permuzazioni_semplici(val,sol,mark,N,0,best_sol,&best_diff,result,&count);
    fclose(result);
    printf("Soluzione migliore ");
    for (int a=0; a<N; a++) {
        printf("%d ", best_sol[a]);
    }
    puts("");
    fflush(stdout);
    return 0;
}

//complessità N fattoriale genera tutti gli ordinamenti possibili del vettore val
int permuzazioni_semplici(int *val, int *sol, int *mark, int n, int pos, int *best_sol, int *best_diff, FILE *result, int *count) {

    if (pos>=n) {
        //caso terminale controlliamo la soluzione contenuta interamente nel vettore sol
        // for (int b=0; b<n; b++) {
        //     fprintf(result,"%d ", sol[b]);
        // }
        // fprintf(result, "\n");
        // (*count)++;
        // if (*count > 1000) {
        //     fflush(result);
        //     *count = 0;
        // }
        //calcolo soluzione per ottimalità
        check(sol,n,best_sol,best_diff);

        return 0;
    }

    for (int a=0; a<n; a++) {

        //quando uguale a 0 elemento non ancora preso
        if (mark[a] == 0) {
            mark[a] = 1;
            //costruiamo direttamente la soluzione, pos parte da 0 ed è crescente quindi perfetto per comporre il vettore soluzione
            sol[pos]=val[a];

            permuzazioni_semplici(val,sol,mark,n,pos+1,best_sol,best_diff,result,count);
            mark[a] = 0;
        }
    }

    return 0;

}

int check(int *sol, int n, int *best_sol, int *best_diff) {

    //variabili correnti
    int saldo = 0;
    int min_saldo = INT_MAX;
    int max_saldo = 0;

    for (int a=0; a<n; a++) {
        saldo += sol[a];

        if (saldo<min_saldo) {
            min_saldo=saldo;
        }
        if (saldo>max_saldo) {
            max_saldo=saldo;
        }
    }

    int diff = max_saldo-min_saldo;
    //stiamo minimizzando la differenza
    if (diff<*best_diff) {
        *best_diff=diff;
        for (int a=0; a<n; a++) {
            best_sol[a]=sol[a];
        }
        return 1;
    }
    return 0;
}