#include <stdio.h>


int main() {

    int N[30] = {0};
    int n;
    int m = 0;
    int count = 0;
    puts("Dimmi quanti sono gli elementi");
    scanf("%d", &n);


    //itero tutti gli elementi e trovo m
    puts("Dimmi gli elementi");
    for (int a=0; a<n; a++) {
        scanf("%d", &N[a]);
        count += 1;
        if (N[a] == 0) {
            if (count >= m) {
                m = count - 1;
            }
            count = 0;
        }
    }
    count = 0;

    //controllo nel caso non ci siano zeri
    if (m == 0) {
        m = n;
    }

    //stampare le sequenze
    for (int a=0; a<=n; a++) {
        if (N[a] != 0) {
            count += 1;
        }
        else {
            if (count == m) {
                //stampiamo
                printf("[ ");
                for (int b=a-count; b<a; b++) {
                    printf(" %d ", N[b]);
                }
                printf(" ] ");
            }
                count = 0;
        }
    }






    return 0;
}