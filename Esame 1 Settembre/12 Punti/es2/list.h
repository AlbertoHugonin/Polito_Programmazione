//LIST.h
//scrivere qui il codice


//nel compito l'ho chiamato Lista ma per essere compativile con purge si deve chiamare LIST
typedef struct lista_ *LIST;


//crea una lista con interi tra a e b
LIST listacreate(int a, int b);
void purge(LIST l, int div);
void StampaLista(LIST lista);