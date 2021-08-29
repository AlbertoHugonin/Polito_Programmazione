#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4

//trovare tutti i sottoinsiemi tale che la somma degli elementi faccia X
//approccio già con pruning
void disposizioni_ripetute(int *sol, int *val, int n, int pos, int somma, int x);

int main() {

    int S[N] = {2,1,6,4};
    int X = 7;

    int *sol = malloc(N*sizeof(int));

    disposizioni_ripetute(sol,S,N,0,0,X);
    return 0;
}

void disposizioni_ripetute(int *sol, int *val, int n, int pos, int somma, int x) {

    if (pos>=n) {
        if (somma == x) {
            //stampo soluzione
            for (int a=0; a<n; a++) {
                if (sol[a] == 1 ) {
                    printf("%d ", val[a]);
                }
            }
            puts("");
            return;
        }
        return;
    }

    sol[pos] = 1;
    somma += val[pos];
    if (somma>x) {
        return;
    }

    disposizioni_ripetute(sol,val,N,pos+1,somma,x);

    sol[pos] = 0;
    somma -= val[pos];
    disposizioni_ripetute(sol,val,N,pos+1,somma,x);
    return;
}

//soluzione con pruning attraverso valutazione della speranza
void disposizioni_ripetute_con_pruning(int *sol, int *val, int n, int pos, int somma, int x) { 



}