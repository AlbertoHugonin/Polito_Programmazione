#include <stdlib.h>
#include <stdio.h>

#include "list.h"

int main() {

    LIST lista = listacreate(0,5);
    //se resto per 2 uguale 0 allora entro
    purge(lista,2);
    return 0;
}