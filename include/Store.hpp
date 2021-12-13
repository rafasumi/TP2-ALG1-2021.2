#ifndef STORE_H
#define STORE_H

// Classe que representa uma loja
class Store {
  public:
    Store(int id, int x, int y);

    // Calcula a distância euclidiana até a loja passada como parâmetro
    double getDistance(Store store);

  private:
    int id;
    int x, y;
};

#endif
