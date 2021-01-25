#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arco_ {
    int u;
    int v;
} arco;

int powerset_disposizioni_ripetute (int *val, int *sol, int n, int pos, int count, arco *archi);
int check_vertice(int *sol, int *val, arco *archi, int n);
void stampa_soluzione_disposizioni(int *val, int *sol, int n);
int combinazioni_semplici ( int *val, int *sol, int n, int k, int start, int pos, int count, arco *archi);

int main() {

    int nv;
    int nc;

    FILE *ptr = fopen("grafo.txt", "r");
    
    fscanf(ptr, "%d %d", &nv, &nc);
    
    arco *archi = malloc(nc*sizeof(arco));

    for (int a=0; a<nc; a++) {
        fscanf(ptr, "%d %d", &archi[a].u, &archi[a].v);
    }

    //generiamo l'insieme dei vertici
    int *val = malloc(nv*sizeof(int));

    for (int a=0; a<nv; a++) {
        val[a] = a;
    }  

    int *sol = malloc((nv)*sizeof(int));

    //con disposizioni ripetute
    int count = powerset_disposizioni_ripetute(val,sol,nv,0,count,archi);
    printf("\nNumero soluzioni: %d\n\n", count);
    count = 0;
    //con combinazioni semplici
    for (int k=0; k<=nv; k++) {
        count =+ combinazioni_semplici(val,sol,nv,k,0,0,count,archi);
    }
    printf("\nNumero soluzioni: %d", count);
    return 0;
}

int combinazioni_semplici ( int *val, int *sol, int n, int k, int start, int pos, int count, arco *archi) {

    int i;

    if (pos >= k)
    {
        int counter;
        //controlliamo che la soluzione vada bene
        //iteriamo su tutti gli archi della struttura dati
        for (int a = 0; a < n; a++)
        {
            //iteriamo su tutti i vertici della soluzione
            counter = 0;
            for (int v = 0; v < k; v++)
            {
                //controlliamo che il vertice figuri almeno in un estremo di un arco, incrementiamo il contatore
                if (archi[a].u == sol[v] || archi[a].v == sol[v])
                {
                    counter++;
                }
            }
            if (counter == 0)
            {
                //abbiamo fallito
                return count;
            }
        }
        //se no stampiamo
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
        count = combinazioni_semplici(val,sol,n,k,i+1,pos+1,count,archi);
    }
    return count;
}


int powerset_disposizioni_ripetute (int *val, int *sol, int n, int pos, int count, arco *archi) {

    if (pos>=n) {
        if (check_vertice(sol,val,archi,n) == 1) {
            //soluzione sbagliata non la stampiamo e non la contiamo
            return count;
        } 
        //se funziona posso stampare la soluzione
        stampa_soluzione_disposizioni(val,sol,n);
        return count+1;
    }

    sol[pos] = 0;
    //non include l'elemento
    count = powerset_disposizioni_ripetute(val,sol,n,pos+1,count, archi);
    //include l'elemento nei livelli successivi
    sol[pos] = 1;
    count = powerset_disposizioni_ripetute(val,sol,n,pos+1,count, archi);
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

int check_vertice(int *sol, int *val, arco *archi, int n) {

    int counter;
    //controlliamo che la soluzione vada bene
    //iteriamo su tutti gli archi della struttura dati
    for (int a = 0; a < n; a++) {
        //iteriamo su tutti i vertici della soluzione
        counter = 0;
        for (int v = 0; v < n; v++) {
            //controlliamo solo per i vertici inclusi nella sol
            if (sol[v] == 1) {
                //controlliamo che il vertice figuri almeno in un estremo di un arco, incrementiamo il contatore
                if (archi[a].u == val[v] || archi[a].v == val[v]) {
                    counter++;
                }
            }
        }
        if (counter == 0) {
            //abbiamo fallito
            return 1;
        }
    }
    return 0;
}
