#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>



int findBound(int *V, int N, int *lp, int *rp);
void dec(int *V, int l, int r);
int **malloc2d(int N);
int findmin(int *V, int l, int r);

//ritorna indice del minimo nel vettore
int findmin(int *V, int l, int r) {

    int min = V[l];
    int indice = l;

    for (int a=l+1; a<=r; a++) {
        if (V[a] < min) {
            min = V[a];
            indice = a;
        }
    }
return min;
}


void dec(int *V, int l, int r) {
    for (int a=l; a<=r; a++) {
        V[a]--;
    }
}

//obbiettivo è trasformare V in un vettore di tutti 0 con il minior numero di chiamare a findbound e dec

int main() {

    int *lp = malloc(sizeof(int));
    int *rp = malloc(sizeof(int));

    int N = 8;
    int V[] = { 3,1,2,0,0,3,0,5 };
    *lp = 0;
    *rp = N;
    // int V[] = { 0,0,3,0,0,5};

    int n_chiamate_bound = 0;
    int n_chiamate_dec = 0;
    int min;

    while(1) {

        int ret = findBound(V,N,lp,rp);
        n_chiamate_bound++;
        if (ret == 0) {
            break;
        }
        min = findmin(V,*lp,*rp);
        for (int a=0; a<min; a++) {
            dec(V,*lp,*rp);
            n_chiamate_dec++;

        }
        *lp = 0;
        *rp = N;
    }

    return 0;
}

//ritorna 1 se c'è un qualuque sottovettore contenente una sequenza > 0, ritorna 0 se no
//ritorna inoltre tramite puntatori gli estremi sinistro e destro della sequenza a lunghezza massima con valori > 0
int findBound(int *V, int N, int *lp, int *rp) {

    for (int a=*lp; a<*rp; a++) {
        printf("%d ", V[a]);
        fflush(stdout);
    }
    puts("");

    int l1 = -1, l2 = -1, r1 = -1, r2 = -1;

    int flag = 0;

    for (int i=*lp; i<*rp; i++) {

        
        if (V[i] != 0 && flag == 0) {
            if (l1 == -1) {
                l1 = i;
            } else {
                l2 = i;
            }
            flag = 1;
        }

        if (V[i] == 0 && flag == 1) {
            if (r1 == -1) {
                r1 = i-1;
            } else {
                r2 = i-1;
            }
            flag = 0;
        }

        if(flag==1 && i==*rp-1) {
            if (r1 == -1) {
                r1 = i;
            } else {
                r2 = i;
            } 
        }

        if (r2 != -1 && l2 != -1) {
            //valutiamo quale sia maggiore e inizializziamo il secondo a meno 1
            if (V[r2]-V[l2]>V[r1]-V[l1]) {
                r1=r2;
                l1=l2;

            }
            //per sicurezza se funziona lo possiamo togliere
            r2=0;
            l2=0;
        }

    } 

    if(l1==-1) {
        return 0;
    }

    *lp=l1;
    *rp=r1;

   
    return 1;
}


//non serve
int **malloc2d(int N) {
    
    int **matr = malloc(N*sizeof(int *));
    for (int a=0; a<N; a++) {
        matr[a] = malloc(2*sizeof(int));
        matr[a][0] = -1;
        matr[a][1] = -1;
    }
    return matr;
}