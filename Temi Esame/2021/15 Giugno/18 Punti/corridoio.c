#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "corridoio.h"

struct Corridoio_ {

    //numero scaffali
    int C_S;
    //identificativo corridoio
    int ID_C;
};

Corridoio CorridoioInit(int C_S, int ID_C) {
    Corridoio corridoio = malloc(sizeof(struct Corridoio_ *));
    corridoio->C_S=0;

}