#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//lunghezza nastro
#define N 4

int powerset_disposizioni_ripetute (int *sol, int n, int pos, int count, int *lunghezza, int *prezzo, int *best_val, int *best_sol);

int main() {

    //numero diverse lunghezze di cui posso tagliare il nastro
    int m=8;
    //un pezzo di lunghezza 7 costa 17, 4 costa 9, 8 costa 20 e cosi' via
    //ciascun elemento del vettore è >= 1 e <= a n
    int lunghezza[N] = {4,3,2,1};
    int prezzo[N] = {9,8,5,1};


    int *best_sol = malloc((N-1)*sizeof(int));
    int *sol = malloc((N-1)*sizeof(int));
    int best_val = 0;

    powerset_disposizioni_ripetute(sol,N-1,0,0,lunghezza,prezzo,&best_val,best_sol);
    //la soluzione ha costo 10 e divide il nastro in due parti uguali in mezzo
    return 0;
}

//decidiamo elemento preso o elemento lasciato sol[pos] = 0 se non lo prendiamo 1 se lo prendiamo
//parte dall'insieme vuoto e sale fino all'insieme completo
int powerset_disposizioni_ripetute (int *sol, int n, int pos, int count, int *lunghezza, int *prezzo, int *best_val, int *best_sol) {

    if (pos>=n) {
        //calcoliamo il costo
        //in sol è contenuto l'indice di dove mettere il taglio
        int length = 1;
        int costo = 0;
        for (int a=0; a<n; a++) {
            if(sol[a]==1) {
                //vuol dire che c'è un taglio, se il taglio è in a=1 allora tutti quelli prima fino a 
                for (int b=0; b<n+1; b++) {
                    if (lunghezza[b]==length) {
                        costo += prezzo[b];
                        break;
                    }
                }
                length=1;
                continue;
            }
            length++;
        }
        //analizziamo l'ultimo taglio
        for (int b=0; b<n+1; b++) {
            if (lunghezza[b]==length) {
                costo += prezzo[b];
                break;
            }
        }
        if(costo>*best_val) {
            *best_val=costo;
            for (int b=0; b<n; b++) {
                best_sol[b] = sol[b];
            }
        }
        return count+1;
    }


    sol[pos] = 0;
    //non include l'elemento
    count = powerset_disposizioni_ripetute(sol,n,pos+1,count,lunghezza,prezzo,best_val,best_sol);
    //include l'elemento nei livelli successivi
    sol[pos] = 1;
    count = powerset_disposizioni_ripetute(sol,n,pos+1,count,lunghezza,prezzo,best_val,best_sol);
    return count;


}