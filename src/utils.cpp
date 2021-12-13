#include "utils.hpp"
#include "Heap.hpp"
#include <algorithm>

// Função auxiliar que verifica se o valor informado está presente no vetor passado
bool vectorHasValue(std::vector<int> vector, int value) {
  return std::find(vector.begin(), vector.end(), value) != vector.end();
}

utils::MST utils::findMst(double** graph, int size) {
  // Vetor que contém os vértices da árvore
  std::vector<int> treeNodes(size);
  // Definição da MST (é chamado de treeEdges pois contém as arestas da árvore)
  MST treeEdges;

  // Aresta que antecede um determinado nó na MST (o índice no vetor indica o nó)
  std::vector<Edge> predecessors(size);
  // Aresta mais custa que se conhece entre o nó informado pelo índice do vetor e os nós em treeNodes
  std::vector<double> cheapestKnownEdge(size);

  // Vértice considerado como origem para o algoritmo. A escolha do 0 é arbitrária
  int source = 0;

  // Instancia os valores em cheapestKnownEdge. O valor é infinito para todos os nós, exceto o nó de origem
  cheapestKnownEdge[source] = 0; 
  for (int i = 0; i < size; i++) {
    if (i != source) {
      cheapestKnownEdge[i] = utils::INFINITY;
    }
  }

  // Instancia um heap, passando o vetor de cheapestKnownEdge para ser considerado na fila de prioridades
  // Obs.: O heap conterá tanto o ID do nó quanto o valor presente em cheapestKnownEdge
  Heap heap = Heap(cheapestKnownEdge);
  while (!heap.isEmpty()) {
    // Remove o menor elemento do heap e pega o seu índice e adiciona à árvore
    int minId = heap.popMin();
    treeNodes.push_back(minId);

    if (predecessors[minId].first != predecessors[minId].second)
      // Insere o nó incidente em minId na árvore
      treeEdges.push_back({predecessors[minId], graph[predecessors[minId].first][predecessors[minId].second]});

    // Para cada aresta que parte do nó minId, verifica se o seu peso é menor do que o menor custo conhecido do nó de "destino"
    // da aresta (i) até treeNodes. Se for, atualiza seu valor no heap, o valor em cheapestKnownEdge e define a aresta como
    // antecessora de i
    for (int i = 0; i < size; i++) {
      if (graph[minId][i] == 0 || vectorHasValue(treeNodes, i)) continue;

      if (graph[minId][i] < cheapestKnownEdge[i]) {
        heap.decreaseValue(i, graph[minId][i]);
        cheapestKnownEdge[i] = graph[minId][i];
        predecessors[i] = Edge(minId, i);
      }
    }
  }

  return treeEdges;
}

std::vector<std::pair<utils::Edge, double>> utils::removeLargest(utils::MST mst, int n) {
  // Ordena o vetor em ordem decrescente considerando os pesos das arestas
  std::stable_sort(mst.begin(), mst.end(),
    [](std::pair<Edge, double> a, std::pair<Edge, double> b){return a.second > b.second;});

  // Faz uma cópia do vetor pegando a partir n-ésimo elemento
  std::vector<std::pair<utils::Edge, double>> edges;
  edges.assign(mst.begin() + n, mst.end());
  return edges;
}