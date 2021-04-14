#include "arco.h"

typedef struct Nodo_l_ *Nodo_l;
typedef struct Lista_ *Lista;


Nodo_l NodoInit(Arco arco);
Lista InsertL( Lista lista, Arco arco);
Lista ListaInit(Lista lista);
void PrintList(Lista lista);

//recupera arco dalla lista dove n è il numero di posto nella lista
Arco GetArco(Lista lista, int n);