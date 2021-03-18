#include "bst.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo_ {

    Item *corrente;
    struct Nodo_ *left;
    struct Nodo_ *right;

} Nodo;

struct BST_ {

    Nodo *radice;
    Nodo *z;
};


BST BstInit() {

    BST albero = malloc(sizeof(* albero));


}