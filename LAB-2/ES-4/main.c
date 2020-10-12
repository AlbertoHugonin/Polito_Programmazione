#include <stdio.h>
#include <stdlib.h>
#include <Algoritmi/algoritmi_di_ordinamento.c>
#define MAXS 1000

int main() {

    FILE *file = fopen("sort.txt", "r");
    
    int s;

    fscanf(file, "%d", &s);

    for (int a=0; a<s; a++) {
        int length; 
        fscanf(file, "%d", &length);
        int sequenze[MAXS] = {0};
        for (int b=0; b<length; b++) {
            fscanf(file,"%d", &sequenze[b]);
        }
        //finite le sequenze le passiamo alla funzione
        return 0;
    }
}