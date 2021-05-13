//item caratterizzato da due interi S (source), D (destination), P (peso), che rappresentano l'arco piu' generale possibile


typedef struct Arco_ *Arco;


Arco ArcoInit(int S, int D, int P);
void PrintArco(Arco arco);
int GetSource(Arco arco);
int GetDestination(Arco arco);
//check per verificare che arco sia dummy, 0 se dummy
int isDummy(Arco arco);