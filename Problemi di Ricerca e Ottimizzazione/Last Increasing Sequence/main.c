#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int powerset_disposizioni_ripetute (int *val, int *sol, int k, int pos, int count, int *bs, int *ml);


//TODO


//trovare la sottosequenza di lunghezza (K) massima composta da tutti elementi crescenti presi a gruppi di k dentro una sequenza lunga n
//utilizzando il metodo di calcolo del powerset delle disposizioni ripetute con k crescente senza la soluzione vuota
int main() {

}



//0 se elemento non preso, 1 se elemento preso, bs contiene la migliore soluzione, ml la lunghezza della migliore soluzione, k è la lunghezza corrente
int powerset_disposizioni_ripetute (int *val, int *sol, int k, int pos, int count, int *bs, int *ml) {

    if (pos>=k) {

        //controllare la soluzione e ritornare
        return count+1;
    }


    sol[pos] = 0;
    //non include l'elemento
    count = powerset_disposizioni_ripetute(val,sol,k,pos+1,count,bs,ml);
    //include l'elemento nei livelli successivi
    sol[pos] = 1;
    count = powerset_disposizioni_ripetute(val,sol,k,pos+1,count,bs,ml);
    return count;


}