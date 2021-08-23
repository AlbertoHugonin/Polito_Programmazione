#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    int V[] = {-1,2,3,-6,1,3,1};
    int N = 7;

    //salviamo la dim e posizione del piu' grande
    int somma;
    int i;
    //trovare uno dei sottovettori propri
    for (int dim=N; dim>1; dim--) {
        for (int a=0; a<N-dim; a++) {
            int somma_rel = 0;
            int b=0;
            for (b=0; b<dim; b++) {
                somma_rel += V[b+a];
            }
            if (somma_rel>somma) {
                somma=somma_rel;
                i=a;
            }
        }
    }
    return 0;
}