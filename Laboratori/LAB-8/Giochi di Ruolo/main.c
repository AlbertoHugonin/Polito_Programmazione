#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INV 50
//in una lista l'elenco dei personaggi
//vettore di strutture l'elenco di oggetti


//parte inventario
typedef struct stat_ {

    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;

} stat;

typedef struct elem_inv_ {

    //cosi non dobbiamo allocare noi
    char *nome; 
    char *tipo;
    stat statistiche;

} elem_inv, vett_equi;

typedef struct tab_inv_ {

    elem_inv *vett_inventario;
    int n;

} tab_inv;

//////////////////////////////////

typedef struct tab_equi_ {

    int inUso;
    vett_equi *vett_equipaggiamento;

} tab_equi;

typedef struct pers_ {

    char *codice;
    char *nome;
    char *classe;
    stat statistiche;
    tab_equi tab_equipaggiamento;

    struct pers_ *next;

} pers;

//wrapper della lista personaggi
typedef struct tab_pers_ {

    pers *head;
    pers *tail;
    int n_personaggi;

} tab_pers;

//////////////////////////////////////

tab_inv *carica_inventario(FILE *ptr, tab_inv *inventario);
tab_inv *crea_inventario();
void aggiungi_elemento_inventario(FILE *ptr, tab_inv *inventario, int a);
int lunghezza_stringa(char *stringa, int max);

///////////////////////////////////////
tab_pers *crea_tabella_personaggi();
void carica_personaggi_da_file( tab_pers *tabella_personaggi, FILE *file);
pers crea_pers_personalizzato();
pers *aggiungi_personaggio(pers personaggio, tab_pers *tab_personaggi, pers *aggiunto);

void aggiungi_equipaggiamento(tab_pers *tab_personaggi, tab_inv *tab_inventario, char *codice_pers, char *nome_oggetto);

pers elimina_personaggio(tab_pers *tab_personaggi, char *codice_pers);

void calcola_statistiche(tab_pers *tab_personaggi, char *codice_pers);

pers *trova_personaggio(tab_pers *tab_personaggi, char *codice_pers);

int trova_oggetto_equipaggiamento(pers *personaggio, char *nome_oggetto);
int trova_oggetto_inventario(tab_inv *tab_inventario, char *nome_oggetto);
//////////////////////////////////////


