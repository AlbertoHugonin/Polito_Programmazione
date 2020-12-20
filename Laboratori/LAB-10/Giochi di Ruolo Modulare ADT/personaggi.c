#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggi.h"
#define MAX_INV 50

//wrapper della lista personaggi
struct tab_pers_ {

    pers *head;
    pers *tail;
    int n_personaggi;

};


tab_pers crea_tabella_personaggi() {
    
    tab_pers tab_personaggi = malloc(sizeof(tab_pers));
    
    tab_personaggi->n_personaggi = 0;
    tab_personaggi->head = NULL;
    tab_personaggi->tail = NULL;

    return tab_personaggi;
}

pers *trova_personaggio(tab_pers tab_personaggi, char *codice_pers) {

    pers *corrente = tab_personaggi->head;

    while (corrente->next != NULL && strcmp(corrente->codice,codice_pers) != 0) {
        corrente=corrente->next;
    }
    if (strcmp(corrente->codice,codice_pers) != 0) {
        puts("Personaggio non trovato");
        return NULL;
    }

    return corrente;
}

pers elimina_personaggio(tab_pers tab_personaggi, char *codice_pers) {

    pers *corrente = tab_personaggi->head;
    pers *ritorno;

    if (strcmp(corrente->codice,codice_pers) == 0) {
        tab_personaggi->head=corrente->next;
        corrente->next=NULL;
        tab_personaggi->n_personaggi--;
        return *corrente;
    }

    while (corrente->next != NULL && strcmp(corrente->next->codice,codice_pers) != 0) {
        corrente=corrente->next;
    }
    //backup del personaggio
    ritorno=corrente->next;
    //bypassiamo il nodo
    corrente->next=ritorno->next;
    //aggiornamento coda
    if (tab_personaggi->tail == ritorno) {
        tab_personaggi->tail=corrente;
    }
    ritorno->next=NULL;

    return *ritorno;
}

pers crea_pers_personalizzato() {

    pers *personaggio = malloc(sizeof(pers));

    int n;

    char codice[MAX_INV];
    char nome[MAX_INV];
    char classe[MAX_INV];

    puts("Inserisci le seguenti informazioni:");
    puts("< Codice > < Nome > < Classe > < HP > < MP > < ATK > < DEF > < MAG > < SPR >");
    fflush(stdin);
    fscanf(stdin, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &personaggio->statistiche.hp, &personaggio->statistiche.mp, &personaggio->statistiche.atk, &personaggio->statistiche.def, &personaggio->statistiche.mag, &personaggio->statistiche.spr);
    formatta_stringhe_pers(personaggio,codice,nome,classe);
    return *personaggio;
}

//si occupa di prendere i dati da file, creare con essi un personaggio e farlo aggiungere alla funziona aggiungi personaggio
void carica_personaggi_da_file(tab_pers tabella_personaggi, FILE *file) {

    //creiamo il primo personaggio
    pers *personaggio = malloc(sizeof(pers));
    pers *aggiunto = NULL;
    while (pers_read(file,personaggio) != 0)
    {
        aggiunto = aggiungi_personaggio(personaggio, tabella_personaggi, aggiunto);
        personaggio = malloc(sizeof(pers));
    }

    return;
}

//per non sprecare spazio
void formatta_stringhe_pers(pers *personaggio, char *codice, char *nome, char *classe)
{
    personaggio->codice = strdup(codice);
    ///////
    personaggio->nome = strdup(nome);
    ///////
    personaggio->classe = strdup(classe);
    
    personaggio->next = NULL;
}

pers *aggiungi_personaggio(pers *nodo, tab_pers tab_personaggi, pers *aggiunto) {

    if (tab_personaggi->head == NULL) {
        tab_personaggi->head=nodo;
        tab_personaggi->tail=nodo;
        tab_personaggi->n_personaggi++;
        return nodo;
    }
    else {
        //versione solo inserimento in coda
        if (aggiunto != NULL) {
            //usiamo il riferimento
            aggiunto->next=nodo;
            tab_personaggi->tail=nodo;
            tab_personaggi->n_personaggi++;
            return nodo;
        } else {
            //allora dobbiamo scorrere la lista
            pers *corrente = tab_personaggi->head;
            while (corrente->next != NULL) {
                corrente = corrente->next;
            }
            corrente->next=nodo;
            tab_personaggi->tail=nodo;
            tab_personaggi->n_personaggi++;
            return nodo;
        }

    }

}

void aggiungi_equipaggiamento(tab_pers tab_personaggi, tab_inv tab_inventario, char *codice_pers, char *nome_oggetto) {

    pers *corrente = trova_personaggio(tab_personaggi,codice_pers);

    if (corrente == NULL) {
        puts("Personaggio  non trovato, equipaggiamento non aggiornato");
        return;
    }

    int indice = trova_oggetto_inventario(tab_inventario, nome_oggetto);

    if (indice == -1) {
        puts("Oggetto non trovato, equipaggiamento non aggiornato");
        return;
    }

    aggiungi_oggetto_equip(indice,corrente->array_equipaggiamento);

    return;
}