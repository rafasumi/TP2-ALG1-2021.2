#ifndef STORE_H
#define STORE_H

class Store {
  public:
    Store(int id, int x, int y);

    double getDistance(Store store);

  private:
    int id;
    int x, y;
};

#endif
