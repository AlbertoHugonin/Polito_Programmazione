#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct colonna *link;
typedef struct riga *next;
struct colonna{
	int val;
	int col;
	link prox_col;
};

struct riga {
	int r;
	link head;
	next prox_rig;
};

next inizializzaLista();
void listaVisit(next riga);
next newRiga(int r,next prox_rig, link head);
link newColonna(int val, int col, link prox_col);

int main(){
	next lista = inizializzaLista();
	listaVisit(lista);

	return 0;
}

void listaVisit(next riga){
	if (riga == NULL) return;
	link colonna;
	printf("%d : ", riga->r);
	for(colonna = riga->head; colonna!= NULL; colonna= colonna->prox_col)
		printf("%d ", colonna->val);
	printf("\n");
	listaVisit(riga->prox_rig);
}

next newRiga(int r,next prox_rig, link head){
	next x = malloc(sizeof(x));
	x->head = head;
	x->prox_rig = prox_rig;
	x->r = r;
	return x;
}

link newColonna(int val, int col, link prox_col){
	link x = malloc(sizeof(x));
	x->val = val;
	x->col = col;
	x->prox_col = prox_col;
	return x;
}

next inizializzaLista(){
	next riga = NULL;
	link colonna = NULL;

	colonna = newColonna(7,5,colonna);
	colonna = newColonna(8,0, colonna);
	riga = newRiga(2,riga, colonna);

	colonna = NULL;

	colonna = newColonna(12,3,colonna);
	colonna = newColonna(11,2,colonna);
	colonna = newColonna(10,1,colonna);
	riga = newRiga(1,riga,colonna);

	colonna = NULL;

	colonna = newColonna(4,4, colonna);
	colonna = newColonna(5,3,colonna);
	riga= newRiga(0,riga,colonna);

	return riga;

}