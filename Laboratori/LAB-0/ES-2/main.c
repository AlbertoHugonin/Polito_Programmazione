#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int conta(char S[20], int n);

int main() {
    int N = 0;
    FILE *testo;
    char parola[20];
    //lunghezza sottostring
    int n = 4;


    testo = fopen("testo.txt", "r");
    fscanf(testo, "%d", &N);
    for (int a=0; a<N; a++) {
        fscanf(testo, "%s", parola);
        int risultato = conta(parola, n);
        printf("%s ha %d\n", parola, risultato);
    }
    fclose(testo);
    return 0;
}

int conta(char S[20], int n) {

    int count = 0;
    int result = 0;

    if (strlen(S) < n) {
        return 0;
    }

    for (int a=0; a<strlen(S); a++) {
        for (int b=0; b<n; b++) {
            if (S[a+b] == 'a' || S[a+b] == 'e' || S[a+b] == 'i' || S[a+b] == 'o' || S[a+b] == 'u') {
                count += 1;
            }
            if ( a+b >= strlen(S)) {
                count = 0;
                break;
            }
        }
        if (count == 2) {
            result += 1;
        }
        count = 0;
    }



    return result;
}