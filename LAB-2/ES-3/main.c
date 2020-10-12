#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define n_sequenze 20

void trova_sequenza(char sequenze[], FILE *testo);
int funz_ricerca(char parola[], char chiave[]);


int main () {

    char sequenze[n_sequenze][5] = { 0 };

    FILE *testo = fopen("testo.txt", "r");
    FILE *sequenza = fopen("sequenze.txt", "r");

    int n_seq;
    fscanf(sequenza, "%d", &n_seq);

    for (int a=0; a<n_seq; a++) {
        fscanf(sequenza, "%s", sequenze[a]);
    }

    for (int a=0; a<n_seq; a++) {
        //troviamo la sequenza e stampiamo il risultato a video
        trova_sequenza(sequenze[a], testo);
    }


    return 0;
}


void trova_sequenza(char sequenze[], FILE *testo) {

    char parola[25] = { 0 };
    int n_parola = 0;
    int prima_trovata = 0;

    while (fscanf(testo, "%s", &parola) != EOF) {

        //rimuovere la punteggiatura dalla parola
        for (int a=0; a<strlen(parola); a++) {
            if (ispunct(parola[a])) {
                parola[a] = 0;
            }
        }
        //la parola e pronta e possiamo cercare la sequenza nella parola
        //facciamo il primo passaggio per vedere se la sequenza è contenuta in almeno una parola
        if (funz_ricerca(parola,sequenze) != -1) {
            if (prima_trovata == 0) {
                printf("La sequenza %s e' contenuta in: %s (posizione %d nel testo)\n", sequenze, parola, n_parola+1);
                prima_trovata = 1;
            }
            else {
                printf("\t\t\t\t%s (posizione %d nel testo)\n", parola, n_parola+1);
            }
        }
        n_parola++;
    }
    if (prima_trovata == 1) {
        printf("\n");
    }
    rewind(testo);
    return;
}

//funzione gia' usata nell'esercizio 2 lab 1, modificata per ignorare maiuscole e minuscole
int funz_ricerca(char parola[], char chiave[]) {

    int lunghezza_chiave = strlen(chiave);

    for (int a = 0; a < strlen(parola); a++) {

        if (parola[a] == chiave[0] || tolower(parola[a]) == tolower(chiave[0])) {

            if (lunghezza_chiave == 1) {
                return a;
            }

            for (int b = 1; b < lunghezza_chiave; b++) {
                if (parola[b+a] != chiave[b]) {
                    break;
                }
                if ( b == lunghezza_chiave - 1) {
                    //siamo alla fine e non siamo usciti quindi abbiamo trovato la stringa
                    return a;
                }
            }
                
        }
    }
    //nel caso non abbia trovato nulla
    return -1;
}