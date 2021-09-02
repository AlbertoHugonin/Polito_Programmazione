

typedef struct Corridoio_ *Corridoio;

Corridoio CorridoioInit(int C_S, int ID_C);


//mette il pacco al posto giusto dato id scaffale
Corridoio CorridoioScanPacco(char *ID_S);