#include "bst.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    BST bst = BstInit();
    FILE *file = fopen("bst.txt", "r"); 
    Item nuovo;
    int elem;
    while (fscanf(file, "%d", &elem) == 1) {
        nuovo = ItemScan(file,KeyScan(elem));
        BSTInsertR(bst,nuovo); 
    }
    int a = BSTCount(bst);
    int b = AltezzaMassima(bst);
    int c = NFoglie(bst);
    int d = BSTCount_un_figlio(bst);
    printf("Numero di nodi %d\n", a);
    printf("Altezza albero %d\n", b);
    printf("N foglie %d\n", c);
    printf("N nodi senza un figlio %d\n", c);
    bst = BSTCancellaFigliSinistriDaK(bst,0);
    a = BSTCount(bst);
    b = AltezzaMassima(bst);
    c = NFoglie(bst);
    d = BSTCount_un_figlio(bst);
    puts("\nDOPO");
    printf("Numero di nodi %d\n", a);
    printf("Altezza albero %d\n", b);
    printf("N foglie %d\n", c);
    printf("N nodi senza un figlio %d\n", c);
    // Item ricerca;
    // ricerca = BSTSearch(bst,Keyget(nuovo));
    // Item ricerca_succ = BSTsucc(bst,Keyget(nuovo));
    // Item minimo = BSTmin(bst);
    // Item massimo = BSTmax(bst);
    // Item ricerca_pred = BSTpred(bst,Keyget(nuovo));
    // BSTFree(bst);
    return 0;
}