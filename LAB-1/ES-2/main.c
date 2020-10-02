#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//FUNZIONE DI RICERCA CHE DATA UNA PAROLA LA CERCA RITORNANDO L'INDICE DELLA PRIMA OCCORRENZA
int funz_ricerca(char parola[], char chiave[]);

int main()
{
    FILE *sorgente;
    FILE *dizionario;
    FILE *destinazione;
    char parole[20] = {0};
    char ricerca[30][10] = {0};
    char sostituzioni[30][10] = {0};
    
    //supporto per creazione parola
    char supp[20] = {0};

    sorgente = fopen("sorgente.txt", "r");
    dizionario = fopen("dizionario.txt", "r");
    destinazione = fopen("destinazione.txt", "w");

    int s = fscanf(dizionario, " %d", &s);
    s = 9;

    for (int a=0; a<s; a++) {
        fscanf(dizionario, "%s %s", sostituzioni[a], ricerca[a]);
    }

    while(fscanf(sorgente, "%s", parole) != EOF) {

        int trovato = 0;

        for (int a=0; a<s; a++) {

            //variabili per evitare calcoli aggiuntivi durante i cicli for
            int res = funz_ricerca(parole, ricerca[a]);
            int lunghezza_codifica = strlen(sostituzioni[a]);
            int lunghezza_parola_cercata = strlen(ricerca[a]);

            if (res != -1) {
                
                trovato = 1;

                //cominciamo il calcolo della nuova stringa da sostituire
                for (int b=0; b<res; b++) {
                    supp[b] = parole[b];
                }
                //adesso dobbiamo incollare la sostituzione
                for (int b=0; b<lunghezza_codifica; b++) {
                    supp[b+res] = sostituzioni[a][b];
                }
                //incolliamo il resto della parola

                int f = 0;
                int lunghezza_supporto = strlen(supp);

                for (int c = 0; c < res + lunghezza_parola_cercata; c++) {
                    
                    if (parole[res + lunghezza_parola_cercata + f] == '\0') {
                        break;
                    }
                    
                    supp[c + lunghezza_supporto] = parole[res + lunghezza_parola_cercata + f];
                    f++;
                }
                printf("%s ", supp);
                fputs(supp, destinazione);
                fputs(" ", destinazione);

                //resettiamo il supporto per evitare lettere in piu'
                for (int b=0; b<20; b++) {
                    supp[b] = '\0';
                    parole[b] = '\0';
                }
                break;      
            }
        }
        //stampo la parola nel caso non abbia trovato una ricodifica valida
        if (trovato == 0) {
            printf("%s ", parole);
            fputs(parole, destinazione);
            fputs(" ", destinazione);
            trovato = 0;
        }

    }

    //chiusura file
    fclose(dizionario);
    fclose(sorgente);
    fclose(destinazione);

    return 0;
   
}

int funz_ricerca(char parola[], char chiave[]) {

    int lunghezza_chiave = strlen(chiave);

    for (int a = 0; a < strlen(parola); a++) {

        if (parola[a] == chiave[0]) {

            if (lunghezza_chiave == 1) {
                return a;
            }

            for (int b = 0; b < lunghezza_chiave; b++) {
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