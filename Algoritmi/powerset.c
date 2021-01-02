#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <calcolo_combinatorio.h>

int powerset_disposizioni_ripetute (int *val, int *sol, int n, int pos, int count);
int powerset_dividi_et_timpera (int *val, int *sol, int n, int start, int pos, int count);
void stampa_soluzione(int *sol, int pos);
void stampa_soluzione_disposizioni(int *val, int *sol, int n);
//utiliziamo il modello in calcolo_combinatorio.h
int powerset_combinazioni_semplici(int *val, int n);

int main() {

    int n,total = 0,i;

    printf("Inserisci il numero di elementi: ");
    scanf("%d", &n);
    int *val = malloc(n * sizeof(int));
    int *sol = malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        printf("Inserisci elemento %d: ", i+1);
        scanf("%d", &val[i]);
    }
    printf("Il powerset dell'insieme [ ");
    for (i = 0; i < n; i++)
        printf("%d ", val[i]);
    printf("] è:\n");

    puts("Con disposizioni ripetute:");
    total = powerset_disposizioni_ripetute(val,sol,n,0,total);
    printf("e in totale sono %d \n", total);
    total = 0;
    puts("Con dividi et timpera:");
    total = powerset_dividi_et_timpera(val,sol,n,0,0,total);
    printf("e in totale sono5 %d \n", total);
    total = 0;
    puts("Combinazioni semplici (k crescente):");
    total = powerset_combinazioni_semplici(val,n);
    printf("e in totale sono %d \n", total);

    return 0;
}

//start serve per evitare soluzioni simmetriche 
//parte dall'insieme completo e va all elemento vuoto
int powerset_dividi_et_timpera (int *val, int *sol, int n, int start, int pos, int count) {

    int i;

    if (start>=n) {
        stampa_soluzione(sol,pos);
        return count+1;
    }


    for (i=start; i<n; i++) {
        sol[pos] = val[i];
        //include l'elemento nei livelli successivi
        count = powerset_dividi_et_timpera(val,sol,n,i+1,pos+1,count);
    }
    //non include l'elemento, quindi scende di dimensione
    count = powerset_dividi_et_timpera(val,sol,n,n,pos,count);
    return count;
}

void stampa_soluzione(int *sol, int pos) {
    printf("{ ");
    for (int a=0; a<pos; a++) {
        printf("%d ", sol[a]);
    }
    puts("}");
}


//decidiamo elemento preso o elemento lasciato sol[pos] = 0 se non lo prendiamo 1 se lo prendiamo
//parte dall'insieme vuoto e sale fino all'insieme completo
int powerset_disposizioni_ripetute (int *val, int *sol, int n, int pos, int count) {

    if (pos>=n) {
        stampa_soluzione_disposizioni(val,sol,n);
        return count+1;
    }


    sol[pos] = 0;
    //non include l'elemento
    count = powerset_disposizioni_ripetute(val,sol,n,pos+1,count);
    //include l'elemento nei livelli successivi
    sol[pos] = 1;
    count = powerset_disposizioni_ripetute(val,sol,n,pos+1,count);
    return count;


}

void stampa_soluzione_disposizioni(int *val, int *sol, int n) {
    printf("{ ");
    for (int a=0; a<n; a++) {
        if (sol[a] != 0) {
            printf("%d ", val[a]);
        }
    }
    puts("}");
}


//non c'è il concetto di ordine, non c'è insieme vuoto quindi dobbiamo aggiungerlo noi, chiamiamo la funzione ricorsiva tante volete con k crescente
//molto utile per risolvere problemi di ottimizzazione sulla cardinalità
int powerset_combinazioni_semplici(int *val, int n) {

    int *sol = malloc(n *sizeof(int));
    
    int count = 1, i;
    //aggiungiamo insieme vuoto
    printf("{ }\n");

    for (i=1; i<=n; i++) {
        count += combinazioni_semplici(val,sol,n,i,0,0,count);
    }
    return count;
}


