#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define R 19
#define C 19

int cerca_vittoria(char vett[], char t);
int controllo_validita(int sel_r, int sel_c, char scacchiera[R][C]);
void salva_tabella(char scacchiera[R][C], char nome_file[]);

int main() {

    char scacchiera[R][C] = { 0 };
    salva_tabella(scacchiera, "save.txt");

    //prendere la mossa
    char turni[2][6] = {{"nero"}, {"bianco"}};
    int sel_turno = 0;

    int sel_riga;
    int sel_colonna;

    while (1) {

        printf("Inserisci la mossa del %.6s <riga> <colonna>:\n", turni[sel_turno]);
        scanf("%d %d", &sel_riga, &sel_colonna);
        sel_riga--;
        sel_colonna--;

        //controllo validità
        if (controllo_validita(sel_riga, sel_colonna,scacchiera) == 0) {
            continue;
        }

        //inserisco la mossa
        scacchiera[sel_riga][sel_colonna] = toupper(turni[sel_turno][0]);

        //calcoliamo se la mossa porta alla vittoria
        
        //controllo vittoria per riga
        if (cerca_vittoria(scacchiera[sel_riga], toupper(turni[sel_turno][0])) == 1) {
            puts("Hai vinto per riga!!");
            return 0;
        }
        //controllo vittoria per colonna
        char buff[R];
        for (int a=0; a<R; a++) {
            buff[a] = scacchiera[a][sel_colonna];
        }
        if (cerca_vittoria(buff, toupper(turni[sel_turno][0])) == 1) {
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
            if (scacchiera[sel_riga][sel_colonna] == toupper(turni[sel_turno][0])) {
                counter ++;
                if (counter == 5) {
                    puts("Hai vinto per diagonale sinistra!!");
                    return 0;
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
            if (scacchiera[sel_riga][sel_colonna] == toupper(turni[sel_turno][0])) {
                counter ++;
                if (counter == 5) {
                    puts("Hai vinto per diagonale destra!!");
                    return 0;
                }
            }
            else {
                counter = 0;
            }  
            sel_colonna--;
            sel_riga++;              
        }

        //finito cambiamo turno e ricominciamo
        if (sel_turno == 1) {
            sel_turno = 0;
            continue;
        }
        sel_turno = 1;
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

int controllo_validita(int sel_r, int sel_c, char scacchiera[R][C]) {
    //controllo dimensioni scacchiera
    if (sel_r > R || sel_c > C) {
        puts("Numerazione non valida.\n");
        return 0;
    }
        //controlliamo che non ci sia di una casella occupata
    if (scacchiera[sel_r][sel_c] != '.') {
        puts("Posto gia' occupato");
        return 0;
    }
    return 1;
}

void salva_tabella(char scacchiera[R][C], char nome_file[]) {
    
    FILE *partita;
    partita = fopen(nome_file, "r");
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
    fclose(partita);
    return;
}