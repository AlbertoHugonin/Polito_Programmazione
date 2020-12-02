#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define R 50
#define C 50
//ogni gruppo deve essere circondato da celle bianche in tutte le direzioni tranne che in diagonale e dal bordo della tabella

int controllo_riga(int riga[], int pos, int c);

int main() {

    int mappa[R][C];
    FILE *file = fopen("mappa.txt", "r");

    //salviamo la mappa
    int r;
    int c;
    fscanf(file, "%d %d", &r, &c);
    for (int a=0; a<r; a++) {
        for (int b=0; b<c; b++) {
            fscanf(file, "%d", &mappa[a][b]);
        }
    }

    for (int a=0; a<r; a++) {
        for (int b=0; b<c; b++) {

            if (mappa[a][b] != 1) {
                continue;
            }
            //a e b sono riga e colonna dell'elemento considerato
            //controllo per riga
            int lunghezza = controllo_riga(mappa[a], b, c);
            int altezza = 1;
            int area = 0;
            
            //controllo per colonna
            for (int pos_r = a+1; pos_r<r; pos_r++) {
                if (mappa[pos_r][b] == 1) {
                    //se l'elemento sotto vale 1 allora puo' esserci un altra riga che forma un rettangolo
                    //per azzerare
                    controllo_riga(mappa[pos_r], b, c);
                    altezza++;
                }
                else {
                    break;
                }
            }
            //abbiamo lunghezza e altezza possiamo calcolare l'area
            area = lunghezza*altezza;

            if (area > lunghezza && area > altezza) {
                printf("Max Area: pos [%d,%d], lunghezza %d, altezza %d, area %d\n", a, b, lunghezza, altezza, area);
            }
            if (area == lunghezza && lunghezza > altezza) {
                printf("Max Base: pos [%d,%d], lunghezza %d, altezza %d, area %d\n", a, b, lunghezza, altezza, area);
            }
            if (area == altezza && altezza > lunghezza) {
                printf("Max Altezza: pos [%d,%d], lunghezza %d, altezza %d, area %d\n", a, b, lunghezza, altezza, area);
            }
            if (area == lunghezza && area == altezza) {
                printf("Quadrato piccolo: pos [%d,%d], lunghezza %d, altezza %d, area %d\n", a, b, lunghezza, altezza, area);
            }
            
        }
    }
    return 0;
}


int controllo_riga(int riga[], int pos, int c) {
    int count = 0;
    for (int a=pos; a<c; a++) {
        if (riga[a] == 1) {
            count++;
            riga[a] = 0;
        }
        else {
            return count;
        }
    }
    return count;
}