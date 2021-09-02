#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scaffale.h"

struct Scaffale_ {
    //numero slot
    int k;
    //ID SCAFFALE
    char *ID_S;
    Pacco *pacchi;
};