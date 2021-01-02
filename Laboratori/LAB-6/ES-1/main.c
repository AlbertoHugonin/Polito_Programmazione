#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

    char **scelte;
    int num_scelte;
    
} Livello;

int principio_di_moltiplicazione_string ( Livello *corrente, char **sol, int n, int pos, int count);

int principio_di_moltiplicazione_string ( Livello *corrente, char **sol, int n, int pos, int count) {

    int a=0;

    if (pos >= n) {
        printf("Playlist #%d\n", count+1);
        for (a=0; a<n; a++) {
            printf("%s\n", sol[a]);
        }
        puts("");
        return count+1;
    }

    for (a=0; a<corrente[pos].num_scelte; a++) {
        sol[pos] = strdup(corrente[pos].scelte[a]);
        count = principio_di_moltiplicazione_string(corrente,sol,n,pos+1,count);
    }
    return count;

}
int main() {

    FILE *brani = fopen("brani.txt", "r");

    int n_amici;
    char stringa[255];
    int count = 0;

    fscanf(brani,"%d", &n_amici);

    //creiamo un vettore val di struct che contengono a sua volta un vett delle scelte e il numero di scelte per quel livello
    Livello *val = calloc(n_amici, n_amici*sizeof(Livello));

    for (int a=0; a<n_amici; a++) {

        fscanf(brani,"%d", &val[a].num_scelte);

        //la calloc a quanto pare risolve ogni problema
        val[a].scelte = calloc(val[a].num_scelte, val[a].num_scelte*sizeof(char));
        
        for (int b=0; b<val[a].num_scelte; b++) {
            fscanf(brani,"%s", stringa);
            val[a].scelte[b] = strdup(stringa);
        }
    
    }
    char **sol = calloc(n_amici, n_amici*sizeof(char));
    principio_di_moltiplicazione_string(val,sol,n_amici,0,count);
    return 0;
}