//modelli del calcolo combinatorio in c
#include <stdio.h>
#include <stdlib.h>
#include <algoritmi_di_ordinamento.c>

int disposizioni_semplici(int *val, int *mark, int n, int *sol, int k, int count, int pos);
int disposizioni_ripetute(int *val, int n, int *sol, int k, int count, int pos);
int permutazioni_semplici(int *val, int *mark, int n, int *sol, int count, int pos);
int anagrammi_con_ripetizione(char *val, int *mark, int n, char *sol, int count, int pos);

int permutazioni_ripetute (char *sol, int n, char *dist_val, int n_dist, int *mark, int pos, int count);
int combinazioni_semplici (int *val, int *sol, int n, int k, int start, int pos, int count);
int combinazioni_con_ripetizione ( int *val, int *sol, int n, int k, int start, int pos, int count);


//n elementi presi a k a k dove non conta l'ordine quindi 1,2,3=3,2,1 perciò usiamo indice di partenza start che forza un solo ordinamento possibile
int combinazioni_semplici ( int *val, int *sol, int n, int k, int start, int pos, int count) {

    int i;

    if (pos >= k) {
        printf("{ ");
        for (i=0; i<k; i++) {
            printf("%d ", sol[i]);
        }
        puts("}");
        return count+1;
    }

    for (i=start; i<n; i++) {
        sol[pos] = val[i];
        //le scelte che precedono l'indice start non sono piu' disponibili cosi da forzare l'ordine
        count = combinazioni_semplici(val,sol,n,k,i+1,pos+1,count);
    }
    return count;
}

//n elementi presi a k a k dove non conta l'ordine quindi 1,2,3=3,2,1 perciò usiamo indice di partenza start che forza un solo ordinamento possibile ma
//lo incrementiamo dopo la chiamata ricorsiva per permettere ripetizione
int combinazioni_con_ripetizione ( int *val, int *sol, int n, int k, int start, int pos, int count) {

    int i;

    if (pos >= k) {
        for (i=0; i<k; i++) {
            printf("%d ", sol[i]);
        }
        puts("\n");
        return count+1;
    }

    for (i=start; i<n; i++) {
        sol[pos] = val[i];
        //le scelte che precedono l'indice start non sono piu' disponibili cosi da forzare l'ordine
        count = combinazioni_semplici(val,sol,n,k,start,pos+1,count);
        start++;
    }
    return count;
}

//anagrammi distinti con lettere ripetute, le lettere vengono prese massimo n_dist numero di volte, dist_val è il vettore di valori tutti distinti
//sono ripetute ma non ci sono soluzioni uguali
int permutazioni_ripetute (char *sol, int n, char *dist_val, int n_dist, int *mark, int pos, int count) {

    int i = 0;

    //condizione di terminazione, vogliamo raggiungere una soluzione di n elementi
    if (pos >= n) {
        for (i=0; i<n; i++) {
            printf("%c ", sol[i]);
        }
        puts("\n");
        //incrementiamo il numero di soluzioni
        return count+1;
    }

    for (i=0; i<n_dist; i++) {
        if (mark[i] > 0) {
            mark[i]--;
            sol[pos] = dist_val[i];
            count = permutazioni_ripetute(sol,n,dist_val,n_dist,mark,pos+1,count);
            mark[i]++;
        }
    }

    return count;
}



//campioni ordinati di dimensione K, estratti da N senza reinserimento, ciascun elemento è distinto quindi abbiamo bisogno di un vettore mark di n elementi
//e vettore di solzuoni di dimensione k, la condizione di terminazione è pos nel vettore sol >= k, marchiamo gli elementi già presi, se elemento non marcato lo prendiamo
//  Numero soluzioni:  n!/n-k!
//campioni ordinati di dimensione k senza reinserimento estratti da N 

int disposizioni_semplici(int *val, int *mark, int n, int *sol, int k, int count, int pos) {
    //indice per i cicli interni
    int i = 0;
    //condizione di terminazione, livello ricorsione maggiore del numero di k quindi la soluzione è completa
    if (pos>=k) {
        printf("[");
        for (i=0; i<k; i++) {
            printf(" %d ", sol[i]);
        }
        printf("]");
        printf("\n");
        return count+1;
    }
    //centro dell'algoritmo
    //andiamo a iterare su tutte le possibili scelte
    for (i=0; i<n; i++) {
        //applichiamo il filtro per evitare ripetizioni all'interno della stessa soluzione
        if (mark[i] == 0) {
            mark[i] = 1;
            //la soluzione al posto pos (livello ricorsione) è uguale al valore al posto i
            sol[pos] = val[i];
            count = disposizioni_semplici(val,mark,n,sol,k,count,pos+1);
            //al livello pos = 0 si hanno a disposizione tutti gli elementi, la chiamata sottostante con pos = 1 non puo' prendere di nuovo quello che è stato scelto
            //prima per evitare ripetizioni
            mark[i]= 0;
        }
    }
    return count;
}


