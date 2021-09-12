typedef struct HEAP_ *HEAP;

typedef struct ITEM_ ITEM;
typedef int Key;

struct ITEM_ {
    Key chiave;
};


ITEM ItemScan();

//ritorna > 1 se b è maggiore di a, 0 se sono uguali
int KeyCompare(Key a, Key b);
Key KeyGet(ITEM item);


HEAP HeapInit(int maxN);
void HeapInsert(HEAP heap, ITEM K);

//heapify a partire da un determinato nodo
void Heapify(HEAP heap, int k);