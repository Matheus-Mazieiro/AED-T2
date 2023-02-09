#include <stdio.h>
#include <stdlib.h>

struct Celula
{
    struct Celula *prox;
    int posicao;
};

void insere(struct Celula *lista, int p)
{
    struct Celula *nova = (struct Celula *)malloc(sizeof(struct Celula));
    nova->posicao = p;
    if (lista->prox == NULL)
        nova->prox = lista;
    else
        nova->prox = lista->prox;
    lista->prox = nova;
}

void imprimeLista(struct Celula *list, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d -> ", list->posicao);
        list = list->prox;
    }
    printf("\n");
}

void removeProximo(struct Celula *list){
    struct Celula *morta = list->prox;
    list->prox = morta->prox;
    free(morta);
}

int resolveJosephus(int n, int m)
{
    if (n < 2)
        return n;

    //Cria lista circular de tamanho n
    struct Celula *list = (struct Celula *)malloc(sizeof(struct Celula));
    list->posicao = 1;
    list->prox = NULL;
    for (int i = n; i > 1; i--)
        insere(list, i);

    //Para quando só tem 1 elemento
    while (list->prox->posicao != list->posicao)
    {
        int assassino = list->posicao;
        //Pula m-1 posições, para dps retirar elemento na emésima posicão
        for (int i = 0; i < m - 1; i++)
            list = list->prox;

        //Retira o elemento da emésima posição (ou emésima+1, caso seja um suicidio)
        int suicidio = assassino == list->prox->posicao;
        removeProximo(suicidio ? list->prox : list);
        list = suicidio ? list->prox->prox : list->prox;
    }

    return list->posicao;
}

int main()
{
    int nroexecs;
    scanf("%d", &nroexecs);
    int *n = malloc(nroexecs * sizeof(int));
    int *m = malloc(nroexecs * sizeof(int));

    for (int i = 0; i < nroexecs; i++)
    {
        scanf("%d", &n[i]);
        scanf("%d", &m[i]);
    }

    for (int i = 0; i < nroexecs; i++)
    {
        printf("Usando n=%d, m=%d, resultado=%d\n", n[i], m[i], resolveJosephus(n[i], m[i]));
    }

    free(n);
    free(m);

    return 0;
}