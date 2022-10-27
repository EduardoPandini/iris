#include <stdio.h>
#include <stdlib.h>
#include "arq.h"

int main()
{
    double **matrix = NULL;
    struct descritor *desc = NULL;
    double acc;
    int escolha = 5;
    while (1)
    {
        printf("Digite 1 para montar a matriz e gerar um arquivo de texto representando o grafo\nDigite 2 para importar o grafo de um arquivo de texto existente\nDigite 3 para printar o grafo\nDigite 4 para calcular a acuracia\nDigite 0 para sair\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1:
            matrix = cria_tabela();
            if (matrix == NULL)
            {
                printf("Erro ao importar arquivo CSV\n");
                break;
            }
            fazerTxt(matrix);
            printf("Sucesso ao criar txt\n");
            break;
        case 2:
            desc = cria();
            if (desc == NULL)
                printf("Erro ao importar grafo do arquivo\n");
            else
                printf("Grafo importado com sucesso!\n");
            break;
        case 3:
            if (desc == NULL)
            {
                printf("Grafo ainda nao foi importado!\n");
                break;
            }
            printar_grafo(desc);
            break;
        case 4:
            acc = acuracia();
            if (acc != -1.0)
                printf("Acuracia: %.6lf\n", acc);
            else
                printf("Arquivo txt inexistente ou vazio\n");
            break;
        case 0:
            destroi(desc);
            if (matrix != NULL)
                free(matrix);
            return 0;
        }
    }
}
