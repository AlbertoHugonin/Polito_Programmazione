typedef struct BST_ *BST;
#include "item.h"

BST BstInit();

void BSTInsertR(BST albero, Item nuovo);

int BSTCount(BST albero);

int AltezzaMassima(BST albero);

int NFoglie(BST albero);
int BSTCount_un_figlio(BST albero);



//cancella figli sinistro 
BST BSTCancellaFigliSinistriDaK(BST albero,int k);

//BST SearchByIndex trova l'item a partire dalla chiave
Item BSTSearch(BST albero, Key key);

//BST SearchByItem trova la chiave a partire dall'item
Key BSTSearchKey(BST albero, Item elemento);

void BSTFree(BST albero);

void BSTPrint(BST albero);
//da sistemare

Item BSTsucc(BST albero, Key key);
Item BSTpred(BST albero, Key key);

//
Item BSTmin(BST albero);
Item BSTmax(BST albero);
//select