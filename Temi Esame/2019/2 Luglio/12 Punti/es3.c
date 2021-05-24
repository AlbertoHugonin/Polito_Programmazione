#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//modello del calcolo del powerset con disposizioni ripetute
int powerset_disposizioni_ripetute (int *val, int *sol, int n, int pos, int count, int *n_best, int *best_sol);
//verifica la validità della soluzione e ritorna la sua lunghezza, ritorna -1 se non valida, >= 0 se valida
int valida_soluzione(int *val, int *sol, int n);


int main() {

    int N = 9; 
    //dato dalla consegna
    int V[] = {4, 2, 5, 9, 7, 6, 10, 3, 1};


    int *sol = malloc(N*sizeof(int));
    int *best_sol = malloc(N*sizeof(int));

    int n_best = 0;
    int count = powerset_disposizioni_ripetute(V,sol,N,0,0,&n_best,best_sol);
    printf("Soluzioni Valide trovate: %d\n", count);
    printf("Lunghezza soluzione migliore: %d\n", n_best);
    printf("Una delle soluzioni migliori: ");

    for (int a=0; a<N; a++) {
        if (best_sol[a] == 1) {
            printf("%d ", V[a]); 
        }
    }
    puts("");
    return count;

}

int valida_soluzione(int *val, int *sol, int n) {

    int *sol_c = malloc(n*sizeof(int));

    //riferimento nel vettore sol_c, soluzione "vera"
    int indice = 0;

    //generiamo il vettore risultante a partire dalla soluzione, lo facciamo per comodità
    for (int a=0; a<n; a++) {
        if (sol[a] == 1) {
            sol_c[indice] = val[a];
            indice++;
        }
    }

    //indica l'ordinamento attuale, 0 per crescente, 1 per decrescente
    int ord = 0;

    //prima della verifica abbiamo 512 soluzioni possibili
    //adesso controlliamo con che ordinamento inizia la soluzione
    if (sol_c[1] < sol_c[0]) {
        //ordinamento descrescente
        ord = 1;
    }

    //indica il numero di cambi di ordinamento che abbiamo fatto, se maggiore di uno scartiamo la soluzione
    int n_cambi = 0;

    //adesso iteriamo su tutto il resto della soluzione controllando quante volte cambia l'ordinamento
    for (int a=1; a<indice-1; a++) {

        //ordinamento decrescente o rimane uguale
        if (sol_c[a] >= sol_c[a+1]) {
            //se l'ordinamento era crescente allora aumentiamo il numero n_cambi
            if (ord == 0) {
                n_cambi++;
            }
            //aggiorniamo l'ordinamento corrente
            ord = 1;
        }
        else {
            //ordinamento crescente
            //se siamo arrivati da un ordinamento decrescente incrementiamo il numero di cambi
            if (ord == 1) {
                n_cambi++;
            }
            //aggiorniamo l'ordinamento corrente
            ord = 0;
        }
        //se n_cambi è maggiore di uno allora dobbiamo scartare la soluzione
        if (n_cambi > 1) {
            return -1;
        }
    }

    //ritorniamo la lunghezza della soluzione se valida > 0
    return indice;
    //notiamo come questa operazione di verifica non scarta le soluzioni solo crescenti e neanche quelle solo decrescenti, scarta solo quelle che cambiano
}

int powerset_disposizioni_ripetute (int *val, int *sol, int n, int pos, int count, int *n_best, int *best_sol) {

    if (pos>=n) {

        int lunghezza = valida_soluzione(val,sol,n);
        if (lunghezza == -1) {
            //se la lunghezza è uguale a 0 non è una soluzione valida
            return count;
        }
        else {
            //stampiamo per prova ogni singola soluzione trovata
            for (int a=0; a<n; a++) {
                if (sol[a] == 1) {
                    printf("%d ", val[a]); 
                }
            }
            puts("");

            //se è soluzione ottima aggiorniamo l'intero n_best e il vettore best_sol
            if (lunghezza >= *n_best) {
                *n_best = lunghezza;
                //attenzione che memcpy opera sul numero di byte quindi dobbiamo moltiplicare per sizeof(int)
                memcpy(best_sol,sol,n*sizeof(int));
            }
        
        return count+1;
        }
    }


    sol[pos] = 0;
    //non include l'elemento
    count = powerset_disposizioni_ripetute(val,sol,n,pos+1,count,n_best,best_sol);
    //include l'elemento nei livelli successivi
    sol[pos] = 1;
    count = powerset_disposizioni_ripetute(val,sol,n,pos+1,count,n_best,best_sol);
    return count;


}
