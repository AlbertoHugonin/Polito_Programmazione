#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int v; int w; int wt; } Edge;
int combinazioni_semplici ( int *val, int *sol, int n, int k, int start, int pos, int count, Edge *lista, int *vertici, int nv);
int powerset_combinazioni_semplici(int *val, int n, Edge *lista, int *vertici, int nv);
int insert_vett(int v, int *vertici, int Nv);
int controllo_albero(int *sol, Edge *lista, int n, int k, int *vertici, int nv);

int main() {

    FILE *archi = fopen("archi.txt","r");
    int N = 0;
    int Nv = 7;
    //allocare in eccesso tabella archi
    Edge *edges = malloc(10*sizeof(Edge));
    int *vertici = malloc(Nv*sizeof(int));

    for (int a=0; a<Nv; a++) {
        vertici[a] = -1;
    }

    while(fscanf(archi,"%d %d %d ", &edges[N].v, &edges[N].w, &edges[N].wt) != EOF) {
        insert_vett(edges[N].v,vertici,Nv);
        insert_vett(edges[N].w,vertici,Nv);
        N++;
    }

    int val[] = {0,1,2,3,4,5,6,7,8,9};

    powerset_combinazioni_semplici(val,N,edges,vertici,Nv);
    return 0;

}

int insert_vett(int v, int *vertici, int Nv) {
    for (int a=0; a<Nv; a++) {
        if(vertici[a] == v) {
            return 1;
        }
        if(vertici[a] ==-1) {
            vertici[a]=v;
            return 0;
        }
    }
}

//non c'è il concetto di ordine, non c'è insieme vuoto quindi dobbiamo aggiungerlo noi, chiamiamo la funzione ricorsiva tante volete con k crescente
//molto utile per risolvere problemi di ottimizzazione sulla cardinalità
int powerset_combinazioni_semplici(int *val, int n, Edge *lista, int *vertici, int nv) {

    int *sol = malloc(n *sizeof(int));
    
    int count = 1, i;

    for (i=1; i<=n; i++) {
        count += combinazioni_semplici(val,sol,n,i,0,0,count,lista,vertici,nv);
    }
    return count;
}

//n elementi presi a k a k dove non conta l'ordine quindi 1,2,3=3,2,1 perciò usiamo indice di partenza start che forza un solo ordinamento possibile
int combinazioni_semplici ( int *val, int *sol, int n, int k, int start, int pos, int count, Edge *lista, int *vertici, int nv) {

    int i;

    if (pos >= k) {
        // for (i=0; i<k; i++) {
        //     printf("%d ", sol[i]);
        // }
        // puts("\n");
        //controllo se soluzione compre intero grafo
        controllo_albero(sol,lista,n,k,vertici,nv);
        return count+1;
    }

    for (i=start; i<n; i++) {
        //prima di prendere controlliamo se arco sicuro
        //dentro sol[pos] contenuta la scelta dell'arco da prendere
        //controlliamo se arco unisce due alberi o no
        if (k != 0) {
            int flag = 0;
            
        }
        sol[pos] = val[i];
        //le scelte che precedono l'indice start non sono piu' disponibili cosi da forzare l'ordine
        count = combinazioni_semplici(val,sol,n,k,i+1,pos+1,count,lista,vertici,nv);
    }
    return count;
}

//k lunghezza sol, n lunghezza lista archi, nv lunghezza vettore vertici
int controllo_albero(int *sol, Edge *lista, int n, int k, int *vertici, int nv) {
    //bisogna guardare che sia ricoprente e di costo minimo
    //check che sia ricoprente
    int *vertici_sol = malloc(nv*sizeof(int));

    for (int a=0; a<nv; a++) {
        vertici_sol[a] = -1;
    }
    for (int pos=0; pos<k; pos++) {
        insert_vett(lista[sol[pos]].v,vertici_sol,nv);
        insert_vett(lista[sol[pos]].w,vertici_sol,nv);
    }
    //adesso andiamo a verificare che i vettori contengano lo stesso numero di vertici
    int n_1 = 0;
    int n_2 = 0;
    for (int a=0; a<nv; a++) {
        if (vertici_sol[a] != -1) {
            n_1++;
        }
        if (vertici[a] != -1) {
            n_2++;
        }
    }
    if (n_1==n_2) {
         for (int i=0; i<k; i++) {
             printf("%d ", sol[i]);
         }
         puts("\n");
    }

}