#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////OGGETTI.H

typedef struct Item_ *item;

item ItemInit(char *nome, int length, int val, int peso);
item ItemScan(FILE *file);
int GetVal(item oggetto);
int GetPeso(item oggetto);
void PrintNome(item oggetto);

/////////////// OGGETTI.C

struct Item_ {
    char *nome;
    int val;
    int peso;
};

item ItemInit(char *nome, int length, int val, int peso) {
    item oggetto = malloc(sizeof(struct Item_ *));
    oggetto->nome = malloc(length*sizeof(char));
    strcpy(oggetto->nome,nome);
    oggetto->val=val;
    oggetto->peso=peso;
    return oggetto;
}

//recuper UN SOLO item da file, chi usa il modulo si deve occupare di creare una struttura di Item
item ItemScan(FILE *file) {

    //contiene la lunghezza della stringa nome da salvare
    int a;
    char nome[30];
    for (int a=0; a<30; a++) {
        nome[a] = '\0';
    }
    int val;
    int peso;
    if (feof(file)) {
        //ritorna item null
        return ItemInit(NULL,0,0,0);
    }

    fscanf(file,"%s %d %d", nome, &val, &peso);
    for (a=0; a<30; a++) {
        if (nome[a] == '\0') {
            break;
        }
    }
    return ItemInit(nome,a,val,peso);

}

int GetVal(item oggetto) {
    return oggetto->val;
}

int GetPeso(item oggetto) {
    return oggetto->peso;
}

void PrintNome(item oggetto) {
    printf("%s", oggetto->nome);
    return;
}

/////////////////////////// FINE ADT OGGETTI

void disposizioni_ripetute_no_ottimizzazioni(item *val, int *sol, int n, int pos, int *best_sol, int *best_val, int cap);
void disposizioni_ripetute_con_ottimizzazioni(item *val, int *sol, int n, int pos, int *best_sol, int *best_val, int cap, int peso, int valore);
void disposizioni_ripetute_con_ottimizzazioni_e_pruning(item *val, int *sol, int n, int pos, int *best_sol, int *best_val, int cap, int peso, int valore);

int main() {

    FILE *file_oggetti = fopen("oggetti.txt", "r");
    int cap = 10;
    int N = 1;
    item *oggetti = malloc(N*sizeof(item *));
    while (1) {
        oggetti[N-1] = ItemScan(file_oggetti);
        if (feof(file_oggetti)) {
            break;
        } else {
            N++;
            //riassegno perchè se la memoria viene spostata devo spostare anche il puntatore
            oggetti = realloc(oggetti,(N)*sizeof(item *));
        }
    }
    int *sol = malloc(N*sizeof(int));
    int *best_sol = malloc(N*sizeof(int));
    int *best_val = malloc(sizeof(int));
    *best_val=0;

    //disposizioni_ripetute_no_ottimizzazioni(oggetti, sol, N, 0, best_sol,best_val,cap);

    // disposizioni_ripetute_con_ottimizzazioni(oggetti, sol, N, 0, best_sol,best_val,cap,0,0);
    disposizioni_ripetute_con_ottimizzazioni_e_pruning(oggetti, sol, N, 0, best_sol,best_val,cap,0,0);

    for (int a=0; a<N; a++) {
        if (best_sol[a]==1) {
           PrintNome(oggetti[a]);
        }
    }

    printf(" Valore: %d", *best_val);
    return 0;
}

//////////////////////////////////////

//SOLUZIONE SENZA PRUNING
//best sol soluzione migliore, best val valore di guadagno migliore
void disposizioni_ripetute_no_ottimizzazioni(item *val, int *sol, int n, int pos, int *best_sol, int *best_val, int cap) {

    if (pos>=n) {
        //controllo validità soluzione
        //controllo soluzione dentro 
        int peso=0;
        int valore=0;
        for (int a=0; a<n; a++) {
            if (sol[a] == 1) {
                peso += GetPeso(val[a]);
                valore += GetVal(val[a]);
                if (peso>cap) {
                    //soluzione non ammessa
                    return;
                }
            }
        }
        if (valore > *best_val) {
            *best_val = valore;
            for (int a=0; a<n; a++) { 
                best_sol[a]=sol[a];
            }  
        }
        return;
    }

    sol[pos] = 1;
    disposizioni_ripetute_no_ottimizzazioni(val,sol,n,pos+1,best_sol,best_val,cap);
    sol[pos] = 0;
    disposizioni_ripetute_no_ottimizzazioni(val,sol,n,pos+1,best_sol,best_val,cap);
    return;
}


//variante con ottimizzazioni, invece di calcolare il peso e il valore alla fine lo calcolo runtime cosi devo solo piu' confrontare e non perdo tempo dentro un ciclo for
void disposizioni_ripetute_con_ottimizzazioni(item *val, int *sol, int n, int pos, int *best_sol, int *best_val, int cap, int peso, int valore) {


    if (pos>=n) {
        //controllo validità soluzione
        //controllo soluzione dentro 
        if (peso>cap) {
            //soluzione non ammessa
            return;
        }
        if (valore > *best_val) {
            *best_val = valore;
            for (int a=0; a<n; a++) { 
                best_sol[a]=sol[a];
            }  
        }
        return;
    }

    sol[pos] = 1;

    peso += GetPeso(val[pos]);
    valore += GetVal(val[pos]);

    disposizioni_ripetute_con_ottimizzazioni(val,sol,n,pos+1,best_sol,best_val,cap,peso,valore);

    sol[pos] = 0;

    peso -= GetPeso(val[pos]);
    valore -= GetVal(val[pos]);
    disposizioni_ripetute_con_ottimizzazioni(val,sol,n,pos+1,best_sol,best_val,cap,peso,valore);
    return;

}

//variante con ottimizzazione e pruning
void disposizioni_ripetute_con_ottimizzazioni_e_pruning(item *val, int *sol, int n, int pos, int *best_sol, int *best_val, int cap, int peso, int valore) {


    if (pos>=n) {
        //controllo validità soluzione
        //controllo soluzione dentro 
        if (peso>cap) {
            //soluzione non ammessa
            return;
        }
        if (valore > *best_val) {
            *best_val = valore;
            for (int a=0; a<n; a++) { 
                best_sol[a]=sol[a];
            }  
        }
        return;
    }

    sol[pos] = 1;

    peso += GetPeso(val[pos]);
    valore += GetVal(val[pos]);

    //se prendendo l'elemento il peso è già piu' grande del cap non ha senso andare avanti e sprecare tempo PRUNING
    if (peso>cap) {
        return;
    }

    disposizioni_ripetute_con_ottimizzazioni_e_pruning(val,sol,n,pos+1,best_sol,best_val,cap,peso,valore);

    sol[pos] = 0;
    
    peso -= GetPeso(val[pos]);
    valore -= GetVal(val[pos]);
    disposizioni_ripetute_con_ottimizzazioni_e_pruning(val,sol,n,pos+1,best_sol,best_val,cap,peso,valore);
    return;

}