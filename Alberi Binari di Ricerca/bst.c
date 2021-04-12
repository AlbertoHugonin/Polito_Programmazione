#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo_ {

    Item elemento;
    struct Nodo_ *P;
    struct Nodo_ *left;
    struct Nodo_ *right;

} Nodo;

struct BST_ {

    Nodo *radice;
    Nodo *z;
};

static Nodo *NEW(Item item, Nodo *l, Nodo *r, Nodo *p);
static Nodo *InsertR(Nodo *corrente, Nodo *fine, Item nuovo);
static Nodo *BSTSearchR(Nodo *corrente, Nodo *fine, Key key);
static void BSTFreeR(Nodo *corrente, Nodo *fine);
static int countR(Nodo *corrente, Nodo *fine);


BST BstInit() {

    BST albero = malloc(sizeof(* albero));
    albero->radice = (albero->z = NEW(ItemInit(),NULL,NULL,NULL));
    return albero;

}

static Nodo *NEW(Item item, Nodo *l, Nodo *r, Nodo *p) {
    Nodo *n = malloc(sizeof(Nodo));
    n->elemento=item;
    n->left=l;
    n->right=r;
    n->P=p;
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

void BSTFree(BST albero) {
    if (albero == NULL) return;
    BSTFreeR(albero->radice,albero->z);
    free(albero->radice);
    free(albero);
}

static void BSTFreeR(Nodo *corrente, Nodo *fine) {

    if (corrente = fine) {
        return;
    }

    BSTFreeR(corrente->left, fine);
    BSTFreeR(corrente->right, fine);
    ItemFree(corrente->elemento);
    free(corrente);
    return;
}

static int countR(Nodo *corrente, Nodo *fine) {
    if (corrente==fine) {
        return 0;
    }
    return countR(corrente->right,fine) + countR(corrente->left,fine) + 1;
}

void BSTPrint(BST albero) {

    int n = countR(albero->radice,albero->z);
    return;

}