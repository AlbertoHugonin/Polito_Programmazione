#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "albero.h"

//strategia albero ordinato 

struct nodo {
    char *nome;
    struct nodo *left;
    struct nodo *right;
};

struct nodo_l {
    char *nome;
    struct nodo_l *next;
};

typedef struct nodo *link;
typedef struct nodo_l *linkL;

linkL tree2List(link root, int visit);

struct albero_ {
    link padre;
    int N;
};

int insertList(char *stringa);

//variabile globale della lista visto che il prototipo non permette il passaggio della lista per valore o puntatore
linkL lista;

albero tree2ListWrapper(albero tree) {

    printf("Scegli il tipo di visita:\n");
    printf("1-Pre Order\n2-Post Order\n3-In Order\n-----------\n");
    int res = 0;
    scanf("%d", &res);
    tree2List(tree->padre,res);
    return tree;
}

int insertList(char *stringa) {

    linkL corrente = lista;

    //da rivedere le malloc
    linkL nuovo = malloc(sizeof(struct linkL*));
    nuovo->nome = malloc(strlen(stringa)*sizeof(char));
    nuovo->next=NULL;
    strcpy(nuovo->nome,stringa);

    //iteriamo la lista
    if(lista==NULL) {
        lista = nuovo;
    } else {
        while(1) {
            if (corrente->next!= NULL) {
                corrente=corrente->next;
                } else {
                    corrente->next=nuovo;
                    break;
                    }
                }
            }
        
    return 0;
}

linkL tree2List(link root, int visit) {

    if(root==NULL) {
        return lista;
    }

    switch(visit) {
        //pre order
        case 1:
            //significa stampare, seguire il ramo sinistro e poi quello destro
            // printf("%s\n", corrente->nome);
            insertList(root->nome);
            tree2List(root->left,visit);
            tree2List(root->right,visit);
            break;
        //post order
        case 2:
            tree2List(root->left,visit);
            tree2List(root->right,visit);   
            printf("%s\n", root->nome); 
            insertList(root->nome);
            break;
        //in order
        case 3:
            tree2List(root->left,visit);
            printf("%s\n", root->nome);
            tree2List(root->right,visit);
            insertList(root->nome);    
            break;
        default:
            printf("Parametro non ricoosciuto");
    }

    return lista;
}

albero AlberoInit() {

    albero tree = malloc(sizeof(struct albero *));

    tree->N=0;
    tree->padre = NULL;
}

albero AlberoInsert(albero tree, char *stringa) {

    link nuovo = malloc(sizeof(struct nodo *));
    link corrente = tree->padre;

    nuovo->nome=malloc(strlen(stringa)*sizeof(char));
    nuovo->left=NULL;
    nuovo->right=NULL;
    strcpy(nuovo->nome,stringa);

    if (tree->padre == NULL) {
        tree->padre = nuovo;
        tree->N++;
    } else {
        while(1) {
            if(strcmp(nuovo->nome,corrente->nome) > 0) {
                if(corrente->right == NULL) {
                    corrente->right = nuovo;
                    break;
                } else {
                    corrente = corrente->right;
                }
            }
            if(strcmp(nuovo->nome,corrente->nome) < 0) {
                if(corrente->left == NULL) {
                    corrente->left = nuovo;
                    break;
                } else {
                    corrente = corrente->left;
                }
            }
        }
        
    }
    return tree;
}