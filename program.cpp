/*
Insper, 2024-1
Supercomputação, Projeto Final

Código fonte principal

Programa que encontra a clique máxima em um grafo.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// constantes
const std::string SOURCE_FILENAME = "graph.txt";

// identidades de funções
int isAdjacent(std::vector<std::vector<int>> graph, int node_A, int node_B);                                // verifica se um node é adjacnete a outro
std::vector<std::vector<int>> readGraph(const std::string& filename, int& n_nodes);                         // cria a matriz de adjacência a partir to texto do grafo

// função principal
int main() {

    // declara a variável da quantidade de nós e faz a leitura do grafo
    int n_nodes;                                                               // quantidade de nós do grafo, será inicializada pela função de leitura do grafo
    std::vector<std::vector<int>> graph = readGraph(SOURCE_FILENAME, n_nodes); // chamada da função de leitura do grafo
    std::cout << n_nodes << std::endl;
    
    // ### TESTE ###########
    // etapa 1
    for (int i = 0; i < n_nodes; i++) {
        for (int j = 0; j < n_nodes; j++) {
            std::cout << graph[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // etapa 2.2.1
    std::cout << isAdjacent(graph, 0, 1) << std::endl;
    std::cout << isAdjacent(graph, 1, 0) << std::endl;
    std::cout << isAdjacent(graph, 4, 0) << std::endl;
    std::cout << isAdjacent(graph, 12, 3) << std::endl;
    // ### TESTE ###########
}

int isAdjacent(std::vector<std::vector<int>> graph, int node_A, int node_B) {
    /*
    função que verifica se um nó específico é adjacente a outro nó específico

    recebe:
    - graph: matriz de adjacência do grafo
    - node_A: um dos nós a ser testado
    - node_B: o outro nó a ser testado

    retorna: true ou false
    */

   // verifica na matriz de adjacência
   return graph[node_A][node_B];
}

// função que lê um grafo não direcionado a partir do arquivo de entrada em forma de texto
// adaptação do código dispoinibilizado pelo professor
std::vector<std::vector<int>> readGraph(const std::string& filename, int& n_nodes) {

    // abre o arquivo do grafo em forma de texto e extrai a quantidade de vértices e arestas
    std::ifstream file(filename);   // abre o arquivo
    int n_edges;                    // variável da quantidade de arestas
    file >> n_nodes >> n_edges;     // extrai a quandidade de vértices e arestas (V, A)

    // grafo final na forma de matriz de adjacência, começa com tudo 0, 1 indica conexão entre os nodes i e j
    std::vector<std::vector<int>> graph(n_nodes, std::vector<int>(n_nodes, 0));

    // loop de coleta das arestas
    for (int i = 0; i < n_edges; ++i) { // percorre todas as arestas a partir da quantidade de arestas
        int u, v;                       // variáveis dos números dos nós em questão, começam do 1 e não do 0
        file >> u >> v;                 // extrai os números do nós em questão
        graph[u - 1][v - 1] = 1;        // marca como 1 o elemento de índices (u - 1) e (v - 1), indicando a existência de uma aresta entre u e v
        graph[v - 1][u - 1] = 1;        // marca como 1 o elemento de índices (v - 1) e (u - 1), indicando a existência de uma aresta entre v e u (grafo não direcionado)
    }

    // fecha o arquivo
    file.close();

    // retorna a matriz do grafo
    return graph;
}