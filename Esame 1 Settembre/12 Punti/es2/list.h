//LIST.h
//scrivere qui il codice


//nel compito l'ho chiamato Lista ma per essere compativile con purge si deve chiamare LIST
typedef struct lista_ *LIST;


LIST listacreate();
void purge(LIST l, int div);