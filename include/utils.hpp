#include <vector>

using std::vector;
using std::pair;

namespace utils {
  const int INFINITY = 30000;
  using Edge = pair<int, int>;
  using MST = vector<pair<Edge, double>>;

  MST findMstEdges(double** graph, int size);
  vector<Edge> removeLargest(MST mst, int subsetQty);
}
