#include <iostream>
#include <vector>
#include <iomanip>
#include "Store.hpp"
#include "utils.hpp"

int main(int argc, char const *argv[]) {
  int storeQty, bikeKmLimit, droneQty, bikeKmCost, truckKmCost;

  std::cin >> storeQty >> bikeKmLimit >> droneQty >> bikeKmCost >> truckKmCost;

  std::vector<Store> stores;
  int x, y;
  for (int i = 0; i < storeQty; i++) {
    std::cin >> x >> y;
    Store store = Store(i, x, y);
    stores.push_back(store);
  }

  double** graph = new double*[storeQty];
  for (int i = 0; i < storeQty; i++) 
    graph[i] = new double[storeQty];


  for (int i = 0; i < storeQty; i++) {
    Store fromStore = stores.at(i);
    for (int j = 0; j < storeQty; j++) {
      Store toStore = stores.at(j);
      graph[i][j] = fromStore.getDistance(toStore);
    }
  }


  utils::MST mstEdges = utils::findMstEdges(graph, storeQty);

  std::vector<utils::Edge> usedEdges = utils::removeLargest(mstEdges, droneQty - 1);

  double totalTruckCost = 0;
  double totalBikeCost = 0;
  for (utils::Edge edge : usedEdges) {
    if (graph[edge.first][edge.second] <= bikeKmLimit) {
      totalBikeCost += bikeKmCost * graph[edge.first][edge.second];
    } else {
      totalTruckCost += truckKmCost * graph[edge.first][edge.second];
    }
  }

  std::cout << std::fixed;
  std::cout << std::setprecision(3) << totalBikeCost << " " << totalTruckCost << std::endl;

  for (int i = 0; i < storeQty; i++) 
    delete[] graph[i];
  delete[] graph;

  return 0;
}
