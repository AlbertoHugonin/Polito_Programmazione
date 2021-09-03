#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>


void solve(char *target, part *P, int nParts);
void solveR( int *val, int *mark, int n, int *sol, int k, int pos, part *P, char *target, int *best_costo, int costo, int *best_sol, int *best_card);

int check(int *sol, int pos, part *P, char *target);

typedef struct {
char *s;
int pos;
int costo;
} part;



int main() {

    char target[7] = "persona";
    part parti[10] = {
    {"p", 0, 1}, // p0
    {"pers", 0, 5}, // p1
    {"er", 1, 4}, // p2
    {"ers", 1, 4}, // p3
    {"sa", 3, 1}, // p4
    {"so", 3, 2}, // p5
    {"ato", 0, 1}, // p6
    {"on", 4, 2}, // p7
    {"ona", 4, 3}, // p8
    {"a", 6, 1} // p9
    };

    solve(target,parti,10);
    return 0;
}

void solve(char *target, part *P, int nParts) {

    int *val = malloc(nParts*sizeof(int));
    
    for (int a=0; a<nParts; a++) {
    val[a] = a;
    }

    int *sol = malloc(strlen(target)*sizeof(int));
    int *mark = calloc(nParts,sizeof(int));
    int best_costo = INT_MAX; //ricordare di includere limits.h
    int costo = 0;
    int *best_sol = malloc(strlen(target)*sizeof(int));

    int best_card = strlen(target);

    solveR(val,mark,nParts,sol,strlen(target),0,P,target, &best_costo, costo, best_sol,&best_card);

    return;
}


//1 se non possiamo prenderlo
//0 se possiamo prenderlo
//2 se la soluzione è completa
int check(int *sol, int pos, part *P, char *target) {

    if (strlen(P[sol[pos]].s) > strlen (target)) {
        return 1;
    }

    char *stringa = P[sol[pos]].s;
    int inizio = P[sol[pos]].pos;

    int inizio_corrente;
    int lunghezza_corrente;

    //andiamo a vedere se la sottostringa è compatibile con parte della stringa iniziale
    for (int a=0; a<strlen(stringa); a++) {
        if (target[inizio+a] != stringa[a]) {
            return 1;
        }
    }

    //adesso vediamo se il posto era già occupato, questo controllo è meglio metterlo all'inizio
    int elem = strlen(target);
    
    for (int a=0; a<pos; a++) {

        inizio_corrente=P[sol[a]].pos;
        lunghezza_corrente=strlen(P[sol[a]].s)-1;

        elem -= lunghezza_corrente+1;
        
        if ((inizio >= inizio_corrente && inizio <= inizio_corrente + lunghezza_corrente) || (inizio+strlen(stringa)-1 >= inizio_corrente && inizio+strlen(stringa)-1 <= inizio_corrente + lunghezza_corrente)) {
            return 1;
        }
    }

    //abbiamo appurato che possiamo inserire questo elemento nella soluzione, adesso verifichiamo se esso genera la soluzione
    elem -= strlen(stringa);
    if (elem == 0) {
        return 2;
    }

    return 0;
}

//modello con disposizioni semplici
void solveR( int *val, int *mark, int n, int *sol, int k, int pos, part *P, char *target, int *best_costo, int costo, int *best_sol, int *best_card) {
    
    int i = 0;
    if (pos>=k) {
        //caso terminale se raggiunto soluzione non trovata
        printf("Soluzione Non Trovata");
    }

    for (i=0; i<n; i++) {

        if (mark[i] == 0) {
            //pruning, prima di prendere elemento vediamo se va bene se no lo saltiamo
            sol[pos] = val[i];
            int flag = check(sol,pos,P,target);

            if (flag== 0) {
                mark[i]=1;
                //sol[pos] contiene l'indice del vettore P dell'elemento preso
                sol[pos] = val[i];
                solveR( val,mark,n,sol,k,pos+1,P,target,best_costo,costo + P[sol[pos]].costo,best_sol,best_card);
                mark[i] = 0;
            }
            /////////////////parte gestione soluzione migliore
            if (flag == 2) {
                //significa che la soluzione è completa
                costo = costo + P[sol[pos]].costo;
                if (costo < *best_costo || pos+1<*best_card) {
                    *best_costo = costo;
                    *best_card=pos+1;
                    for (int a=0; a<k; a++) {
                        best_sol[a]=sol[a];
                        if (a>pos) {
                            best_sol[a]=-1;
                        }
                    }
                }
                return;
            }
        }
    }
    return;
}