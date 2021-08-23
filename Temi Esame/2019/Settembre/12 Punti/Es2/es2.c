#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <albero.h>


int main() {
    albero tree = AlberoInit();

    FILE *ptr = fopen("albero_genialogico.txt","r");
    int N=1;
    char *stringa = malloc(N*sizeof(char));

    while(!feof(ptr)) {

        stringa[N-1] = getc(ptr);
        if(stringa[N-1] == '\n' || feof(ptr)) {
            stringa[N-1] = '\0';
            AlberoInsert(tree,stringa);
            N=1;
        } else {
            N++;
            void *test = realloc(stringa,N*sizeof(char));

        }
        
    }

    tree2ListWrapper(tree);

    return 0;



}