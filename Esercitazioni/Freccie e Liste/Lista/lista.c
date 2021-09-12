#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"



typedef struct node *link;

struct list {
link head;
link tail;
int N;

};

struct node {
    
    char *string;
    link next;

};

static int ListFreeR(link node);

LISTA ListInit() {
    LISTA list = malloc(sizeof(* list));
    list->head=NULL;
    list->tail=NULL;
    list->N=0;
    return list;
}

int ListFree(LISTA lista) {
    if (lista->N == 0) {
        return 1;
    }
    ListFreeR(lista->head);
    free(lista);
    return 0;
}

int ListPrint(LISTA list, FILE *ptr) {
    if (list->head == NULL) {
        return 1;
    }
    link nodo = list->head;
    while (nodo != NULL) {
        fprintf(ptr,"%s\n",nodo->string);
        nodo = nodo->next;
    }
    return 0;
}
static int ListFreeR(link node) {

    if (node->next != NULL) {
        ListFreeR(node->next);
    }
    free(node->string);
    free(node);
    return 0;
}

LISTA ListAdd(LISTA list, char string[]) {
    link nodo = malloc(sizeof(* nodo));
    nodo->string = malloc(strlen(string) * sizeof(char));
    nodo->next = NULL;
    strcpy(nodo->string,string);
    if (list->head==NULL) {
        list->head = nodo;
    }
    else {
        link corrente = list->head;
        while (corrente->next != NULL) {
            corrente = corrente->next;
        }
        corrente->next = nodo;
        list->tail = corrente->next;
    }
    list->N++;
    return list;
}

LISTA ListAddInOrder(LISTA list, char string[]) {

    link nodo = malloc(sizeof(struct node *));
    nodo->string = malloc(strlen(string) * sizeof(char));
    nodo->next = NULL;
    strcpy(nodo->string,string);
    if (list->head==NULL) {
        list->head = nodo;
    }
    else {
        link corrente = list->head;
        while (corrente->next != NULL) {
            if (strcmp(string,corrente->string) > 0 && strcmp(string,corrente->next->string) < 0) {
                //lo metto in mezzo
                nodo->next = corrente->next;
                corrente->next=nodo;
                list->N++;
                return list;
            }
            corrente = corrente->next;
        }
        corrente->next = nodo;
        list->tail = corrente->next;
    }
    list->N++;
    return list;
}