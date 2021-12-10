#ifndef HEAP_H
#define HEAP_H
#include <vector>

class Heap {
  public:
    Heap(std::vector<double> vector);

    void print();

    int popMin();
    void decreaseValue(int key, double newValue);
    bool isEmpty();

  private:
    void heapify();

    std::vector<std::pair<int, double>> heapVector;
    std::vector<int> keysPositions;
    int size;
};

#endif
