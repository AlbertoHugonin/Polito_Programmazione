#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 500


//funzione wrapper per chiamate a algoritmi ricorsivi

int ordinamenti_ricorsivi (int v[], char id[], int n) {
    //possiamo gestire merge sort e quicksort in base al valore della stringa
     int *buff = (int *) malloc (n*sizeof (v));
     merge_sortR(v,buff, 0, n-1);
}

//variante del merge sort dove il vettore viene diviso in due parti ma di dimensioni diverse e il centro dell'algoritmo sta nella divisione
void quick_sort(int v[], int l, int r) {
    
    if (r<=l) {
        //condizione di terminazione, 1 elemento o 0 elementi è un vettore ordinato
        return;
    }
    //dato il vettore v e i suoi estremi viene partizionato in due parti di dimensioni diverse, con q elemento pivot di mezzo, la scelta del pivot non cambia il caso medio, ma cambia il possibile caso peggiore
    int q = partition(v,l,r);
    //chiamata funzione ricorsiva per ciascuna parte del vettore
    quick_sort(v,l,q-1);
    quick_sort(v,q+1, r);
}

//centro dell
int partition(int v[], int l, int r) {

    //facciamo prima incrementi poi leggiamo quindi i è valido
    int i = l-1;
    int j = r;
    int x = v[r];
    //ciclo infinito
    for (; ;) {
        //ciclo che sale che trova il primo elemento maggiore di x
        while(v[++i] < x);
        //ciclo che scende che trova il primo elemento minore di x
        while(v[--j] > x) {
            //identifichiamo quindi una coppia di elementi fuori posto che deve essere scambiata

            if ( j == l)
                //significa che abbiamo iterato su tutti gli elementi dei sottovettori
                break;
            if ( i >= j)
                //se i scavalca j allora esco
                break;
            
            //adesso scambio gli elementi
            swap(v,i,j);
        }
        swap(v,i,r);
        return i;
    }
}

void merge_sortR(int v[], int buff[], int l, int r) {
    //indice di mezzo
    int q = (l+r)/2;
    if (r <= l)
        return;
    //una chiamata per ciascun ramo
    merge_sortR(v,buff,l,q);
    merge_sortR(v,buff,q+1,r);
    //chiamiamo la merge che si occupa della ricombinazione quindi dell'unione di due sottovettori ordinati in uno ordinato 
    merge(v,buff,l,q,r);
}


//funzione ricombinazione della merge_sort
void merge(int v[], int buff[], int l, int q, int r) {

    //ha bisogno di indice i che punta al primo elemento del sottovettore sinistro
    //indice j che punta al primo elemento del sottovettore destro
    int i = l;
    int j = q+1;
    //iteriamo tutti gli elementi del sottovettore risultato
    for (int k = l; k<=r; k++) {
        // abbiamo 3 casi diversi da gestire
        if (i > q) {
            //vettore sinistro finito (indice i scavalca indice q) riempio con il sottovettore destro
            buff[k] = v[j++];
        }
        else {
            if (j>r) {
                //finito il sottovettore destro (indice destro scavalca l'estremo destro) prendiamo da quello sinistro
                buff[k] = v[i++];
            }
            //nel caso non avessimo finito nessuno dei due vettori dobbiamo confrontare i due elementi
            if (v[i] <= v[j]) {
                //elemento sinistro minore o uguale elemento destro -> prendiamo elemento sinistro
                buff[k] = v[i++];
            }
            else {
                //elemento destro minore o uguale di elemento sinistro -> prendiamo elemento destro
                buff[k] = v[j++];
            }
        }
    }
    //ricostruiamo la soluzione
    for (int k=l; k<=r; k++) {
        v[k] = buff[k];
    }
    return;
}