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
int isAdjacent(std::vector<std::vector<int>> graph, int node_A, int node_B);                    // verifica se um node é adjacnete a outro
int isAdjacentToAll(std::vector<std::vector<int>> graph, std::vector<int> nodes, int node);     // verifica se um node é adjacente a todos da uma lista
std::vector<int> findMaximumClique(std::vector<std::vector<int>> graph);                        // encontra a clique máxima
std::vector<std::vector<int>> readGraph(const std::string& filename, int& n_nodes);             // cria a matriz de adjacência a partir to texto do grafo

// função principal
int main() {

    // declara a variável da quantidade de nós e faz a leitura do grafo
    int n_nodes;                                                               // quantidade de nós do grafo, será inicializada pela função de leitura do grafo
    std::vector<std::vector<int>> graph = readGraph(SOURCE_FILENAME, n_nodes); // chamada da função de leitura do grafo
    
    // acha a clique máxima
    std::vector<int> maximum_clique = findMaximumClique(graph);

    // ### TESTE #########
    for (int i = 0; i < maximum_clique.size(); i++) {
        std::cout << maximum_clique[i] << " ";
    }
    std::cout << std::endl;
    // ### TESTE #########
}

std::vector<int> findMaximumClique(std::vector<std::vector<int>> graph) {
    /*
    função que encontra a clique máxima de um grafo, que é a clique com maior número de nós
    feita com base no pseudocódigo fornecido pelo professor

    recebe:
    - graph: matriz de adjacência do grafo

    retorna: vetor de nós que compõem a clique máxima

    etapas:
        - 1: declaração e inicialização dos vetores
        - 2: loop externo de inclusão ou exclusão dos candidatos
    */

    //== ETAPA 1 === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === findMaximumClique 1

    // variáveis auxiliares
    int n_nodes = graph.size(); // quantidade de nós no grafo

    // declaração dos vetores
    std::vector<int> maximum_clique;        // vetor da clique máxima, vai conter os nós que pertencem a clique máxima
    std::vector<int> candidates(n_nodes);   // lista dos candidatos, tem tamanho inicial igual à quantidade total de vértices

    // inicialização do vetor de candidatos
    for (int i = 0; i < n_nodes; i++) { // percorre todos os números de 0 até a quantidade de nós - 1
        candidates[i] = i;              // iguala o valor do vetor no índice tal ao índice
    }

    //== ETAPA 2 === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === === findMaximumClique 2

    // loop externo de inclusão ou exclusão dos candidatos
    while (candidates.size() > 0) {     // roda até não sobrar mais nenhum candidato

        // pega último candidato e o tira da lista
        int outer_candidate = candidates[candidates.size() - 1];    // pega o último candidato
        candidates.pop_back();                                      // o tira da lista de candidatos

        // verifica se o candidato tem conexão com todos os membros atuais da clique máxima
        int outer_can_be_added = isAdjacentToAll(graph, maximum_clique, outer_candidate);

        // atualiza a clique máxima e renova a lista de possíveis candidatos
        if (outer_can_be_added == 1) {
            
            // atualiza a clique máxima e declara a lista de novos candidatos
            maximum_clique.push_back(outer_candidate);
            std::vector<int> new_candidates;

            // loop de seleção dos novos candidatos, são incluidos todos aqueles que tem conexão com todos os membros atuais da clique
            for (int i = 0; i < candidates.size(); i++) {                                       // percorre todos os candidatos atuais
                int is_adjacent_to_all = isAdjacentToAll(graph, maximum_clique, candidates[i]); // verifica se o novo candidato é adjacente a todos os membros atuais da clique
                if (is_adjacent_to_all == 1) {                                                  // se ele for adjacente a todos os membros atuais da clique
                    new_candidates.push_back(candidates[i]);                                    // adiciona-o à lista de novos candidatos
                }
            }

            // atualiza a lista de candidatos
            candidates = new_candidates;
        }
    }

    return maximum_clique;
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