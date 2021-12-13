#ifndef HEAP_H
#define HEAP_H

#include <vector>

// Classe que representa uma lista de prioridades (heap), onde os elementos de menor chave tem maior prioridade.
class Heap {
  public:
    // Construtor da classe. Recebe como parâmetro o vetor de valores usado como base para o heap
    Heap(std::vector<double> vector);

    // Remove o menor elemento do heap e retorna a sua chave
    int popMin();
    // Diminui o valor para uma determinada chave no heap
    void decreaseValue(int key, double newValue);
    bool isEmpty();

  private:
    // Certifica que a condição de heap está sendo satisfeita em heapVector para os elementos à direita do índice passado
    // como parâmetro
    void heapifyRight(int index);
    // Certifica que a condição de heap está sendo satisfeita em heapVector para os elementos à esquerda do índice passado
    // como parâmetro
    void heapifyLeft(int index);

    // Troca de posição os elementos nos índices indicados
    void swap(int index1, int index2);

    // Vetor que contém os elementos do heap (chave e valor)
    std::vector<std::pair<int, double>> heapVector;
    // Vetor que contém a posição de cada chave. É utilizado para poder obter a posição em que uma determinada chave está
    // em tempo constante
    std::vector<int> keysPositions;
    int size;
};

#endif
