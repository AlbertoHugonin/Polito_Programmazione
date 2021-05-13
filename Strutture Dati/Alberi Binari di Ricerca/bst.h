typedef struct BST_ *BST;
#include "item.h"

BST BstInit();

void BSTInsertR(BST albero, Item nuovo);

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