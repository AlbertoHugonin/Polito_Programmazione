#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggi.h"
#define MAX_INV 50


tab_pers *crea_tabella_personaggi() {
    
    tab_pers *tab_personaggi = malloc(sizeof(tab_pers));
    
    tab_personaggi->n_personaggi = 0;
    tab_personaggi->head = NULL;
    tab_personaggi->tail = NULL;

    return tab_personaggi;
}

void calcola_statistiche(tab_pers *tab_personaggi, char *codice_pers) {

    pers *personaggio = trova_personaggio(tab_personaggi,codice_pers);
    stat statistiche_base;

    memcpy(&statistiche_base,&personaggio->statistiche,sizeof(stat));

    stat *equi_corrente;


    for (int a=0; a<personaggio->tab_equipaggiamento.inUso; a++) {

        equi_corrente = &personaggio->tab_equipaggiamento.vett_equipaggiamento[a].statistiche;

        statistiche_base.hp += equi_corrente->hp;
        statistiche_base.atk += equi_corrente->atk;
        statistiche_base.def += equi_corrente->def;
        statistiche_base.mag += equi_corrente->mag;
        statistiche_base.mp += equi_corrente->mp;
        statistiche_base.spr += equi_corrente->spr;
    }

    printf("Statistiche di %s sono: HP < %d > MP < %d > ATK < %d > DEF < %d > MAG < %d > SPR < %d >\n", codice_pers, statistiche_base.hp, statistiche_base.mp, statistiche_base.atk, statistiche_base.def, statistiche_base.mag, statistiche_base.spr);
    fflush(stdin);
    return;
}

