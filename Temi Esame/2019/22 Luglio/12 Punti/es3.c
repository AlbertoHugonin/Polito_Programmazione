#include <stdio.h>
#include <stdlib.h>

void stampa_soluzione_disposizioni(int *val, int *sol, int n, int *best_sol, int *best_length);
int powerset_disposizioni_ripetute (int *val, int *sol, int n, int pos, int count, int *best_sol, int *best_length);

int main() {

    int V[] = {8,9,6,4,5,7,3,2,4};
    int N=9;
    int *sol = malloc(N * sizeof(int));
    int *best_sol = malloc(N*sizeof(int));
    int *best_length = malloc(sizeof(int));
    *best_length = 0;
    printf("Soluzioni Valide:\n");
    powerset_disposizioni_ripetute(V,sol,N,0,0,best_sol,best_length);
    printf("---------------------------\nSoluzioni Migliore\n");
    //stampiamo la soluzione migliore
    printf("{ ");
    for (int a=0; a<*best_length; a++) {
        printf("%d ", best_sol[a]);
    }
    puts("}");
    printf("Soluzione di lunghezza: %d\n", *best_length);
}


//decidiamo elemento preso o elemento lasciato sol[pos] = 0 se non lo prendiamo 1 se lo prendiamo
//parte dall'insieme vuoto e sale fino all'insieme completo
int powerset_disposizioni_ripetute (int *val, int *sol, int n, int pos, int count, int *best_sol, int *best_length) {

    if (pos>=n) {
        stampa_soluzione_disposizioni(val,sol,n,best_sol,best_length);
        return count+1;
    }


    sol[pos] = 0;
    //non include l'elemento
    count = powerset_disposizioni_ripetute(val,sol,n,pos+1,count,best_sol,best_length);
    //include l'elemento nei livelli successivi
    //pruning credo da inserire qui perchè se sto per prendere un elemente puo' non essere valido
    sol[pos] = 1;
    count = powerset_disposizioni_ripetute(val,sol,n,pos+1,count,best_sol,best_length);
    return count;


}

void stampa_soluzione_disposizioni(int *val, int *sol, int n, int *best_sol, int *best_length) {

    //si puo' introdurre del pruning runtime
    //controlliamo se sono alternativamente maggiore minore
    int corrente;
    int flag = 0;
    //utilizzato anche per risparmiare memoria come contatore
    int primo = 0;
    for (int a=0; a<n; a++) {
        if (sol[a] != 0) {
            if(primo==0) {
                corrente=val[a];
                primo=1;
            } else {
                if (flag == 0) {
                    //deve essere maggiore del precedente
                    if(val[a] < corrente) {
                        //non decresce
                        return;
                    } else {
                        flag=1;
                        corrente=val[a];
                        primo++;
                    }
                } else {
                    if(val[a] > corrente) {
                        return;
                    } else {
                        flag=0;
                        corrente=val[a];
                        primo++;
                    }
                }
            }
        }
    }
    
    //la soluzione è valida stampiamola
    if (primo>*best_length) {
        *best_length=primo;
    }
    printf("{ ");
    //sempre per risparmiare memoria lo usiamo anche come contatore qui;
    primo=0;
    for (int a=0; a<n; a++) {
        if (sol[a] != 0) {
            best_sol[primo] = val[a];
            primo++;
            printf("%d ", val[a]);
        }
    }
    puts("}");
}