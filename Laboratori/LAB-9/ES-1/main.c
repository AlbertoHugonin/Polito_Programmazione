#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct att_ {

    int i;
    int f;
    int d;

    int use;

} att;

typedef struct wrapper_ {
    
    int n;
    att *att_s;

} tab_att;


void powerset_disp_rip(tab_att tabella, int pos, int *durata_migliore, att *sol_migliore);

int main() {

    FILE *ptr = fopen("att.txt", "r");
    tab_att tabella;

    fscanf(ptr, "%d ", &tabella.n);

    tabella.att_s = malloc(tabella.n*sizeof(att));

    for (int a=0; a<tabella.n; a++) {

        fscanf(ptr, "%d %d ", &tabella.att_s[a].i, &tabella.att_s[a].f);
        tabella.att_s[a].d = tabella.att_s[a].f - tabella.att_s[a].i;
        tabella.att_s[a].use = 0;
        
    }

    puts("Condizione Iniziale\n");
    for (int a=0; a<tabella.n; a++) {
        printf("atttività %d: ( %d - %d ) -> %d in uso: %d\n", a+1, tabella.att_s[a].i, tabella.att_s[a].f, tabella.att_s[a].d, tabella.att_s[a].use);
    }
    puts("\n");

    //powerset mediante disposizioni ripetute

    int *durata_migliore = malloc(sizeof(int));
    att *sol_migliore = malloc(tabella.n*sizeof(att));

    powerset_disp_rip(tabella,0,durata_migliore, sol_migliore);

    puts("Soluzione Migliore\n");

    for (int a=0; a<tabella.n; a++) {
        printf("atttività %d: ( %d - %d ) -> %d in uso: %d\n", a+1, sol_migliore[a].i, sol_migliore[a].f, sol_migliore[a].d, sol_migliore[a].use);
    }
    
    printf("\nDurata Migliore: %d\n", *durata_migliore);

    return 0;
}

//il wrapper tabella include n che è la dim del problema, count viene omesso perchè non utile, pos è necessario perchè indica la dimensione del problema a passo ricorsivo
//non usiamo un vettore sol ma scriviamo direttamente in un campo dentro ciascuna attività se l'abbiamo usata o meno (stesso utilizzo di memoria)
void powerset_disp_rip(tab_att tabella, int pos, int *durata_migliore, att *sol_migliore) {

    int j;

    if (pos >= tabella.n) {
        //condizione di terminazione salviamo solo se è ottima
        int durata = 0;

        //calcolo durata
        for (j=0; j<tabella.n; j++) {
            if (tabella.att_s[j].use != 0) {
                durata = durata + tabella.att_s[j].d;
            }
        }
        //se è la soluzione migliore la salvo

        if (durata > *durata_migliore) {
            *durata_migliore = durata;
            memcpy(sol_migliore,tabella.att_s,sizeof(att)*tabella.n);
        }
        return;
    }

    tabella.att_s[pos].use = 0;
    powerset_disp_rip(tabella,pos+1,durata_migliore,sol_migliore);

    //controllo che attività che voglio inserire non si intersechi con un altra

    for (j=0; j<pos; j++) {
        if (tabella.att_s[j].use != 0) {
            if (tabella.att_s[pos].i < tabella.att_s[j].f && tabella.att_s[j].i < tabella.att_s[pos].f) {
                return;
            }
        }
    }
    
    //se non si interseca la posso inserire

    tabella.att_s[pos].use = 1;
    powerset_disp_rip(tabella,pos+1,durata_migliore,sol_migliore);

    return;

}