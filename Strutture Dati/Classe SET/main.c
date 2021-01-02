#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "set.h"

int main () {

    SET set1 = SetInit(50);
    SET set2 = SetInit(80);

    FILE *ptr1 = fopen("gruppo1.txt", "r");
    FILE *ptr2 = fopen("gruppo2.txt", "r");

    SetFill(set1,ptr1);
    SetFill(set2,ptr2);
    
    SET unione = SetUnion(set1,set2);
    SET intersezione = SetInter(set1,set2);
    
    FILE *save = fopen("result.txt", "w");

    fprintf(save,"Insieme 1\n");
    SetSave(set1,save);
    fprintf(save,"\nInsieme 2\n");
    SetSave(set2,save);
    fprintf(save,"\nInsieme Unione 1-2\n");
    SetSave(unione,save);
    fprintf(save,"\nInsieme Intersezione 1-2\n");
    SetSave(intersezione,save);
    

    return 0;
}