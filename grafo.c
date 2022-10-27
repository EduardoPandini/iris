#include "arq.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 150
struct descritor *(cria)()
{
    FILE *fp = fopen("grafo.txt", "r");
    if (fp == NULL)
    {
        return NULL;
    }
    int n_vertices;
    fscanf(fp, "%d", &n_vertices);
    struct descritor *desc = malloc(sizeof(struct descritor));
    desc->quantidade_vertices = n_vertices;
    desc->lista = calloc(n_vertices, sizeof(struct vertice));
    desc->lista->primeiro = NULL;
    int v1, v2;
    while (1)
    {
        fscanf(fp, "%d %d", &v1, &v2);
        if (feof(fp))
            return desc;

        // Bloco de codigo que vai encadear a ligacao do primeiro vertice da dupla ordenada (aresta)

        struct aresta *novo = malloc(sizeof(struct aresta));
        novo->ligacao = v2;
        novo->proximo = NULL;
        if (desc->lista[v1 - 1].primeiro == NULL)
        {
            desc->lista[v1 - 1].primeiro = novo;
            desc->lista[v1 - 1].grau = 1;
        }
        else
        {
            desc->lista[v1 - 1].grau += 1;
            struct aresta *aux = malloc(sizeof(struct aresta));

            aux = desc->lista[v1 - 1].primeiro;
            while (aux->proximo != NULL)
            {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }
        if (v1 != v2)
        {

            // Bloco de codigo que vai encadear a ligacao do segundo vertice da dupla ordenada (aresta)

            struct aresta *novo2 = malloc(sizeof(struct aresta));
            novo2->ligacao = v1;
            novo2->proximo = NULL;
            if (desc->lista[v2 - 1].primeiro == NULL)
            {
                desc->lista[v2 - 1].grau += 1;
                desc->lista[v2 - 1].primeiro = novo2;
            }
            else
            {
                desc->lista[v2 - 1].grau += 1;

                struct aresta *aux = malloc(sizeof(struct aresta));

                aux = desc->lista[v2 - 1].primeiro;
                while (aux->proximo != NULL)
                {
                    aux = aux->proximo;
                }
                aux->proximo = novo2;
            }
        }
    }
    if (fp != NULL)
        fclose(fp);
}

void destroi(struct descritor *desc)
{
    if (desc == NULL)
        return;
    int tamanho = desc->quantidade_vertices;
    for (int i = 0; i < tamanho; i += 1)
    {
        if (desc->lista[i].primeiro == NULL)
            free(desc->lista[i].primeiro);
        else
        {
            struct aresta *aux = desc->lista[i].primeiro;

            while (aux->proximo != NULL)
            {
                desc->lista[i].primeiro = aux->proximo;
                free(aux);
                aux = desc->lista[i].primeiro;
            }
            free(desc->lista[i].primeiro);
        }
    }
    free(desc);
    return;
}

void printar_grafo(struct descritor *desc)
{
    int tamanho = desc->quantidade_vertices;
    for (int i = 0; i < tamanho; i += 1)
    {
        printf("\nv[%d]", i + 1);
        struct aresta *aux = desc->lista[i].primeiro;

        while (aux != NULL)
        {
            printf("-%d", aux->ligacao);
            aux = aux->proximo;
        }
        printf("\n");
    }
}

void fazerTxt(double **matrix) // le a matriz e cria um txt
{
    if (matrix == NULL)
        return;
    char buffer[100];
    FILE *fp = fopen("grafo.txt", "w");
    if (fp == NULL)
    {
        return;
    }
    fprintf(fp, "%d\n", SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = i + 1; j < SIZE; j++)
        {
            if (matrix[i][j] <= 0.3)
                fprintf(fp, "%d %d\n", i + 1, j + 1);
        }
    }
    fclose(fp);
}

double **cria_tabela()
{

    FILE *fp = fopen("iris.csv", "r");
    if (fp == NULL)
    {
        return NULL;
    }
    double maior = 0; // para fazer a normalização
    double menor = 0;
    double dist = 0; // distancia entre nodos
    double **matrix = calloc(SIZE, sizeof(double *));
    if (matrix == NULL)
        return NULL;
    char buffer[100];
    fpos_t linha_atual;
    fgetpos(fp, &linha_atual);
    fgets(buffer, 100, fp); // Ignorando a ultima coluna
    fsetpos(fp, &linha_atual);
    double x, y, z, w, esp, x2, y2, z2, w2, esp2;

    int i = 0, j = 1;
    while (i < SIZE)
    {
        fgets(buffer, 100, fp); // Ignorando a linha
        fgetpos(fp, &linha_atual);
        fscanf(fp, "%lf, %lf, %lf, %lf,", &x, &y, &z, &w);
        fgets(buffer, 100, fp); // Ignorando a ultima coluna
        matrix[i] = calloc(SIZE, sizeof(double));

        while (j < SIZE)
        {

            fscanf(fp, "%lf, %lf, %lf, %lf,", &x2, &y2, &z2, &w2);
            fgets(buffer, 100, fp);
            dist = sqrt(pow((x - x2), 2) + pow((y - y2), 2) + pow((z - z2), 2) + pow((w - w2), 2));
            matrix[i][j] = dist;
            if (i == 0)
            {
                maior = dist;
                menor = dist;
            }
            else if (dist < menor)
            {
                menor = dist;
            }
            else if (dist > maior)
            {
                maior = dist;
            }

            j++;
        }
        fsetpos(fp, &linha_atual);
        i++;
        j = i + 1;
    }
    normaliza(matrix, menor, maior);
    return matrix;
    if (fp != NULL)
    {
        fclose(fp);
    }
}

void normaliza(double **matrix, double menor, double maior)
{

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = i + 1; j < SIZE; j++)
        {
            matrix[i][j] = (matrix[i][j] - menor) / (maior - menor);
        }
    }
}

double acuracia()
{
    FILE *f = fopen("grafo.txt", "r");
    int v1 = 0, v2 = 0, tam = 0;
    int tp = 0, fp = 0, fn = 0, tn = 0;
    if (f == NULL)
    {
        return -1.0;
    }
    fscanf(f, "%d", &tam);
    if (tam == 0)
        return -1.0;
    for(int i = 0; i <tam; i += 1)
    {
        fscanf(f, "%d %d", &v1, &v2);
        if (v1 <= 50 && v2 <= 50)
        {
            tp += 2;
        }
        else if (v1 <= 50 && v2 > 50)
        {
            fp += 1;
            fn += 1;
        }
        else if (v1 > 50 && v2 <= 50)
        {
            fn += 1;
            fp += 1;
        }
        else
        {
            tn += 2;
        }
    }
    if (f)
        fclose(f);
    double acc = (double)(tp + tn) / (tp + tn + fp + fn);
    return acc;
}
