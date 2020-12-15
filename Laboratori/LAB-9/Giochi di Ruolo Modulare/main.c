#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//prima uno poi l'altro in questo caso è uguale
#include "inventario.h"
#include "personaggi.h"
//////


int main() {

    FILE *file_inventario = fopen("inventario.txt", "r");
    FILE *file_personaggi = fopen("pg.txt", "r");
    
    tab_inv *tabella_inventario  = crea_inventario();
    
    tabella_inventario = carica_inventario(file_inventario,tabella_inventario);

    //era anche possibile nascondere il puntatore alla funzione main (vedere parte modularità)
    tab_pers *tabella_personaggi = crea_tabella_personaggi();
    
    carica_personaggi_da_file(tabella_personaggi,file_personaggi);

    //versione crea personaggio personalizzato che si appoggia a crea_pers e chiede i dettagli del personaggio
    pers *personaggio = crea_pers_personalizzato();

    aggiungi_personaggio(personaggio,tabella_personaggi, NULL);

    //elimina il personaggio con estrazione
    elimina_personaggio(tabella_personaggi, "PG0001");


    aggiungi_equipaggiamento(tabella_personaggi, tabella_inventario, "PG0002", "Escutcheon");
    aggiungi_equipaggiamento(tabella_personaggi, tabella_inventario, "PG0002", "Escutcheon");

    aggiungi_equipaggiamento(tabella_personaggi, tabella_inventario, "PG0002", "TalismanoNero");
    aggiungi_equipaggiamento(tabella_personaggi, tabella_inventario, "PG0002", "DagaRunica");
    
    elimina_equipaggiamento(tabella_personaggi, "PG0002", "TalismanoNero");


    calcola_statistiche(tabella_personaggi,"PG0002");

    //si puo' fare anche per l'inventario
    cancella_tabella_personaggi(tabella_personaggi);

    return 0;
}