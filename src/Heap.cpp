#include "Heap.hpp"
#include <iostream>

Heap::Heap(std::vector<double> vector) {
  this->size = vector.size();
  this->heapVector = std::vector<std::pair<int, double>>(size);
  this->keysPositions = std::vector<int>(size);

  for (int i = 0; i < size; i++) {
    this->heapVector[i] = std::pair<int, double>(i, vector[i]);
    this->keysPositions[i] = i;
  }
  
  heapify();
}

int Heap::popMin() {
  if (this->size == 0) return -1;

  int minId = this->heapVector[0].first;

  this->keysPositions[0] = -1;
  this->keysPositions[this->heapVector[this->size-1].first] = 0;
  this->heapVector[0] = this->heapVector[this->size-1];
  
  this->size--;
  heapify();

  return minId;
}

void Heap::decreaseValue(int key, double newValue) {
  if (this->keysPositions[key] != -1 && this->heapVector[this->keysPositions[key]].second > newValue) {
    this->heapVector[this->keysPositions[key]].second = newValue;
    heapify();
  }
}

bool Heap::isEmpty() {
  return (this->size == 0);
}

void Heap::heapify() {
  int index = this->size - 1;
  while (index > 0) {
    int parent = (index - 1)/2;

    if (this->heapVector[index].second < this->heapVector[parent].second) {
      std::pair<int, double> aux = this->heapVector[parent];

      this->keysPositions[this->heapVector[index].first] = parent;
      this->heapVector[parent] = this->heapVector[index];

      this->keysPositions[aux.first] = index;
      this->heapVector[index] = aux;
    }

    index--;
  }
}
