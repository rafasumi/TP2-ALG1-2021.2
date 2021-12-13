#include "Heap.hpp"
#include <iostream>

Heap::Heap(std::vector<double> vector) {
  this->size = vector.size();
  this->heapVector = std::vector<std::pair<int, double>>(size);
  this->keysPositions = std::vector<int>(size);

  // Copia os valores de vector para heapVector, além de informar os índices das chaves em keysPositions
  for (int i = 0; i < size; i++) {
    this->heapVector[i] = std::pair<int, double>(i, vector[i]);
    this->keysPositions[i] = i;
  }
  
  // Chama heapifyRight para 0 para garantir que a condição de heap é satisfeita em heapVector
  heapifyRight(0);
}

int Heap::popMin() {
  if (this->size == 0) return -1;

  int minId = this->heapVector[0].first;

  // Marca o índice da chave removida como -1
  this->keysPositions[0] = -1;

  // Passa o elemento que estava na última posição para a primeira
  this->keysPositions[this->heapVector[this->size - 1].first] = 0;
  this->heapVector[0] = this->heapVector[this->size - 1];
  
  this->size--;

  // Chama heapifyRight para 0 para garantir que a condição de heap é satisfeita em heapVector
  heapifyRight(0);

  return minId;
}

void Heap::decreaseValue(int key, double newValue) {
  // Decrementa o valor apenas se a chave estiver presente em heapVector e se o seu valor atual for maior que o novo valor
  if (this->keysPositions[key] != -1 && this->heapVector[this->keysPositions[key]].second > newValue) {
    this->heapVector[this->keysPositions[key]].second = newValue;
    // Chama heapifyLeft para a chave atualizada para garantir que a condição de heap é satisfeita à esquerda do heap
    heapifyLeft(this->keysPositions[key]);
  }
}

bool Heap::isEmpty() {
  return (this->size == 0);
}

void Heap::heapifyRight(int index) {
  // Obtém os filhos do índice passado
  int leftChild = 2*index + 1;
  int rightChild = leftChild + 1;

  // Define index como tendo o menor valor entre ele e seus filhos
  int lowestValue = index;

  // Verifica se o filho da esquerda é na verdade o menor
  if (leftChild < this->size && heapVector[leftChild].second < heapVector[lowestValue].second) {
    lowestValue = leftChild;
  }

  // Verifica se o filho da direita é na verdade o menor
  if (rightChild < this->size && heapVector[rightChild].second < heapVector[lowestValue].second) {
    lowestValue = rightChild;
  }

  // Se o menor não for index, troca de posição com index e chama heapifyRight recursivamente para o antigo índice do menor valor
  if (lowestValue != index) {
    swap(lowestValue, index);

    heapifyRight(lowestValue);
  }
}

void Heap::heapifyLeft(int index) {
  // Obtém o pai de index
  int parent = (index - 1)/2;

  // Se index tiver um valor menor que o pai, troca ambos de lugar e chama heapifyLeft para o índice do pai
  if (index && heapVector[parent].second > heapVector[index].second) {
    swap(parent, index);

    heapifyLeft(parent);
  }
}

void Heap::swap(int index1, int index2) {
  // Define um par auxiliar igual a index1
  std::pair<int, double> aux = this->heapVector[index1];

  // Coloca index2 na posição de index1 e atualiza a posição da chave em keysPositions
  this->keysPositions[this->heapVector[index2].first] = index1;
  this->heapVector[index1] = this->heapVector[index2];

  // Coloca o auxiliar na posição de index2 e atualiza a posição da chave em keysPositions
  this->keysPositions[aux.first] = index2;
  this->heapVector[index2] = aux;
}
