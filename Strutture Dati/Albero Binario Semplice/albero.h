typedef struct albero_ *albero;


albero AlberoInit();
void AlberoFree();
albero AlberoInsert(albero tree, char *stringa);
albero tree2ListWrapper(albero tree);