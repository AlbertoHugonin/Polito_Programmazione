#include <stdlib.h>
#include <stdio.h>

#include "list.h"

int main() {

    LIST lista = listacreate(0,9);
    //se resto per 2 uguale 0 allora entro
    StampaLista(lista);
    purge(lista,3);
    StampaLista(lista);
    return 0;
}