#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "set.h"

int main () {

    SET set1 = SetInit(50);
    SET set2 = SetInit(80);

    FILE *ptr1 = fopen("gruppo1.txt", "r");
    FILE *ptr2 = fopen("gruppo2.txt", "r");

    //magari possibile senza i numeri, quando ritorno NULL mi fermo (magari)
    int n_1, n_2;
    fscanf(ptr1, "%d", &n_1);
    fscanf(ptr2, "%d", &n_2);

    int a = 0;

    Item elemento;

    for (a=0; a<n_1; a++) {
        elemento = itemScan(ptr1);
        SetFill(set1,elemento);
    }

    for (a=0; a<n_2; a++) {
        elemento = itemScan(ptr2);
        SetFill(set2,elemento);
    }

    SET unione = SetUnion(set1,set2);
    
    FILE *save = fopen("result.txt", "w");

    SetSave(unione,save);

    

    return 0;
}