#include "elem_pers.h"
#include "inventario.h"

typedef struct tab_pers_ *tab_pers;


tab_pers crea_tabella_personaggi();
void carica_personaggi_da_file( tab_pers tabella_personaggi, FILE *file);

pers crea_pers_personalizzato();

pers *aggiungi_personaggio(pers *personaggio, tab_pers tab_personaggi, pers *aggiunto);
pers elimina_personaggio(tab_pers tab_personaggi, char *codice_pers);



pers *trova_personaggio(tab_pers tab_personaggi, char *codice_pers);


void formatta_stringhe_pers(pers *personaggio, char *codice, char *nome, char *classe);

void aggiungi_equipaggiamento(tab_pers tab_personaggi, tab_inv tab_inventario, char *codice_pers, char *nome_oggetto);