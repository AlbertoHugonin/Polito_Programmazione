//modelli del calcolo combinatorio in c
#include <stdio.h>
#include <stdlib.h>

int disposizioni_semplici(int *val, int *mark, int n, int *sol, int k, int count, int pos);
int disposizioni_ripetute(int *val, int n, int *sol, int k, int count, int pos);
int permutazioni_semplici(int *val, int *mark, int n, int *sol, int count, int pos);
int anagrammi_con_ripetizione(char *val, int *mark, int n, char *sol, int count, int pos);

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
    printf("6. Exit\n");
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
                    char *val_c = malloc(n * sizeof(char));
                    char *sol_c = malloc(n * sizeof(char));
                    mark = calloc(n, sizeof(int));
                    printf("Inserisci parola:");
                    //lo scanf con i vettori e puntatori dato che sono la stessa cosa non ha bisogno di &
                    scanf("%s", val_c);
                    printf("Gli anagrammi possibili della parola %s sono:", val_c);
                    total = anagrammi_con_ripetizione(val_c,mark,n,sol_c,0,0);
                    printf("e in totale sono %d \n", total);
                    free(mark);
                    break;
        default:    printf("Opzione non valida\n");
        }
  }
  free(sol);
  free(val);
  return 0;
}

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

//ogni elemento pu' essere ripetuto fino a k volte
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
//basandosi sulle permutazioni semplici quindi ipotizzando che lettere uguali siano in realta diverse, non serve k perchè n=k
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