int main() {
    //caricare inventario
    tab_inv *tabella_inventario  = crea_inventario();

    FILE *file_inventario = fopen("inventario.txt", "r");


    tabella_inventario = carica_inventario(file_inventario,tabella_inventario);

    //era anche possibile nascondere il puntatore alla funzione main (vedere parte modularità)
    tab_pers *tabella_personaggi = crea_tabella_personaggi();

    FILE *file_personaggi = fopen("pg.txt", "r");

    carica_personaggi_da_file(tabella_personaggi,file_personaggi);

    //crea personaggio (puo' esere usata anche dalla carica personaggi)
    //pers personaggio = crea_pers_personalizzato();

    //aggiungi personaggio
    //aggiungi_personaggio(personaggio,tabella_personaggi, NULL);

    elimina_personaggio(tabella_personaggi, "PG0001");

    //elimina personaggio, se glielo passiamo elimina quello se mettiamo una stringa cerchiamo il suo id
    //elimina_personaggio(tabella_personaggi, personaggio.codice);

    aggiungi_equipaggiamento(tabella_personaggi, tabella_inventario, "PG0002", "Escutcheon");
    aggiungi_equipaggiamento(tabella_personaggi, tabella_inventario, "PG0002", "Escutcheon");
    aggiungi_equipaggiamento(tabella_personaggi, tabella_inventario, "PG0002", "TalismanoNero");
    calcola_statistiche(tabella_personaggi,"PG0002");
    return 0;
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

    printf("Statistiche di %s sono: HP < %d > MP < %d > ATK < %d > DEF < %d > MAG < %d > SPR < %d >", codice_pers, statistiche_base.hp, statistiche_base.mp, statistiche_base.atk, statistiche_base.def, statistiche_base.mag, statistiche_base.spr);
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

int trova_oggetto_inventario(tab_inv *tab_inventario, char *nome_oggetto) {

    int pos;
    for (pos = 0; pos<tab_inventario->n; pos++) {
        if (strcmp(tab_inventario->vett_inventario[pos].nome,nome_oggetto) == 0) {
            return pos;
        }
    }
    return -1;

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

pers elimina_personaggio(tab_pers *tab_personaggi, char *codice_pers) {

    pers *corrente = tab_personaggi->head;
    pers *ritorno;

    int strb = strncmp(corrente->codice, codice_pers, 6*sizeof(char));
    if (strb == 0) {
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
    personaggio->tab_equipaggiamento.inUso=0;
    personaggio->tab_equipaggiamento.vett_equipaggiamento=NULL;

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
    personaggio->next = NULL;

    return *personaggio;
}

//si occupa di prendere i dati da file, creare con essi un personaggio e farlo aggiungere alla funziona aggiungi personaggio
void carica_personaggi_da_file(tab_pers *tabella_personaggi, FILE *file) {

    //creiamo il primo personaggio
    pers *personaggio = malloc(sizeof(pers));
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
        personaggio->next = NULL;
        personaggio->tab_equipaggiamento.inUso=0;
        personaggio->tab_equipaggiamento.vett_equipaggiamento=NULL;
        aggiunto = aggiungi_personaggio(*personaggio, tabella_personaggi, aggiunto);
        free(personaggio);
        personaggio = malloc(sizeof(pers));
    }

    return;
}

pers *aggiungi_personaggio(pers personaggio, tab_pers *tab_personaggi, pers *aggiunto) {

    //questa malloc risolve tutto, senza memcpy è come se copiasse il puntatore e non il contenuto (non è la strdup che f anche la malloc)
    pers *nodo = malloc(sizeof(pers));
    memcpy(nodo,&personaggio,sizeof(pers));
    nodo->next=NULL;

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



tab_pers *crea_tabella_personaggi() {
    
    tab_pers *tab_personaggi = malloc(sizeof(tab_pers));
    
    tab_personaggi->n_personaggi = 0;
    tab_personaggi->head = NULL;
    tab_personaggi->tail = NULL;

    return tab_personaggi;
}


tab_inv *crea_inventario() {

    tab_inv *inventario = malloc (sizeof(tab_inv));

    inventario->n=0;
    inventario->vett_inventario=NULL;

    return inventario;
}

tab_inv *carica_inventario(FILE *ptr, tab_inv *inventario) {

    int n_elementi;
    fscanf(ptr, "%d", &n_elementi);

    //allocazione vett inventario
    inventario->vett_inventario = malloc(n_elementi*sizeof(elem_inv));

    for (int a=0; a<n_elementi; a++) {
        aggiungi_elemento_inventario(ptr,inventario,a);
    }

    return inventario;

}

void aggiungi_elemento_inventario(FILE *ptr, tab_inv *inventario, int a) {

    elem_inv *corrente = inventario->vett_inventario+a;

    int n;
    char cache[MAX_INV];

    fscanf(ptr,"%s", cache);
    corrente->nome = strdup(cache);
    fscanf(ptr,"%s", cache);
    corrente->tipo = strdup(cache);

    stat *ptr_stat = &corrente->statistiche;

    //il simbolo & fa riferimento all'ultimo nella sequenza ->sdddf->atk (è l'unica spiegazione)
    fscanf(ptr, "%d %d %d %d %d %d", &ptr_stat->hp, &ptr_stat->mp, &ptr_stat->atk, &ptr_stat->def, &ptr_stat->mag, &ptr_stat->spr);

    inventario->n++;
    return;
}