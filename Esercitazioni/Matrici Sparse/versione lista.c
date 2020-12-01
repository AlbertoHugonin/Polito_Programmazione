#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct elemento_ {
    int n;
    int n_col;
    struct elemento_ *successivo;
    struct elemento_ *precedente;

} elemento;


typedef struct riga_ {

    int count;
    elemento *testa;
    elemento *coda;

} riga;

typedef struct matrice_ {
    riga *righe;
    int N;
} matrice;



matrice *CreaMatrice (int r, int c, int *cache);
void Inserimento (int val, int n_colonna, riga *lista);
void leggi_matrice_sparsa(matrice *matrice_sparsa);
void Aggiornamento (int val, int r, int c, matrice *matrice_sparsa);

int main() {
    
    FILE *tabella = fopen("matrice.txt", "r");
    //prendiamo le dimensioni della matrice

    int r,c;

    fscanf(tabella,"%d", &r);
    fscanf(tabella,"%d", &c);

    //matrice di supporto con vettore dinamico
    int *cache = malloc (r * c * (sizeof(int)));

    for (int a=0; a<r; a++) {
        for (int b=0; b<c; b++) {
            fscanf(tabella, "%d", &cache[c*a + b]);
        }
    }

    matrice *matrice_sparsa = CreaMatrice(r,c,cache);

    leggi_matrice_sparsa(matrice_sparsa);

    //proviamo a fare una modifica e rileggere
    Aggiornamento(0,0,3,matrice_sparsa);
    Aggiornamento(0,0,7,matrice_sparsa);
    Aggiornamento(0,0,0,matrice_sparsa);
    Aggiornamento(0,0,1,matrice_sparsa);
    //proviamo svuotata la riga ad inserire
    Aggiornamento(10,0,0, matrice_sparsa);
    Aggiornamento(15,0,1, matrice_sparsa);

    puts("\n\n");
    puts("Nuova tabella\n\n");
    leggi_matrice_sparsa(matrice_sparsa);

    return 0;
}

void leggi_matrice_sparsa(matrice *matrice_sparsa) {

    for (int a=0; a<matrice_sparsa->N; a++) {
        
        riga *riga_corrente = &(matrice_sparsa->righe[a]);
        elemento *elemento_corrente = riga_corrente->testa;
        printf("Elementi riga n:%d con num elementi: %d\n\n", a, riga_corrente->count);
        for (int b=0; b<riga_corrente->count; b++) {
            printf("\t Elemento indice n.%d e': %d\n ", elemento_corrente->n_col, elemento_corrente->n);
            elemento_corrente = elemento_corrente->successivo;
        }
        puts("\n");
    }
    return;
}

matrice *CreaMatrice (int r, int c, int *cache) {

    matrice *matrice_sparsa = malloc(sizeof(matrice));

    matrice_sparsa->righe = malloc(r*sizeof(riga));
    matrice_sparsa->N=r;

    matrice_sparsa->righe[0].testa = malloc(sizeof(elemento));

    
    for (int a=0; a<r; a++) {

        for (int b=0; b<c; b++) {
            if (cache[c*a + b] != 0) {
                Inserimento(cache[c*a + b], b, &(matrice_sparsa->righe[a]));
            }
        }
    }
    return matrice_sparsa;

}

void Aggiornamento (int val, int r, int c, matrice *matrice_sparsa) {

    riga *riga_corrente = &(matrice_sparsa->righe[r]);
    elemento *elemento_corrente = riga_corrente->testa;

    //controllo invalidità
    if (matrice_sparsa==NULL || r>=matrice_sparsa->N) {
        return;
    }

    //Rimozione
    if (val == 0) {
        for (int a=0; a<riga_corrente->count; a++) {
        if (elemento_corrente->n_col==c) {
            //rimozione dalla lista

            riga_corrente->count--;
            
            //se ultimo elemento da rimuovere
            if (riga_corrente->count==0) {
                riga_corrente->testa=NULL;
                riga_corrente->coda=NULL;
                free(elemento_corrente);
                return;
            }

            //caso eliminazione testa
            if (a==0) {
                elemento_corrente->successivo->precedente=NULL;
                riga_corrente->testa=elemento_corrente->successivo;
                free(elemento_corrente);

                return;

            }
            //caso coda
            if (a==riga_corrente->count) {
                elemento_corrente->precedente->successivo=NULL;
                riga_corrente->coda=elemento_corrente->precedente;
                free(elemento_corrente);
                return;
            }

            //casi in mezzo
            elemento_corrente->precedente->successivo = elemento_corrente->successivo;
            elemento_corrente->successivo->precedente=elemento_corrente->precedente;

            return;
        }
        elemento_corrente=elemento_corrente->successivo; 
    }
    }

    //Aggiornamento
    for (int a=0; a<riga_corrente->count; a++) {
        if (elemento_corrente->n_col==c) {
            elemento_corrente->n=val;
            return;
        }
        elemento_corrente=elemento_corrente->successivo;
    }

    //Inserimento
    Inserimento(val,c,riga_corrente);
    return;
}

//non essendo un inserimento ordinato è sempre un inserimento in coda
void Inserimento (int val, int n_colonna, riga *lista) {

    elemento *nodo_corrente = malloc(sizeof(elemento));
    nodo_corrente->n=val;
    nodo_corrente->n_col=n_colonna;

    if (lista->count==0) {

        lista->testa=nodo_corrente;
        lista->coda=nodo_corrente;
    
    }
    else {
        //siamo nel caso primo elemento già inserito
        elemento *coda = lista->coda;

        coda->successivo=nodo_corrente;
        nodo_corrente->precedente=coda;
        lista->coda=nodo_corrente;        

    }
    lista->count++;

    return;

}