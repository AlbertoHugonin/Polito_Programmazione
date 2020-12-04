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


int main() {

    int n,k;
    //intero scelta
    int s;
    //numero soluzioni
    int total;

    //vettore di n interi dei valori possibili 
    int *val;
    //vettore k interi che memorizza la soluzione
    int *sol;
    //vettore n elementi inizializzato a zero perchè non sono utilizzati
    int *mark;

    char *val_c;
    char *sol_c;

    //indice per i for
    int i;

    //stampo menu
    printf("\n");
    printf("\n Calcolo Combinatorio\n");
    printf("===============\n");
    printf("1. Principio di moltiplicazione\n");
    printf("2. Disposizioni semplici\n");
    printf("3. Disposizioni ripetute\n");
    printf("4. Permutazioni semplici\n");
    printf("5. Anagrammi con ripetizione\n");
    printf("6. Anagrammi distinti con lettere ripetute\n");
    printf("7. Combinazioni semplici di n elementi presi k a k dove non conta l'ordine\n");
    printf("8. Combinazioni con ripetizione di n elementi");
    printf("9. Exit\n");
    printf("Selezionare : ");
    if(scanf("%d",&s)<=0) {
        printf("Solo interi!\n");
        exit(0);
    }
    else {
        //chiedi dati per i casi 2,3
        if (s==2 || s==3) {
            printf("Inserisci n: ");
            scanf("%d", &n);
            printf("Inserisci k: ");
            scanf("%d", &k);
            val = malloc(n * sizeof(int));
            sol = malloc(k * sizeof(int));
            for (i=0; i < k; i++) {
                sol[i]= -1;
            }
            for (i=0; i<n; i++) {
                printf("Inserisci elemento %d: ", i);
                scanf("%d", &val[i]);
                }
        }


        switch(s) {
        case 1:   //TO DO
                break;
        
        case 2:     mark = calloc(n, sizeof(int));
                    printf("Le disposizioni semplici di %d interi ", n);
                    for (i=0; i <n; i++)
                        printf("%d ", val[i]);
                    printf(" a %d a %d sono:\n", k, k);
                    total = disposizioni_semplici(val, mark, n, sol, k, 0, 0);
                    printf("e in totale sono %d \n", total);
                    free(mark);
                    break;
        
        case 3:     printf("Le disposizioni ripetute di %d interi ", n);
                    for (i=0; i <n; i++)
                        printf("%d ", val[i]);
                    printf("a %d a %d sono:\n", k, k);
                    total = disposizioni_ripetute(val, n, sol, k, 0, 0);
                    printf("e in totale sono %d \n", total);
                    break;
        
        case 4:     printf("Inserisci n: ");
                    scanf("%d", &n);
                    val = malloc(n * sizeof(int));
                    sol = malloc(n * sizeof(int));
                    mark = calloc(n, sizeof(int));
                    for (i=0; i < n; i++)
                        sol[i]= -1;
                    for (i=0; i<n; i++) {
                        printf("Inserisci elemento %d: ", i);
                        scanf("%d", &val[i]);
                    }
                    printf("Le permutazioni semplici di %d interi  ", n);
                    for (i=0; i <n; i++)
                        printf("%d ", val[i]);
                    printf("sono:\n");
                    total = permutazioni_semplici(val, mark, n, sol, 0, 0);
                    printf("e in totale sono %d \n", total);
                    free(mark);
                    break;
        
        case 5:     //anagrammi con ripetizione (perchè le lettere anche se uguali sono in realtà diverse)
                    printf("Inserisci numero lettere: ");
                    scanf("%d", &n);
                    val_c = malloc(n * sizeof(char));
                    sol_c = malloc(n * sizeof(char));
                    mark = calloc(n, sizeof(int));
                    printf("Inserisci parola: ");
                    //lo scanf con i vettori e puntatori dato che sono la stessa cosa non ha bisogno di &
                    scanf("%s", val_c);
                    printf("Gli anagrammi possibili della parola %s sono:\n", val_c);
                    total = anagrammi_con_ripetizione(val_c,mark,n,sol_c,0,0);
                    printf("e in totale sono %d \n", total);
                    free(mark);
                    break;
        case 6:     //generare a partire da una parola con lettere ripetute i suoi anagrammi distinti
                    printf("Inserisci numero lettere: ");
                    scanf("%d", &n);
                    val_c = malloc(n * sizeof(char));
                    sol_c = malloc(n * sizeof(char));

                    //vengono sopra allocati perchè non conosciamo il numero di elementi, passiamo poi n_dist che è il valore di elementi distinti
                    char *dist_val = malloc(n* sizeof(char));
                    int *mark = malloc(n* sizeof(char));

                    printf("Inserisci parola: ");
                    //lo scanf con i vettori e puntatori dato che sono la stessa cosa non ha bisogno di &
                    scanf("%s", val_c);

                    //ordiniamo il vettore val 
                    insertion_sort_char(val_c,n);
                    //contare gli elementi ripetuti del vettore e inserire solo le prime occorrenze nel vettore dist_val sopra allocato


                    //indice mark è uguale a dist val
                    int indice_mark = 0;
                    int indice_val = 0;

                    dist_val[indice_mark]=val_c[indice_val];
                    mark[indice_mark] = 1;
                    for (indice_val = 1; indice_val <= n; indice_val++) {
                        if (dist_val[indice_mark] == val_c[indice_val]) {
                            mark[indice_mark] += 1;
                            //printf("Lettera %c, ripetuta: %d volte\n", val[indice_val], mark[indice_mark]);
                        }
                        else {
                            indice_mark++;
                            dist_val[indice_mark] = val_c[indice_val];
                            mark[indice_mark] = 1;
                        }
                    }
                    // puts("Vettore Mark\n");
                    // for (int a=0; a<indice_mark; a++) {
                    //     printf("%d ", mark[a]);
                    //     fflush(stdout);
                    // }
                    // puts("\nVettore valori distinti\n");
                    // for (int a=0; a<indice_mark; a++) {
                    //     printf("%c ", dist_val[a]);
                    //     fflush(stdout);
                    // }
                    puts("\n");
                    permutazioni_ripetute(sol_c,n,dist_val,indice_mark,mark,0,0);
                    break;

        case 7:     //combinazioni semplici un esempio è il controllo delle lampadine
                    printf("Inserisci numero n: ");
                    scanf("%d", &n);
                    printf("Inserisci numero k: ");
                    scanf("%d", &k);
                    val = malloc(n * sizeof(int));
                    sol = malloc(k * sizeof(int));
                    for (int a=0; a<n; a++) {
                        printf("Inserisci elemento %d: ", a);
                        scanf("%d", &val[a]);
                    }
                    printf("I modi possibili di combinare %d numeri presi %d a %d sono:\n", n, k, k);
                    total = combinazioni_semplici(val,sol,n,k,0,0,0);
                    printf("E in totale sono %d \n", total);
                    free(mark);
                    break;
        case 8:     //combinazioni con ripetizione un esempio è il controllo delle lampadine
                    printf("Inserisci numero n: ");
                    scanf("%d", &n);
                    printf("Inserisci numero k: ");
                    scanf("%d", &k);
                    val = malloc(n * sizeof(int));
                    sol = malloc(k * sizeof(int));
                    for (int a=0; a<n; a++) {
                        printf("Inserisci elemento %d: ", a);
                        scanf("%d", &val[a]);
                    }
                    printf("I modi possibili di combinare %d numeri presi %d a %d sono:\n", n, k, k);
                    total = combinazioni_con_ripetizione(val,sol,n,k,0,0,0);
                    printf("E in totale sono %d \n", total);
                    break;
        default:    printf("Opzione non valida\n");
        }
  }
  return 0;
}


//n elementi presi a k a k dove non conta l'ordine quindi 1,2,3=3,2,1 perciò usiamo indice di partenza start che forza un solo ordinamento possibile
int combinazioni_semplici ( int *val, int *sol, int n, int k, int start, int pos, int count) {

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