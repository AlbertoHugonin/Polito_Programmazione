typedef struct BST_ *BST;
#include "item.h"

BST BstInit();
void BSTInsertR(BST albero, Item nuovo);
Item BSTSearch(BST albero, Key key);
void BSTFree(BST albero);
void BSTPrint(BST albero);