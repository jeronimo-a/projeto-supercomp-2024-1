/*
Insper, 2024-1
Supercomputação, Projeto Final

Código fonte principal

Programa que encontra a clique máxima em um grafo a partir da heurística gulosa.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// constantes
const std::string SOURCE_FILENAME = "../inputs/graph.txt";

// identidades de funções
int isAdjacent(std::vector<std::vector<int>> graph, int node_A, int node_B);                        // verifica se um node é adjacnete a outro
int isAdjacentToAll(std::vector<std::vector<int>> graph, std::vector<int> nodes, int node);         // verifica se um node é adjacente a todos da uma lista
std::vector<int> findClique(std::vector<std::vector<int>> graph, std::vector<int> candidates);      // encontra uma clique com base em um vetor de candidatos
std::vector<int> findMaximumClique(std::vector<std::vector<int>> graph);                            // procura a clique máxima pela heurística gulosa
std::vector<std::vector<int>> readGraph(const std::string& filename, int& n_nodes);                 // cria a matriz de adjacência a partir to texto do grafo

// função principal
int main() {

    // declara a variável da quantidade de nós e faz a leitura do grafo
    int n_nodes;                                                               // quantidade de nós do grafo, será inicializada pela função de leitura do grafo
    std::vector<std::vector<int>> graph = readGraph(SOURCE_FILENAME, n_nodes); // chamada da função de leitura do grafo
    
    // inicialização do vetor de candidatos
    std::vector<int> candidates(n_nodes);
    for (int i = 0; i < n_nodes; i++) { // percorre todos os números de 0 até a quantidade de nós - 1
        candidates[i] = i;              // iguala o valor do vetor no índice tal ao índice
    }

    // acha a clique máxima e verboes de feedback
    std::cout << "Encontrando a clique máxima pela heurística gulosa" << std::endl;
    std::vector<int> clique = findMaximumClique(graph);

    // ### TESTE #########
    for (int i = 0; i < clique.size(); i++) {
        std::cout << clique[i] << " ";
    }
    std::cout << std::endl;
    // ### TESTE #########
}

std::vector<int> findMaximumClique(std::vector<std::vector<int>> graph) {
    /*
    função que encontra a clique "máxima" de um grafo usando a heurística gulosa
    retotrna clique obtido a partir de um vetor de candidatos ordenado pelo grau de cada um

    recebe:
    - graph: a matriz de adjacência do grafo

    retorna: o vetor da clique "máxima" de acordo com a heurística gulosa
    */

    // gera a lista de candidatos inicial
    std::vector<int> candidates(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        candidates[i] = i;
    }

    std::vector<int> maximum_clique;    // maior clique de acordo com a heurística

    // retorna a clique máxima
    return maximum_clique;
}

std::vector<int> findClique(std::vector<std::vector<int>> graph, std::vector<int> candidates) {
    /*
    função que encontra uma clique qualquer de um grafo
    a clique que será encontrada é uma clique qualquer que depende da ordem dos candidatos
    feita com base no pseudocódigo fornecido pelo professor

    recebe:
    - graph: matriz de adjacência do grafo
    - candidates: vetor de candidatos

    retorna: vetor de nós que compõem a clique
    */

    // declaração do vetor da clique
    std::vector<int> clique;    // vetor da clique, vai conter os nós que pertencem a uma clique qualquer

    // loop externo de inclusão ou exclusão dos candidatos
    while (candidates.size() > 0) {     // roda até não sobrar mais nenhum candidato

        // pega último candidato e o tira da lista
        int outer_candidate = candidates[candidates.size() - 1];    // pega o último candidato
        candidates.pop_back();                                      // o tira da lista de candidatos

        // verifica se o candidato tem conexão com todos os membros atuais da clique máxima
        int outer_can_be_added = isAdjacentToAll(graph, clique, outer_candidate);

        // atualiza a clique máxima e renova a lista de possíveis candidatos
        if (outer_can_be_added == 1) {
            
            // atualiza a clique máxima e declara a lista de novos candidatos
            clique.push_back(outer_candidate);
            std::vector<int> new_candidates;

            // loop de seleção dos novos candidatos, são incluidos todos aqueles que tem conexão com todos os membros atuais da clique
            for (int i = 0; i < candidates.size(); i++) {                                       // percorre todos os candidatos atuais
                int is_adjacent_to_all = isAdjacentToAll(graph, clique, candidates[i]); // verifica se o novo candidato é adjacente a todos os membros atuais da clique
                if (is_adjacent_to_all == 1) {                                                  // se ele for adjacente a todos os membros atuais da clique
                    new_candidates.push_back(candidates[i]);                                    // adiciona-o à lista de novos candidatos
                }
            }

            // atualiza a lista de candidatos
            candidates = new_candidates;
        }
    }

    return clique;
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

int isAdjacentToAll(std::vector<std::vector<int>> graph, std::vector<int> nodes, int node) {
    /*
    função que verifica se um nó específico é adjacente a todos os nós de uma lista

    recebe:
    - graph: matriz de adjacência do grafo
    - nodes: vetor dos nós em questão
    - node: número do nó específico

    retorna: true ou false
    */

    // loop de verificação
    for (int i = 0; i < nodes.size(); i++) {            // percorre todos os nós do grupo
        if (isAdjacent(graph, node, nodes[i]) == 0) {   // verifica se é adjacente ao nó membro do grupo em questão
            return 0;                                   // se não for, já retorna 0
        }
    }

    // se chegou até aqui, quer dizer que é adjacente a todos
    return 1;
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