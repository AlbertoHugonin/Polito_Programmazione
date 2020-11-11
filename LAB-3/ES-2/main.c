#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

int test = 50; /* solo il byte meno significativo !=0, gli altri tutti ==0 */
  char *pchar = (char *)&test; /* punta al byte di indirizzo pi� piccolo */
  /* guarda il byte di indirizzo pi� piccolo: se ==0 Big Endian */
  return (*pchar == 0); /* sintassi di tipo puntatore */
  /* return (pchar[0] == 0); */ /*  sintassi alternativa a vettore */

    return 0;
}