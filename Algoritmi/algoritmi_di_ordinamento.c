#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 500

//variabile globale per ritornare il risultato
typedef struct {
    int scambi;
    int iterazioni_ciclo_esterno;
    int iterazioni_per_ciclo_interno;
    int num_totale_iterazioni;
} risultato;

//il vettore è diviso concettualmente in 2 parti, parte ordinata e parte disordinata. L'elemento iniziale è sempre ordinato, andiamo a crescere ad ogni interazione il vettore ordinato
//e diminuiamo quello non ordinato. Alla fine la parte non ordinata ha zero elementi. Ogni elemento lo confrontiamo con tutto il vettore ordinato e lo inseriamo al posto giusto mantenendo
//l'ordinamento (ad ogni ciclo while spostiamo il vettore a destra lasciando spazio per il nuovo elemento). 
//Andiamo quindi ad ingrandire ad ogni passaggo la parte odinata e ha produrre alla fine il vettore ordinato completamente
risultato insertion_sort(int V[], int n);

risultato insertion_sort(int V[], int n) {

    risultato res;

    res.scambi = 0;
    res.num_totale_iterazioni = 0;
    res.iterazioni_per_ciclo_interno = 0;
    res.iterazioni_ciclo_esterno = 0;

    int l = 0;     //estremo sinistro
    int r = n-1;   //estremo destro

    int elem_corrente;
    int j;

    //ciclo for e ciclo while interno T(n) = O(N^2) (caso peggiore se è ordinato al contrario)

    for (int i = l+1; i <= r; i++) {

        res.iterazioni_ciclo_esterno++;
        //i estremo destro parte ordinata, i=0 sempre ordinato
        elem_corrente = V[i];
        //indice elem precedente
        j = i - 1;

        //continua finche non si arriva all'inizio della parte ordinata o trova il posto dove mettere l'elemento, maggiore di V[j] se discendente
        while ( j >= l && elem_corrente < V[j]) {
            //se l'elemento corrente è minore dell'elemento arrivato da inserire allora lo scambio, ad ogni ciclo sposto il vettore a destra finche non trovo il posto
            res.scambi++;
            V[j+1] = V[j];
            j--;
        }
        //inseriscmo l'elemento al posto giusto
        V[j+1] = elem_corrente;
    }
    return res;
}
/* 

int main() {

    int V[N];

    //generazione vettore
    int i;
    srand(time(0));

    for (i=0; i<N; i++){
        V[i] = 1 + rand()%N;
    }

    insertion_sort(V, N);	

    return 0;
} */