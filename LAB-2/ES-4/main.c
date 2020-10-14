#include <stdio.h>
#include <stdlib.h>
#include <Algoritmi/algoritmi_di_ordinamento.c>
#define MAXS 1000

void stampa_risultato(risultato res, int length);

int main() {

    FILE *file = fopen("sort.txt", "r");
    
    int s;
    int length;
    int sequenze[MAXS] = {0};
    risultato res;

    fscanf(file, "%d", &s);

    for (int a=0; a<s; a++) {

        fscanf(file, "%d", &length);
        
        for (int b=0; b<length; b++) {
            fscanf(file,"%d", &sequenze[b]);
        }
        //finite le sequenze le passiamo alla funzione
        puts("-Insertion Sort");
        res = insertion_sort(sequenze,length);
        stampa_risultato(res,length);
        puts("\n-Bubble Sort");
        res = bubble_sort(sequenze,length);
        stampa_risultato(res,length);
        puts("\n-Selection Sort");
        res = selection_sort(sequenze,length);
        stampa_risultato(res,length);
        puts("\n||||||||||||||||||||||||||||||||||||||||||||||");
    }
    return 0;
}


void stampa_risultato(risultato res, int length) {

    int b=0;
    printf("Numero totale di scambi %d, numero di iterazioni del ciclo esterno %d, numero totale di iterazioni %d\n", res.scambi, res.iterazioni_ciclo_esterno, res.num_totale_iterazioni);
    printf("Numero di iterazioni del ciclo interno per ogni passo del ciclo esterno: ");
    for (b=0; b<length; b++) {
        printf("%d ", res.iterazioni_per_ciclo_interno[b]);
    }
    printf("\nVettore ordinato: ");
    for (b=0; b<length; b++) {
        printf("%d ", res.V[b]);
    }
    return;
}