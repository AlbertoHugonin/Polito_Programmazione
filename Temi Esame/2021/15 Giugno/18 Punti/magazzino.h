//FILE FORMATTATO
//C numero corridoi
//coppia ID_C id corridoio C_S numeri scaffali nel corridoio
//ID_S stringa scaffale K numero slot scaffale


#include "corridoio.h"


typedef struct Magazzino_ *Magazzino;



Magazzino MagazzinoInit();


Magazzino MagazzinoScan(FILE *struttura);

Magazzino MagazzinoScanPacco(FILE *pacchi);