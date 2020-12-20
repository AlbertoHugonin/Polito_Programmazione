#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equip_array.h"

struct tab_equip {

    int inUso;
    int vett_equipaggiamento[N_SLOT];

};



equip_array equip_array_init() {
    equip_array equipaggiamento = malloc(sizeof(equip_array));
    equipaggiamento->inUso = 0;
    //for tutto su una linea
    for (int a=0; a<N_SLOT; a++) equipaggiamento->vett_equipaggiamento[a] = -1;
    return equipaggiamento;
}

void aggiungi_oggetto_equip(int indice_equip, equip_array equipaggiamento) {

    equipaggiamento->vett_equipaggiamento[equipaggiamento->inUso] = indice_equip;
    equipaggiamento->inUso++;
}