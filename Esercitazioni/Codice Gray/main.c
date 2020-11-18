#include <stdio.h>
#include <stdlib.h>
#define n_bit 3
#define maxcod 8


void gray_1(int codici[maxcod][n_bit], int pos, int nbit);

//codifica di numeri interi tale che se passo da (da n a n+1) 2 a 3 le codifiche differiscono solo per 1 bit, la generazione si puo' gestire in maniera ricorsiva specchiando etc
//caso terminale numero a 1 bit
//per n bit si ottiene specchiando i codici a n-1 bit e aggiungendo 0 alla prima e 1 alla seconda meta

int main() {
    //iniziamo con l'allocazione statica
    int codici[maxcod][n_bit];

    gray_1(codici,0,n_bit);

    return 0;

}
//2^e, shift logico a sinistra di n posizioni
int pow2 (int e) {
    return 1<<e;
}

//pos la colonna dove la funzione andrà ad operare, nbit è il numero di bit che devo generare in tutto
void gray_1(int codici[maxcod][n_bit], int pos, int nbit) {

    //numero di codici che vado a generare attraversa questa chiamata ricorsiva
    int ncodici = pow2(nbit-pos);
    
    if ( pos == nbit-1) {
        codici[0][pos] = 0;
        codici[1][pos] = 1;
        return;
    }
    gray_1(codici,pos+1,nbit);
    //ncodici/2 perchè vado a codificare il resto delle occorrenze dentro al for
    for (int a=0; a<ncodici/2; a++) {
        codici[a][pos] = 0;
        codici[(ncodici/2)+a][pos] = 1;
        //b<nbit perchè deve arrivare sempre alla fine della tabella
        for (int b=pos+1; b<nbit; b++) {
            codici[(ncodici/2)+a][b] = codici[(ncodici/2)-1-a][b];
        }
    }
}