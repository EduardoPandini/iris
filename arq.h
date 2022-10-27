//O arquivo "grafo.txt" deve conter na primeira linha o numero de vertices seguido do numero de arestas
//Nas proximas linhas, o arquivo deve apresentar o numero do primeiro vertice, seguido do numero do segundo, indicando uma aresta
//existente entre esses dois vertices
struct descritor
{
    struct vertice *lista;
    int quantidade_vertices;
};
struct vertice
{
    struct aresta *primeiro;
    int grau;
};
struct aresta
{
    int ligacao;
    struct aresta *proximo;
};
//Definicao das funcoes

struct descritor *(cria)();
void destroi(struct descritor *desc);
void printar_grafo(struct descritor *desc);
double** cria_tabela();
void normaliza(double** matrix, double menor, double maior);
void fazerTxt();
double acuracia();

