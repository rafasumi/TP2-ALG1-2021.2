#include <iostream>
#include <vector>
#include <iomanip>
#include "Store.hpp"
#include "utils.hpp"

// Função main do programa. É responsável pela leitura do arquivo de input, por instanciar objetos e variáveis
// e pela chamada de funções necessárias para obter as arestas necessárias para o cálculo do custo
int main(int argc, char const *argv[]) {
  int storeQty, bikeKmLimit, droneQty, bikeKmCost, truckKmCost;

  // Faz a leitura da primeira linha do input, que contém informações diversas
  std::cin >> storeQty >> bikeKmLimit >> droneQty >> bikeKmCost >> truckKmCost;

  // Faz a leitura das linhas referentes às lojas
  std::vector<Store> stores;
  int x, y;
  for (int i = 0; i < storeQty; i++) {
    std::cin >> x >> y;
    Store store = Store(i, x, y);
    stores.push_back(store);
  }

  // Instancia o grafo, que é uma matriz de adjacência. Como já se sabe que cada vértice terá uma aresta até todo
  // outro vértice, a matriz possui os pesos da aresta entre cada vértice. Como não existem arestas de um vértice
  // para ele mesmo, posições do tipo (i, i) na matriz terão valor 0.
  double** graph = new double*[storeQty];
  for (int i = 0; i < storeQty; i++) 
    graph[i] = new double[storeQty];

  // Popula a matriz de adjacência do grafo considerando todas as lojas
  for (int i = 0; i < storeQty; i++) {
    Store fromStore = stores.at(i);
    for (int j = 0; j < storeQty; j++) {
      Store toStore = stores.at(j);
      graph[i][j] = fromStore.getDistance(toStore);
    }
  }

  utils::MST mst = utils::findMst(graph, storeQty);

  // Remove as n maiores arestas da MST. No caso, n será a quantidade de drones - 1, já que isso define a quantidade
  // de subconjuntos conectados que seram resultantes da remoção de arestas da árvore. Dessa forma, como temos droneQty
  // drones, queremos obter droneQty subconjuntos da árvore e, para tal, removemos droneQty - 1 arestas
  std::vector<std::pair<utils::Edge, double>> usedEdges = utils::removeLargest(mst, droneQty - 1);

  // Calcula o custo total para motocicletas e caminhões
  double totalBikeCost = 0;
  double totalTruckCost = 0;
  for (auto edge : usedEdges) {
    if (edge.second <= bikeKmLimit) {
      totalBikeCost += bikeKmCost * edge.second;
    } else {
      totalTruckCost += truckKmCost * edge.second;
    }
  }

  std::cout << std::fixed;
  std::cout << std::setprecision(3) << totalBikeCost << " " << totalTruckCost;

  for (int i = 0; i < storeQty; i++) 
    delete[] graph[i];
  delete[] graph;

  return 0;
}
