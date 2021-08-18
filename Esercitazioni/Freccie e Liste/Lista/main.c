#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"




int main() {

    FILE *ptr;

    LISTA list = ListInit();

    ptr = fopen("lista.txt", "r");
    char *string = malloc (sizeof(char));
    int size = 1;
    while (!feof(ptr)) {
        string[size-1] = getc(ptr);
        if (string[size-1] == '\n' || feof(ptr)) {
            //togliere a capo finale
            string[size-1] = '\0';
            //filtraggio linea vuota
            if (strcmp("", string) == 0) {
                break;
            }
            list = ListAddInOrder(list,string);
            printf("%s\n", string);
            fflush(stdout);
            size = 1;
        }
        else {
            size++;
        }
        void *res = realloc(string, size * sizeof(char));
    }
    FILE *output = fopen("output.txt", "w+");
    ListPrint(list,output);
    free(string);
    ListFree(list);
    return 0;
}