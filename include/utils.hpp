#include <vector>

// Namespace que contém funções e dados úteis
namespace utils {
  // Constante que representa um valor infinito (arbitrariamente grande)
  const int INFINITY = 30000;
  // Alias para um tipo que representa uma aresta (par de inteiros)
  using Edge = std::pair<int, int>;
  // Alias para um tipo que representa uma árvore geradora mínima (vetor de arestas e com seus pesos)
  using MST = std::vector<std::pair<Edge, double>>;

  // Encontra a árvore geradora mínima para o grafo passado usando o algoritmo de Prim
  MST findMst(double** graph, int size);
  // Remove as n arestas com maior peso da MST passada. O tipo de retorno não é utils::MST, pois após remover as n
  // arestas, o conjunto deixa de ser uma árvore geradora mínima
  std::vector<std::pair<Edge, double>> removeLargest(MST mst, int n);
}
