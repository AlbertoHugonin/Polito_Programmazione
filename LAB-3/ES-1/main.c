#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXR 50
#define MAXC 50
//modifica esercizio 1 lab 2

int controllo_riga(int riga[], int pos, int c);
void leggiMatrice(int matrice[MAXR][MAXC], int *nr, int *nc);

int main() {

    int mappa[MAXR][MAXC];
    int r;
    int c;

    leggiMatrice(mappa, &r, &c);

    for (int a=0; a<r; a++) {
        for (int b=0; b<c; b++) {
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

void leggiMatrice(int matrice[MAXR][MAXC], int *nr, int *nc) {

    FILE *file = fopen("LAB-3/ES-1/mappa.txt", "r");

    //salviamo la mappa
    fscanf(file, "%d %d", nr, nc);
    for (int a=0; a<*nr; a++) {
        for (int b=0; b<*nc; b++) {
            fscanf(file, "%d", &matrice[a][b]);
        }
    }

}