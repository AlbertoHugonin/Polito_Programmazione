//lista come adt di prima classe contenente item per semplicità

typedef struct list *LISTA;

LISTA ListInit();
LISTA ListAdd(LISTA list, char string[]);
LISTA ListAddInOrder(LISTA list, char string[]);
LISTA ListSearch(LISTA list, char string[]);
LISTA ListRemove(LISTA list, char string[]);
int ListPrint(LISTA list, FILE *ptr);
int ListFree(LISTA lista);