pers *trova_personaggio(tab_pers *tab_personaggi, char *codice_pers) {

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

int trova_oggetto_equipaggiamento(pers *personaggio, char *nome_oggetto) {

    int pos;
    for (pos = 0; pos<personaggio->tab_equipaggiamento.inUso; pos++) {
        if (strcmp(personaggio->tab_equipaggiamento.vett_equipaggiamento[pos].nome,nome_oggetto) == 0) {
            return pos;
        }
    }
    return -1;

}

void aggiungi_equipaggiamento(tab_pers *tab_personaggi, tab_inv *tab_inventario, char *codice_pers, char *nome_oggetto) {

    pers *corrente = trova_personaggio(tab_personaggi,codice_pers);

    if (corrente == NULL) {
        puts("Personaggio  non trovato, equipaggiamento non aggiornato");
        return;
    }

    int pos = trova_oggetto_inventario(tab_inventario, nome_oggetto);

    if (pos == -1) {
        puts("Oggetto non trovato, equipaggiamento non aggiornato");
        return;
    }

    tab_equi *tab_equipaggiamento = &corrente->tab_equipaggiamento;

    if (trova_oggetto_equipaggiamento(corrente, nome_oggetto) != -1) {
        //oggetto già presente dentro equipaggiamento
        puts("Oggetto già presente dentro equipaggiamento, non verrà aggiunto");
        return;
    }

    vett_equi *nuovo_equip = malloc((tab_equipaggiamento->inUso+1)*sizeof(vett_equi));
    memcpy(nuovo_equip,tab_equipaggiamento->vett_equipaggiamento,tab_equipaggiamento->inUso*sizeof(vett_equi));
    nuovo_equip[tab_equipaggiamento->inUso] = tab_inventario->vett_inventario[pos];

    tab_equipaggiamento->vett_equipaggiamento=nuovo_equip;
    tab_equipaggiamento->inUso++;

    return;
}

void elimina_equipaggiamento(tab_pers *tab_personaggi, char *codice_pers, char *nome_oggetto) {

    pers *corrente = trova_personaggio(tab_personaggi,codice_pers);

    if (corrente == NULL) {
        puts("Personaggio  non trovato, equipaggiamento non aggiornato");
        return;
    }

    int pos = trova_oggetto_equipaggiamento(corrente, nome_oggetto);

    if (pos == -1) {
        //oggetto già presente dentro equipaggiamento
        puts("Oggetto non presente dentro equipaggiamento, equipaggiamento non aggiornato");
        return;
    }

    tab_equi *tab_equipaggiamento = &corrente->tab_equipaggiamento;


    vett_equi *nuovo_equip = malloc((tab_equipaggiamento->inUso-1)*sizeof(vett_equi));

    int n = 0;
    for (int a=0; a<corrente->tab_equipaggiamento.inUso; a++) {
        if (a != pos) {
            nuovo_equip[n] = tab_equipaggiamento->vett_equipaggiamento[a];
            n++;
        }
    }

    //come alternativa si potrebbe usare memmove

    tab_equipaggiamento->vett_equipaggiamento=nuovo_equip;
    tab_equipaggiamento->inUso--;

    return;

}

pers elimina_personaggio(tab_pers *tab_personaggi, char *codice_pers) {

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
    tab_personaggi->n_personaggi--;
    return *ritorno;
}

//crea e inizializza personaggio
pers *crea_pers() {
    pers *personaggio = malloc(sizeof(pers));
    personaggio->tab_equipaggiamento.inUso=0;
    personaggio->tab_equipaggiamento.vett_equipaggiamento=NULL;
    personaggio->next = NULL;
    return personaggio;
}

pers *crea_pers_personalizzato() {

    pers *personaggio = crea_pers();

    int n;

    char codice[MAX_INV];
    char nome[MAX_INV];
    char classe[MAX_INV];

    puts("Inserisci le seguenti informazioni:");
    puts("< Codice > < Nome > < Classe > < HP > < MP > < ATK > < DEF > < MAG > < SPR >");
    fflush(stdin);
    fscanf(stdin, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &personaggio->statistiche.hp, &personaggio->statistiche.mp, &personaggio->statistiche.atk, &personaggio->statistiche.def, &personaggio->statistiche.mag, &personaggio->statistiche.spr);
    personaggio->codice = strdup(codice);
    personaggio->nome = strdup(nome);
    personaggio->classe = strdup(classe);
    return personaggio;
}

//si occupa di prendere i dati da file, creare con essi un personaggio e farlo aggiungere alla funziona aggiungi personaggio
void carica_personaggi_da_file(tab_pers *tabella_personaggi, FILE *file) {

    //creiamo il primo personaggio
    pers *personaggio = crea_pers();
    pers *aggiunto = NULL;


    int n;

    char codice[MAX_INV];
    char nome[MAX_INV];
    char classe[MAX_INV];

    while (fscanf(file, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &personaggio->statistiche.hp, &personaggio->statistiche.mp, &personaggio->statistiche.atk, &personaggio->statistiche.def, &personaggio->statistiche.mag, &personaggio->statistiche.spr) != EOF)
    {
        personaggio->codice = strdup(codice);
        personaggio->nome = strdup(nome);
        personaggio->classe = strdup(classe);
        //ritorna ultimo personaggio aggiunto per non scorrere di nuovo la lista
        aggiunto = aggiungi_personaggio(personaggio, tabella_personaggi, aggiunto);
        personaggio = crea_pers();
    }

    return;
}

pers *aggiungi_personaggio(pers *personaggio, tab_pers *tab_personaggi, pers *aggiunto) {

    //aggiunta con lista vuota
    if (tab_personaggi->head == NULL) {
        tab_personaggi->head=personaggio;
        tab_personaggi->tail=personaggio;
        tab_personaggi->n_personaggi++;
        return personaggio;
    }
    else {
        //aggiunta in coda utilizzando puntatore ultimo elemento passato per riferimento per evitare di passare su tutta la lista
        if (aggiunto != NULL) {
            //usiamo il riferimento
            aggiunto->next=personaggio;
            tab_personaggi->tail=personaggio;
            tab_personaggi->n_personaggi++;
            return personaggio;
        } else {
            //aggiunta in coda scorrendo tutta la lista
            pers *corrente = tab_personaggi->head;
            //arriva fino all'ultimo nodo
            while (corrente->next != NULL) {
                corrente = corrente->next;
            }
            corrente->next=personaggio;
            tab_personaggi->tail=personaggio;
            tab_personaggi->n_personaggi++;
            return personaggio;
        }

    }

}

int cancella_tabella_personaggi(tab_pers *tabella_pers) {

    pers *corrente = tabella_pers->head;
    pers *precedente;

    for (precedente = corrente; corrente != NULL, precedente = corrente;) {
        corrente = corrente->next;
        //facciamo free equipaggiamento
        free(precedente->classe);
        free(precedente->codice);
        free(precedente->nome);
        free(precedente);
    }
    return 0;
}