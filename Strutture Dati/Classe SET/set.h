typedef struct set_ *SET;

#include "item.h"

//versione con intero per sovra allocare il vettore e per nascondere in caso di utilizzo della lista
SET SetInit(int MAX_N);

//inserisce un elemento nell'insieme (non ordinato)
void SetInsert(SET s, Item Val);
//legge da file e crea un insieme
void SetFill(SET s, FILE *ptr);

//ritorna unione ordinata di due insiemi O(N)
SET SetUnion(SET s1, SET s2);
//ritorna intersezione ordinata di due insiemi O(N)
SET SetInter(SET s1, SET s2);

//salva su file il contenuto dell'insieme
void SetSave(SET s, FILE *ptr);

//ordina l'insieme usando quicksort
void SetQuickSort(SET s);
