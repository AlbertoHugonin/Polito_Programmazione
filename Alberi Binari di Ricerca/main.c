#include "bst.h"

int main() {

    BST bst = BstInit();
    Item nuovo;
    for (int a=0; a<5; a++) {
        nuovo = ItemScan(stdin);
        BSTInsertR(bst,nuovo); 
    }
    Item ricerca;
    ricerca = BSTSearch(bst,Keyget(nuovo));
    BSTFree(bst);
    return 0;
}