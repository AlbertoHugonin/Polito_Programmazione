#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////OGGETTI.H

typedef struct Item_ *item;

item ItemInit(char *nome, int length, int val, int peso);
item ItemScan(FILE *file);
int GetVal(item oggetto);
int GetPeso(item oggetto);
char *GetNome(item oggetto);

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

char *GetNome(item oggetto) {
    return oggetto->nome;
}

/////////////////////////// FINE ADT OGGETTI

int main() {

    FILE *file_oggetti = fopen("oggetti.txt", "r");
    int N = 1;
    item *oggetti = malloc(N*sizeof(item *));
    while (!feof(file_oggetti)) {
        N++;
        oggetti[N-2] = ItemScan(file_oggetti);
        realloc(oggetti,(N-1)*sizeof(item *));

    }
    return 0;
}