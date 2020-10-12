#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#define N 100000

int LinearSearch(int v[], int l, int r, int k);


int main() {

    int V[N];

    //generazione vettore
    int i;
    srand(time(0));

    for (i=0; i<N; i++){
        V[i] = 1 + rand()%N;
    }	

    //analisi con alta possibilità caso peggiore
    int k = 1 + rand()%N;
    int pos = LinearSearch(V, 0, N-1, k);

    if (pos != -1) {
        printf("Trovato %d in pos %d", k, pos);
        return 0;
    }
    printf("Non trovato %d", k);

    return 1;
}


//v vettore, l estremo sinistro, r estremo destro, k chiave: comlessità T(n) = N (lineare)
int LinearSearch(int v[], int l, int r, int k) {

    int i=l;
    int found=0;
    
    //uscita strutturata
    while (i<=r && found == 0)
    if (k == v[i])
      found = 1;
    else
      i++;
    if (found == 0)
      return -1;
    else
      return i;

}