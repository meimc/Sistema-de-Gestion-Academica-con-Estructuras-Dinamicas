#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

// Ejercicio 03: aplicar los algoritmos de ordenamiento requeridos.

struct Estudiante {
  int codigo;
  string nombre;
  float promedio;
};

struct Nodo {
  Estudiante data;
  Nodo *next;
};

void insertarAlFinal(Nodo *&head, const Estudiante &e) {
  Nodo *nuevo = new Nodo{e, nullptr};
  if (head == nullptr) {
    head = nuevo;
    return;
  }
  Nodo *curr = head;
  while (curr->next != nullptr) {
    curr = curr->next;
  }
  curr->next = nuevo;
}

int contarNodos(const Nodo *head) {
  int total = 0;
  const Nodo *curr = head;
  while (curr != nullptr) {
    total++;
    curr = curr->next;
  }
  return total;
}

Estudiante *copiarListaAArreglo(const Nodo *head, int &n) {
  n = contarNodos(head);
  if (n == 0) {
    return nullptr;
  }

  Estudiante *arreglo = new Estudiante[n];
  const Nodo *curr = head;
  int i = 0;
  while (curr != nullptr) {
    arreglo[i] = curr->data;
    i++;
    curr = curr->next;
  }
  return arreglo;
}

void liberarLista(Nodo *&head) {
  while (head != nullptr) {
    Nodo *tmp = head;
    head = head->next;
    delete tmp;
  }
}

void mostrarArreglo(const Estudiante *arreglo, int n, const string &titulo) {
  cout << "\n=== " << titulo << " ===\n";
  if (arreglo == nullptr || n == 0) {
    cout << "Arreglo vacio.\n";
    return;
  }
  for (int i = 0; i < n; i++) {
    cout << i << ": Codigo: " << arreglo[i].codigo
         << " |  Nombre: " << arreglo[i].nombre
         << " | Promedio: " << arreglo[i].promedio << "\n";
  }
}

// Ordenamientos
void ordenamientoBurbuja(Estudiante *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j].promedio > arr[j + 1].promedio) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void ordenarSeleccion(Estudiante *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    int minIdx = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j].codigo < arr[j].codigo) {
        minIdx = j;
      }
    }
    if (minIdx != i) {
      swap(arr[i], arr[minIdx]);
    }
  }
}

void ordenarInsercion(Estudiante *arr, int n) {
  for (int i = 0; i < n; i++) {
    Estudiante clave = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j].nombre > clave.nombre) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = clave;
  }
}

int main() {
  cout << "Ejercicio 03 - Ordenamientos" << endl;
  return 0;
}