//ogni elemento può essere ripetuto fino a k volte, con k anche >= n, non serve il vettore mark, il vettore soluzione ha dimensione n e le possibili disposizioni sono n^k
//pos indica la profondità della ricorsione, count il numero di soluzioni
//il for itera su tutti gli elementi, la prima soluzione prende sempre k volte il primo elemento del vett val....
int disposizioni_ripetute(int *val, int n, int *sol, int k, int count, int pos) {
    //indice per i cicli interni
    int i = 0;
    //condizione di terminazione, livello ricorsione maggiore del numero di k quindi la soluzione è completa
    if (pos>=k) {
        printf("[");
        for (i=0; i<k; i++) {
            printf(" %d ", sol[i]);
        }
        printf("]");
        printf("\n");
        return count+1;
    }
    //centro dell'algoritmo
    //andiamo a iterare su tutte le possibili scelte
    for (i=0; i<n; i++) {
            //la soluzione al posto pos (livello ricorsione) è uguale al valore al posto i
            sol[pos] = val[i];
            count = disposizioni_ripetute(val,n,sol,k,count,pos+1);
            //al livello pos = 0 si hanno a disposizione tutti gli elementi, la chiamata sottostante con pos = 1 non puo' prendere di nuovo quello che è stato scelto
            //prima per evitare ripetizioni
    }
    return count;
}

//come le disposizioni semplici con n=k, serve sempre il vettore mark perchè non ci devono essere ripetizioni
//estraggo tutti gli elementi n senza reinserimento
int permutazioni_semplici(int *val, int *mark, int n, int *sol, int count, int pos) {
    //indice per i cicli interni
    int i = 0;
    //condizione di terminazione, livello ricorsione maggiore del numero di k quindi la soluzione è completa
    if (pos>=n) {
        printf("[");
        for (i=0; i<n; i++) {
            printf(" %d ", sol[i]);
        }
        printf("]");
        printf("\n");
        return count+1;
    }
    //centro dell'algoritmo
    //andiamo a iterare su tutte le possibili scelte
    for (i=0; i<n; i++) {
        //applichiamo il filtro per evitare ripetizioni all'interno della stessa soluzione
        if (mark[i] == 0) {
            mark[i] = 1;
            //la soluzione al posto pos (livello ricorsione) è uguale al valore al posto i
            sol[pos] = val[i];
            count = permutazioni_semplici(val,mark,n,sol,count,pos+1);
            //al livello pos = 0 si hanno a disposizione tutti gli elementi, la chiamata sottostante con pos = 1 non puo' prendere di nuovo quello che è stato scelto
            //prima per evitare ripetizioni
            mark[i]= 0;
        }
    }
    return count;
}
//basandosi sulle permutazioni semplici quindi ipotizzando che lettere uguali siano in realta diverse (lettere distinte) quindi non devo 
//riprenderle piu' di una volta, non serve k perchè n=k
//non le prendo piu' di una volta ma possono esserci soluzioni uguali
int anagrammi_con_ripetizione(char *val, int *mark, int n, char *sol, int count, int pos) {
//indice per i cicli interni
    int i = 0;
    //condizione di terminazione, livello ricorsione maggiore del numero di k quindi la soluzione è completa
    if (pos>=n) {
        sol[pos] = '\0';
        printf("%s\n", sol);
        return count+1;
    }
    //centro dell'algoritmo
    //andiamo a iterare su tutte le possibili scelte
    for (i=0; i<n; i++) {
        //applichiamo il filtro per evitare ripetizioni all'interno della stessa soluzione
        if (mark[i] == 0) {
            mark[i] = 1;
            //la soluzione al posto pos (livello ricorsione) è uguale al valore al posto i
            sol[pos] = val[i];
            count = anagrammi_con_ripetizione(val,mark,n,sol,count,pos+1);
            //al livello pos = 0 si hanno a disposizione tutti gli elementi, la chiamata sottostante con pos = 1 non puo' prendere di nuovo quello che è stato scelto
            //prima per evitare ripetizioni
            mark[i]= 0;
        }
    }
    return count;
}