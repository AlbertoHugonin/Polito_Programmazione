#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define R 19
#define C 19

int cerca_vittoria(char vett[], char t);



int main() {

    FILE *partita;

    char scacchiera[R][C] = { 0 };

    partita = fopen("save.txt", "r");

    //salviamo la schacchiera sulla struttura dati
    char c;
    for (int a=0; a<R; a++) {
        for (int b=0; b<C+1; b++) {
            c = getc(partita);
            if (c != '\n') {
                scacchiera[a][b] = c;
            }
        }
    }

    //prendere la mossa
    char turni[2][6] = {{"nero"}, {"bianco"}};
    char turni_c[2][1] = {{"N"}, {"B"}};
    int sel_turno = 0;

    int sel_riga;
    int sel_colonna;

    while (1) {

        printf("Inserisci la mossa del %s <riga> <colonna>:\n", turni[sel_turno]);
        scanf("%d %d", &sel_riga, &sel_colonna);
        sel_riga--;
        sel_colonna--;

        //controllo dimensioni scacchiera
        if (sel_riga > 19 || sel_colonna > 19) {
            puts("Numerazione non valida.\n");
            continue;
        }
        //controlliamo che non ci sia di una casella occupata
        if (scacchiera[sel_riga][sel_colonna] != '.') {
            puts("Posto gia' occupato");
            continue;
        }
        //inserisco la mossa
        scacchiera[sel_riga][sel_colonna] = turni_c[sel_turno][0];
        //calcoliamo se la mossa porta alla vittoria
        
        //controllo vittoria per riga
        if (cerca_vittoria(scacchiera[sel_riga], turni_c[sel_turno][0]) == 1) {
            puts("Hai vinto per riga!!");
            return 0;
        }
        //controllo vittoria per colonna
        char buff[R];
        for (int a=0; a<R; a++) {
            buff[a] = scacchiera[a][sel_colonna];
        }
        if (cerca_vittoria(buff, turni_c[sel_turno][0]) == 1) {
            puts("Hai vinto per colonna!!");
            return 0;
        }
        //controllo per diagonale da sinistra verso destra
        int counter = 0;
        int back_riga = sel_riga;
        int back_colonna = sel_colonna;

        while (sel_riga > 0 && sel_colonna > 0) {
            sel_colonna--;
            sel_riga--;
        }
        while (sel_riga < R && sel_colonna < C) {
            if (scacchiera[sel_riga][sel_colonna] == turni_c[sel_turno][0]) {
                counter ++;
                if (counter == 5) {
                    puts("Hai vinto per diagonale sinistra!!");
                    return 1;
                }
            }
            else {
                counter = 0;
            }  
            sel_colonna++;
            sel_riga++;              
        }
        counter = 0;
        sel_riga = back_riga;
        sel_colonna = back_colonna;
        //controllo per diagonale da destra verso sinistra
        while (sel_riga > 0 && sel_colonna < 19) {
            sel_colonna++;
            sel_riga--;
        }
        while (sel_riga < R && sel_colonna > 0) {
            if (scacchiera[sel_riga][sel_colonna] == turni_c[sel_turno][0]) {
                counter ++;
                if (counter == 5) {
                    puts("Hai vinto per diagonale destra!!");
                    return 1;
                }
            }
            else {
                counter = 0;
            }  
            sel_colonna--;
            sel_riga++;              
        }
    }
    return 0;
}


int cerca_vittoria(char vett[], char t) {

    int counter = 0;

    for (int a=0; a<strlen(vett); a++) {
        if (vett[a] == t) {
            counter++;
            if (counter == 5) {
                return 1;
                }
            }
            else {
                counter = 0;
        }
    }
    return 0;
}