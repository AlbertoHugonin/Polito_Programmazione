#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo_ {

    Item elemento;
    //elemento precedente
    struct Nodo_ *P;

    struct Nodo_ *left;
    struct Nodo_ *right;
    //numero di nodi nel sottoalbero
    int N;

} Nodo;

struct BST_ {

    Nodo *radice;
    Nodo *z;
};

static Nodo *NEW(Item item, Nodo *l, Nodo *r, Nodo *p, int N);
static Nodo *InsertR(Nodo *corrente, Nodo *fine, Item nuovo, Nodo *p);
static Nodo *BSTSearchR(Nodo *corrente, Nodo *fine, Key key);
static void BSTFreeR(Nodo *corrente, Nodo *fine);
static int countR(Nodo *corrente, Nodo *fine);
static Item BSTsuccR(Nodo *corrente, Nodo *fine, Key key);
static Nodo *BSTminR(Nodo *corrente, Nodo *fine);
static Nodo *BSTmaxR(Nodo *corrente, Nodo *fine);
static Item BSTpredR(Nodo *corrente, Nodo *fine, Key key);
static Nodo *BSTSearchKeyR(Nodo *corrente, Nodo *fine, Item elemento);

BST BstInit() {

    BST albero = malloc(sizeof(* albero));
    albero->radice = (albero->z = NEW(ItemInit(),NULL,NULL,NULL,0));
    return albero;

}

static Nodo *NEW(Item item, Nodo *l, Nodo *r, Nodo *p, int N) {
    Nodo *n = malloc(sizeof(Nodo));
    n->elemento=item;
    n->left=l;
    n->right=r;
    n->P=p;
    n->N=N;
    return n;
}

void BSTInsertR(BST albero, Item nuovo) {
    //ci penso io ad agganciarlo, la root potrebbe non cambiare
    albero->radice = InsertR(albero->radice,albero->z,nuovo,albero->radice);
}

static Nodo *InsertR(Nodo *corrente, Nodo *fine, Item nuovo, Nodo *p) {

    if (corrente==fine) {
        return NEW(nuovo,fine,fine,p,1);
    }
    p=corrente;
    if (KeyCompare(Keyget(nuovo),Keyget(corrente->elemento)) > 0) {
        corrente->right=InsertR(corrente->right,fine,nuovo,p);
        corrente->left->P=corrente;
    }
    else {
        corrente->left=InsertR(corrente->left,fine,nuovo,p);
        corrente->right->P=corrente;
    }   
    //aggiornamento contatore elementi figli
    (corrente->N)++;
    return corrente;
}

Item BSTSearch(BST albero, Key key) {
    return BSTSearchR(albero->radice,albero->z,key)->elemento;
}

static Nodo *BSTSearchR(Nodo *corrente, Nodo *fine, Key key) {
    if (corrente==fine) {
        return NEW(corrente->elemento,NULL,NULL,NULL,0);
    }
    if (KeyCompare(key,Keyget(corrente->elemento)) > 0) {
        return BSTSearchR(corrente->right,fine,key);
    }
    if (KeyCompare(key,Keyget(corrente->elemento)) < 0) {
        return BSTSearchR(corrente->left,fine,key);
    }
    return corrente;
}

Key BSTSearchKey(BST albero, Item elemento) {
    return Keyget(BSTSearchKeyR(albero->radice,albero->z,elemento)->elemento);
}

static Nodo *BSTSearchKeyR(Nodo *corrente, Nodo *fine, Item elemento) {

    //se non trova nulla
    if (corrente==fine) {
        return NEW(corrente->elemento,NULL,NULL,NULL,-1);
    }
    if (ItemCompare(elemento,corrente->elemento) > 0) {
        return BSTSearchKeyR(corrente->right,fine,elemento);
    }
    if (ItemCompare(elemento,corrente->elemento) < 0) {
        return BSTSearchKeyR(corrente->left,fine,elemento);
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

Item BSTsucc(BST albero, Key key) {
    return BSTsuccR(albero->radice,albero->z,key);
}

//ricerca del successore
static Item BSTsuccR(Nodo *corrente, Nodo *fine, Key key) {

    Nodo *p;
    //arrivato in fondo non trovato
    if (corrente==fine) {
        return ItemInit();
    }
    //appena trova
    if (KeyCompare(key, Keyget(corrente->elemento)) == 0) {
        //il nodo appena trovato ha un figlio destro
        if (corrente->right != fine) {
            BSTminR(corrente->right,fine);
        }
        else {
            p = corrente->P;
            while( corrente == p->right) {
                corrente = p;
                p = corrente->P;
            }
        }
        //serve nel caso sia il massimo dell'albero
        if(corrente==fine) return ItemInit();
        return p->elemento;
    }

    //non trovato riccorriamo
    if (KeyCompare(key, Keyget(corrente->elemento)) != 0) {
        return BSTsuccR(corrente->left,fine,key);
    }
    return BSTsuccR(corrente->right,fine,key);
}


Item BSTpred(BST albero, Key key) {
    return BSTpredR(albero->radice,albero->z,key);
}

//ricerca del successore
static Item BSTpredR(Nodo *corrente, Nodo *fine, Key key) {

    Nodo *p;
    //arrivato in fondo non trovato
    if (corrente==fine) {
        return ItemInit();
    }
    //appena trova
    if (KeyCompare(key, Keyget(corrente->elemento)) == 0) {
        //il nodo appena trovato ha un figlio destro
        if (corrente->left != fine) {
            BSTmaxR(corrente->left,fine);
        }
        else {
            p = corrente->P;
            while( corrente == p->left) {
                corrente = p;
                p = corrente->P;
            }
        }
        //serve nel caso sia il massimo dell'albero
        if(corrente==fine) return ItemInit();
        return p->elemento;
    }

    //non trovato riccorriamo
    if (KeyCompare(key, Keyget(corrente->elemento)) != 0) {
        return BSTpredR(corrente->left,fine,key);
    }
    return BSTpredR(corrente->right,fine,key);
}

Item BSTmin(BST albero) {
    Nodo *trovato = BSTminR(albero->radice,albero->z);
    return trovato->elemento;
}

static Nodo *BSTminR(Nodo *corrente, Nodo *fine) {
    if (corrente->left==fine) {
        return corrente;
    }
    return BSTminR(corrente->left,fine);
}

Item BSTmax(BST albero) {
    Nodo *trovato = BSTmaxR(albero->radice,albero->z);
    return trovato->elemento;
}

static Nodo *BSTmaxR(Nodo *corrente, Nodo *fine) {

    if (corrente->right==fine) {
        return corrente;
    }
    return BSTmaxR(corrente->right,fine);
}