//modelli del calcolo combinatorio in c
#include <stdio.h>
#include <stdlib.h>

#include <algoritmi_di_ordinamento.c>

//togliere per abilitare il main
#define MAIN

typedef struct {

    int *scelte;
    int num_scelte;
    
} Livello;


int disposizioni_semplici(int *val, int *mark, int n, int *sol, int k, int count, int pos);
int disposizioni_ripetute(int *val, int n, int *sol, int k, int count, int pos);
int permutazioni_semplici(int *val, int *mark, int n, int *sol, int count, int pos);
int anagrammi_con_ripetizione(char *val, int *mark, int n, char *sol, int count, int pos);

int permutazioni_ripetute (char *sol, int n, char *dist_val, int n_dist, int *mark, int pos, int count);
int combinazioni_semplici (int *val, int *sol, int n, int k, int start, int pos, int count);
int combinazioni_con_ripetizione ( int *val, int *sol, int n, int k, int start, int pos, int count);


int principio_moltiplicazione ( Livello *corrente, int *sol, int n, int pos, int count);