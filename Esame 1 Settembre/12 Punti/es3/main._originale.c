
typedef struct {
char *s;
int pos;
int costo;
} part;

void solve(char *target, part *P, int nParts)
{
    int *val = malloc(nParts * sizeof(int));
    for (int a = 0; a < nParts; a++)
    {
        val[a] = a;
    }
    int *sol = malloc(strlen(target) * sizeof(int));
    int *mark = calloc(nParts, sizeof(int));
    int best_costo = MAX_INT; //ricordare di includere limits.h
    int costo = 0;
    int *best_sol = malloc(strlen(target) * sizeof(int));
    SolveR(val, mark, nParts, sol, strlen(target), 0, P, target, costo, *best_costo, best_sol);
}

//modello con disposizioni semplici
void solveR(int *val, int *mark, int n, int *sol, int k, int pos, parts *P, char *target, int *best_costo, int costo, int *best_sol)
{
    int i = 0;
    if (pos >= k)
    {
        //caso terminale
        if (cost > *best_costo)
        {
            *best_costo = cost;
        }
    }
    for (i = 0; i < n; i++)
    {
        if (mark[i] == 0)
        {
            //pruning, prima di prendere elemento vediamo se va bene se no lo saltiamo
            if (check(sol, pos, P, targer) == 0)
            {
                mark[i] = 1;
                //sol[pos] contiene l'indice del vettore P dell'elemento preso
                sol[pos] = val[i];
                solveR(val, mark, n, sol, k, pos + 1, P, target, best_costo, costo + P[sol[pos]]->costo);
                mark[i] = 0;
            }
        }
        return void;
    }

    int check(int *sol, int pos, parts *P, char *target)
    {
        if (strlen(parts[sol[pos]]) > strlen(target))
        {
            return 1;
        }
        char *stringa = parts[sol[pos]]->s;
        int inizio = parts[sol[pos]]->pos;
        //andiamo a vedere se la sottostringa è compatibile con parte della stringa iniziale
        for (int a = 0; a < strlen(stringa); a++)
        {
            if (target[inizio + a] != stringa[a])
            {
                return 1;
            }
        }
        //adesso vediamo se il posto era già occupato, questo controllo è meglio metterlo all'inizio
        for (int a = 0; a < pos; a++)
        {
            if (parts[sol[a]]->pos == inizio)
            {
                return 1;
            }
        }
        return 0;
    }