#include "bst.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    BST bst = BstInit();
    Item nuovo;
    for (int a=0; a<5; a++) {
        nuovo = ItemScan(stdin,KeyScan(a));
        BSTInsertR(bst,nuovo); 
    }
    Item ricerca;
    ricerca = BSTSearch(bst,Keyget(nuovo));
    Item ricerca_succ = BSTsucc(bst,Keyget(nuovo));
    Item minimo = BSTmin(bst);
    Item massimo = BSTmax(bst);
    Item ricerca_pred = BSTpred(bst,Keyget(nuovo));
    BSTFree(bst);
    return 0;
}