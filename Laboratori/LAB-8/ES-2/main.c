#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stampa_soluzione_disposizioni(int *sol, int n);

typedef struct test_ {
    int disp[4];
    int rip;
    int pietra_rip;
    int val[4];
} test;


int powerset_disposizioni_ripetute (int *sol, int n, int pos, int count, test pietre_preziose, int max_rip);

char pietre[4] = {'Z','R','T','S'};

int main() {
    FILE *ptr = fopen("easy_test_set.txt", "r");

    int n_test;

    test pietre_preziose;
    //tabella simboli per conversione intero simbolo (carattere)
    

    fscanf(ptr, "%d", &n_test);

    int num_pietre;
    int count;

    for (int n=0; n<n_test; n++) {
        fscanf(ptr, "%d %d %d %d", &pietre_preziose.disp[0], &pietre_preziose.disp[1], &pietre_preziose.disp[2], &pietre_preziose.disp[3]);
        num_pietre = pietre_preziose.disp[0] + pietre_preziose.disp[1] + pietre_preziose.disp[2] + pietre_preziose.disp[3];
        for (int i=num_pietre; i>1; i--) {
            int *sol = calloc(i,i*sizeof(char));
            pietre_preziose.pietra_rip=0;
            pietre_preziose.rip=0;
            int max_rip = 3;
            count = powerset_disposizioni_ripetute(sol,i,0,0,pietre_preziose, max_rip);
            //printf("Numero di soluzioni trovate lunghezza %d trovate sono: %d\n", i, count);
            if (count != 0) {
                printf("Lunghezza Massima test %d è: %d\n", n+1, i);
                break;
            }
        }
    }

    return 0;
}

int powerset_disposizioni_ripetute (int *sol, int n, int pos, int count, test pietre_preziose, int max_rip) {

    if (pos>=n) {
        //se funziona posso stampare la soluzione
        stampa_soluzione_disposizioni(sol,n);
        return count+1;
    }

    for (int a=0; a<4; a++) {

        if (pietre_preziose.disp[a] == 0) {
            continue;
        }

        if (pos > 0) {
            if ((sol[pos-1] == 0 || sol[pos-1] == 2) && ((a==2) || (a==3)))
                continue;
            if ((sol[pos-1] == 1 || sol[pos-1] == 3) && ((a==0) || (a==1)))
                continue;
        }

        if (a == pietre_preziose.pietra_rip) {
            if (pietre_preziose.rip+1>max_rip) {
                continue;
            }
            pietre_preziose.rip++;
        } else {
            pietre_preziose.pietra_rip = a;
            pietre_preziose.rip=1;
        }

        pietre_preziose.disp[a]--;
        sol[pos] = a;
        count = powerset_disposizioni_ripetute(sol,n,pos+1,count,pietre_preziose, max_rip);
        //non ci interessa enumerare tutto lo spazio basta che troviamo una soluzione (quindi in realtà non ci serve neanche il contatore)
        if (count != 0) {
            return count;
        }
        pietre_preziose.disp[a]++;
    }

    return count;


}

void stampa_soluzione_disposizioni(int *sol, int n) {
    printf("{ ");
    for (int a=0; a<n; a++) {
        printf("%c ", pietre[sol[a]]);
    }
    puts("}");
}