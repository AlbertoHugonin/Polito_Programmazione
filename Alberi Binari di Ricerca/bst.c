#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo_ {

    Item elemento;
    struct Nodo_ *left;
    struct Nodo_ *right;

} Nodo;

struct BST_ {

    Nodo *radice;
    Nodo *z;
};

static Nodo *NEW(Item item, Nodo *l, Nodo *r);
static Nodo *InsertR(Nodo *corrente, Nodo *fine, Item nuovo);
static Nodo *BSTSearchR(Nodo *corrente, Nodo *fine, Key key);


BST BstInit() {

    BST albero = malloc(sizeof(* albero));
    albero->radice = (albero->z = NEW(ItemInit(),NULL,NULL));
    return albero;

}

static Nodo *NEW(Item item, Nodo *l, Nodo *r) {
    Nodo *n = malloc(sizeof(Nodo));
    n->elemento=item;
    n->left=l;
    n->right=r;
    return n;
}

void BSTInsertR(BST albero, Item nuovo) {
    //ci penso io ad agganciarlo, la root potrebbe non cambiare
    albero->radice = InsertR(albero->radice,albero->z,nuovo);
}

static Nodo *InsertR(Nodo *corrente, Nodo *fine, Item nuovo) {

    if (corrente==fine) {
        return NEW(nuovo,fine,fine);
    }
    if (ItemCompare(nuovo,corrente->elemento) > 0) {
        corrente->right=InsertR(corrente->right,fine,nuovo);
    }
    else {
        corrente->left=InsertR(corrente->left,fine,nuovo);
    }   
    //
    return corrente;
}

Item BSTSearch(BST albero, Key key) {
    return BSTSearchR(albero->radice,albero->z,key)->elemento;
}

static Nodo *BSTSearchR(Nodo *corrente, Nodo *fine, Key key) {
    if (corrente==fine) {
        return NEW(corrente->elemento,NULL,NULL);
    }
    if (KeyCompare(key,Keyget(corrente->elemento)) > 0) {
        return BSTSearchR(corrente->right,fine,key);
    }
    if (KeyCompare(key,Keyget(corrente->elemento)) < 0) {
        return BSTSearchR(corrente->left,fine,key);
    }
    return corrente;
}