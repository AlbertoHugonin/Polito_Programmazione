
typedef struct set_ *SET;

#include "item.h"

//versione con intero per sovra allocare il vettore e per nascondere in caso di utilizzo della lista
SET SetInit(int MAX_N);
void SetFill(SET s, Item Val);
SET SetUnion(SET s1, SET s2);
void SetSave(SET s, FILE *ptr);