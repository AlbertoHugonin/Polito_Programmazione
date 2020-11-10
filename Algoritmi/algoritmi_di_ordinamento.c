#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 500

//variabile globale per ritornare il risultato, da mettere sempre per prima
typedef struct {

    int scambi;
    int iterazioni_ciclo_esterno;
    int iterazioni_per_ciclo_interno[N];
    int num_totale_iterazioni;
    int V[N];

} risultato;

//il vettore è diviso concettualmente in 2 parti, parte ordinata a sinistra e parte disordinata a destra. L'elemento iniziale è sempre ordinato, andiamo a crescere ad ogni interazione il vettore ordinato
//e diminuiamo quello non ordinato. Alla fine la parte non ordinata ha zero elementi. Ogni elemento lo confrontiamo con tutto il vettore ordinato e lo inseriamo al posto giusto mantenendo
//l'ordinamento (ad ogni ciclo while spostiamo il vettore a destra lasciando spazio per il nuovo elemento). 
risultato insertion_sort(int v[], int n);

//il vettore è diviso in parte ordinata a destra (inizialmente uguale a 0), e parte disordinata a sinistra (inizialemente uguale a N).
//Il ciclo esterno itera per ogni elemento del vettore, il ciclo interno pure ed è quello che effettua gli scambi portando a destra o facendo affondare gli elementi piu' grandi
risultato bubble_sort(int v[], int n);


risultato selection_sort(int v[], int n);


risultato shell_sort(int v[], int n);

//inizializzazione delle variabili principali
risultato initializer();


risultato initializer() {
    
    risultato res;

    res.scambi = 0;
    res.num_totale_iterazioni = 0;
    res.iterazioni_ciclo_esterno = 0;
    return res;
}


risultato bubble_sort(int v[], int n) {

    risultato res = initializer();

    //copia dell'array per non modificare quello di partenza
    for (int a=0; a<n; a++) {
        res.V[a] = v[a];
    }

    //inizio algoritmo
    int l = 0, r = n-1, tmp;
    //ciclo esterno dall'inizio della parte disordinata
    for (int i=l; i<r; i++) {
        //ciclo dall'inizio parte disordinata a inizio parte ordinata
        res.iterazioni_per_ciclo_interno[i-l] = 0;
        res.num_totale_iterazioni++;
        res.iterazioni_ciclo_esterno++;
        for (int b=l; b<r-i+l; b++) {
            res.num_totale_iterazioni++;
            res.iterazioni_per_ciclo_interno[i-l]++;
            //se l'elemento corrente è maggiore dell'elemento successivo lo scambia, al giro dopo lo riprende e fa la stessa cosa con l'elemento successivo ancora,
            //r-i+1 rappresenta gli elementi l'inizio degli elementi già ordinati.
            if (res.V[b] > res.V[b+1]) {
                res.scambi++;
                tmp = res.V[b];
                res.V[b] = res.V[b+1];
                res.V[b+1] = tmp;
            }
        
        }
    }
    return res;
}

risultato insertion_sort(int v[], int n) {

    risultato res = initializer();

    //copia dell'array per non modificare quello di partenza
    for (int a=0; a<n; a++) {
        res.V[a] = v[a];
    }

    int l = 0;     //estremo sinistro
    int r = n-1;   //estremo destro

    int elem_corrente;
    int j;

    //ciclo for e ciclo while interno T(n) = O(N^2) (caso peggiore se è ordinato al contrario)
    res.iterazioni_per_ciclo_interno[0] = 0;
    for (int i = l+1; i <= r; i++) {
        res.iterazioni_per_ciclo_interno[i-l] = 0;
        res.iterazioni_ciclo_esterno++;
        res.num_totale_iterazioni++;
        //i estremo destro parte ordinata, i=0 sempre ordinato
        elem_corrente = res.V[i];
        //indice elem precedente
        j = i - 1;

        //continua finche non si arriva all'inizio della parte ordinata o trova il posto dove mettere l'elemento, maggiore di V[j] se discendente
        while ( j >= l && elem_corrente < res.V[j]) {
            //se l'elemento corrente è minore dell'elemento arrivato da inserire allora lo scambio, ad ogni ciclo sposto il vettore a destra finche non trovo il posto
            res.iterazioni_per_ciclo_interno[i-l]++;   
            res.scambi++;
            res.num_totale_iterazioni++;
            res.V[j+1] = res.V[j];
            j--;
        }
        //inseriscmo l'elemento al posto giusto nel vettore ordinato
        res.V[j+1] = elem_corrente;
    }
    return res;
}

risultato selection_sort(int v[], int n) {

    risultato res = initializer();

    //copia dell'array per non modificare quello di partenza
    for (int a=0; a<n; a++) {
        res.V[a] = v[a];
    }

    int l = 0;     //estremo sinistro
    int r = n-1;   //estremo destro

    //indice del minimo
    int min;
    int j;
    int tmp;

    for (int i=l; i<r; i++) {
        min = i;
        res.iterazioni_per_ciclo_interno[i-l] = 0;
        res.num_totale_iterazioni++;
        res.iterazioni_ciclo_esterno++;

        //trovare l'indice del minimo nella parte disordinata
        for (j=i+1; j<=r; j++) {
            res.num_totale_iterazioni++;
            res.iterazioni_per_ciclo_interno[i-l]++;
            if (res.V[j] < res.V[min]) {
                min = j;
            }
        }
        res.scambi++;
        tmp = res.V[i];
        res.V[i] = res.V[min];
        res.V[min] = tmp;
    }

    return res;

}


risultato shell_sort(int v[], int n) {

    risultato res = initializer();

    //copia dell'array per non modificare quello di partenza
    for (int a=0; a<n; a++) {
        res.V[a] = v[a];
    }

    int l = 0;     //estremo sinistro
    int r = n-1;   //estremo destro

    int h = 1;
    int j;
    int tmp;

    //da finire

}

risultato counting_sort(int v[], int n, int k) {

    risultato res = initializer();

    //copia dell'array per non modificare quello di partenza
    for (int a=0; a<n; a++) {
        res.V[a] = v[a];
    }

    int i;
    int *B, *C;

    //vettore inizializzazione
    for (i=0; i<k; i++) {
        C[i] = 0;
    }

    //vettore occorrenze semplici
    for (i=0; i<k; i++) {

        //posizione numero, sommiamo al valore già presente
        C[v[i]]++;
    }

    //vettore occorrenze multiple
    for (i=0; i<k; i++) {
        C[i] += C[i-1];
    }

    //ciclo principale da destra verso sinistra per mantenere la stabilità
    for (i=n; i>=0; i--) {
        B[C[v[i]]-1] = v[i];
        C[v[i]]--;
    }

    


}

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
    merge_sortR(v,buff,l,q);
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
                //elemento sinistro minore o uguale elemento destro -> prendiamo elemento sinitro
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


