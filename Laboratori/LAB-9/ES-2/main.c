#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//database tile
typedef struct tile {

    //colore del tile
    char col[2];
    //valore del tile
    int val[2];
    //se in utilizzo o meno
    int use;

} tile;

//indica la singola mossa
typedef struct mossa_ {

    int tile;
    int rot;

} mossa;

//truttura wrapper scacchiera
typedef struct board_ {

    int nr;
    int nc;
    mossa **scacchiera;
    
} board;

int disposizioni_semplici(int n, int k, int count, int pos, tile *tiles, board board_w, int *punteggio_max, mossa **migliore);
int punteggio(board board_w, tile *tiles);

int punteggio(board board_w, tile *tiles) {

    int punteggio = 0;
    int parziale = 0;
    char colore;
    
    //da riguardare
    for (int r=0; r<board_w.nr; r++) {
        for (int c=0; c<board_w.nc; c++) {
            if (c==0) {
                colore = tiles[board_w.scacchiera[r][c].tile].col[(0+board_w.scacchiera[r][c].rot)%2];
                parziale += tiles[board_w.scacchiera[r][c].tile].val[(0+board_w.scacchiera[r][c].rot)%2];
            }
            else {
                if (colore != tiles[board_w.scacchiera[r][c].tile].col[(0+board_w.scacchiera[r][c].rot)%2]) {
                    parziale=0;
                    break;
                }
                parziale += tiles[board_w.scacchiera[r][c].tile].val[(0+board_w.scacchiera[r][c].rot)%2];
            }
        }
        punteggio = punteggio+parziale;
        parziale = 0;
    }

    for (int c=0; c<board_w.nc; c++) {
        for (int r=0; r<board_w.nr; r++) {
            if (r==0) {
                colore = tiles[board_w.scacchiera[r][c].tile].col[(1+board_w.scacchiera[r][c].rot)%2];
                parziale += tiles[board_w.scacchiera[r][c].tile].val[(1+board_w.scacchiera[r][c].rot)%2];
            }
            else {
                if (colore != tiles[board_w.scacchiera[r][c].tile].col[(1+board_w.scacchiera[r][c].rot)%2]) {
                    parziale=0;
                    break;
                }
                parziale += tiles[board_w.scacchiera[r][c].tile].val[(1+board_w.scacchiera[r][c].rot)%2];
            }
        }
        punteggio = punteggio+parziale;
        parziale = 0;
    }

    return punteggio;
}

// n tile e k tra cui scegliere posti liberi
//iteriamo tra tutti i tiles e possiamo o prenderne uno e inserirlo, o non fare nulla perchè il posto è gia occupato, o inserirlo ruotato
int disposizioni_semplici(int n, int k, int count, int pos, tile *tiles, board board_w, int *punteggio_max, mossa **migliore) {

    int i = 0;

    if (pos>=k) {
        int punteggio_corrente = punteggio(board_w,tiles);
        if (punteggio_corrente > *punteggio_max) {
            *punteggio_max = punteggio_corrente;
            for (int a=0; a<board_w.nr; a++) {
                for (int b=0; b<board_w.nc; b++) {
                    migliore[a][b].tile = board_w.scacchiera[a][b].tile;
                    migliore[a][b].rot = board_w.scacchiera[a][b].rot;
                }
            }
        }
        return count+1;
    }

    int r = pos / board_w.nc;
    int c = pos % board_w.nc;

    if (board_w.scacchiera[r][c].tile == -1) {
    //andiamo a iterare su tutti i tile disponibili
    for (i=0; i<n; i++) {
        //verifichiamo che il tile sia disponibile se no andiamo avanti
        if (tiles[i].use == 1) {
            continue;
        }
        //inseriamo non ruotato
        board_w.scacchiera[r][c].tile = i;
        //funge da vettore mark
        tiles[i].use = 1;
        board_w.scacchiera[r][c].rot = 0;
        count = disposizioni_semplici(n,k,count,pos+1,tiles,board_w,punteggio_max,migliore);
        //inserimento ruotato
        board_w.scacchiera[r][c].rot = 1;
        count = disposizioni_semplici(n,k,count,pos+1,tiles,board_w,punteggio_max,migliore);
        //backtracking
        board_w.scacchiera[r][c].tile = -1;
        tiles[i].use = 0;

    }
    } else {
        count = disposizioni_semplici(n,k,count,pos+1,tiles,board_w,punteggio_max,migliore);
    }

    return count;
}

int main() {

    FILE *board_f = fopen("board.txt", "r");
    FILE *tiles_f = fopen("tiles.txt", "r");

    board board_w;

    int nt;
    fscanf(tiles_f,"%d ", &nt);

    tile *tiles = malloc(nt*sizeof(tile));
    for (int a=0; a<nt; a++) {
        if (fscanf(tiles_f,"%c %d %c %d ", &tiles[a].col[0], &tiles[a].val[0], &tiles[a].col[1], &tiles[a].val[1]) == 4);
        //di default non usata
        tiles[a].use = 0;
    }

    fscanf(board_f,"%d ", &board_w.nr);
    fscanf(board_f,"%d ", &board_w.nc);

    board_w.scacchiera = malloc(board_w.nr*sizeof(mossa));

    for (int a=0; a<board_w.nr; a++) {
        board_w.scacchiera[a] = malloc(board_w.nc*sizeof(mossa));

        for (int b=0; b<board_w.nc; b++) {

            int n_tile;
            int rot;

            fscanf(board_f,"%d / %d", &n_tile, &rot);
            
            
            if (n_tile == -1) {
                board_w.scacchiera[a][b].tile = -1;
                board_w.scacchiera[a][b].rot = 0;
            }
            else {
                board_w.scacchiera[a][b].tile = n_tile;
                board_w.scacchiera[a][b].rot = rot;
                tiles[n_tile].use=1;
            }
        }
    }
    int *punteggio_max = malloc(sizeof(int));
    *punteggio_max = 0;

    mossa **migliore = malloc(board_w.nr*sizeof(mossa));

    for (int a=0; a<board_w.nr; a++) {
        migliore[a] = malloc(board_w.nc*sizeof(mossa));
    } 
    disposizioni_semplici(nt,9,0,0,tiles,board_w,punteggio_max,migliore);
    printf("%d", *punteggio_max);
    puts("\n");
    for (int a=0; a<board_w.nr; a++) {
        for (int b=0; b<board_w.nc; b++) {
            int rif = migliore[a][b].tile;
            printf("%c %c %d %d / %d ", tiles[rif].col[(0+migliore[a][b].rot)%2], tiles[rif].col[(1+migliore[a][b].rot)%2], tiles[rif].val[(0+migliore[a][b].rot)%2], tiles[rif].val[(1+migliore[a][b].rot)%2], migliore[a][b].rot);
        }
    puts("\n");
    }

    return 0;

}