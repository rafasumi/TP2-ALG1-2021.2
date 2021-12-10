#include "Store.hpp"
#include <cmath>

Store::Store(int id, int x, int y) {
  this->id = id;
  this->x = x;
  this->y = y;
}

double Store::getDistance(Store store) {
  int xSum = std::pow(this->x - store.x, 2);
  int ySum = std::pow(this->y - store.y, 2);
  return std::sqrt(xSum + ySum);
}
