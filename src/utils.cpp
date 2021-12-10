#include "utils.hpp"
#include "Heap.hpp"
#include <algorithm>
#include <numeric>

bool vectorHasValue(vector<int> vector, int value) {
  return std::find(vector.begin(), vector.end(), value) != vector.end();
}

utils::MST utils::findMstEdges(double** graph, int size) {
  vector<int> treeNodes(size);
  MST treeEdges;

  vector<Edge> predecessors(size);
  vector<double> cheapestKnownEdge(size);

  int source = 0;

  cheapestKnownEdge[source] = 0; 
  for (int i = 0; i < size; i++) {
    if (i != source) {
      cheapestKnownEdge[i] = utils::INFINITY;
    }
  }

  Heap heap = Heap(cheapestKnownEdge);
  while (!heap.isEmpty()) {
    int minId = heap.popMin();
    treeNodes.push_back(minId);

    if (predecessors[minId].first != predecessors[minId].second)
      treeEdges.push_back({predecessors[minId], graph[predecessors[minId].first][predecessors[minId].second]});

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

vector<utils::Edge> utils::removeLargest(utils::MST mst, int subsetQty) {
  std::stable_sort(mst.begin(), mst.end(),
    [](pair<Edge, double> a, pair<Edge, double> b){return a.second > b.second;});

  vector<Edge> edges;
  for (size_t i = subsetQty; i < mst.size(); i++) {
    edges.push_back(mst[i].first);
  }

  return edges;
}