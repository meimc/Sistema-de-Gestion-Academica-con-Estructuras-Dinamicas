#include <cstddef>
#include <iostream>
#include <string>

using namespace std;

// Ejercicio 02: copiar la lista a un arreglo dinamico auxiliar.
//
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

void mostrarArreglo(const Estudiante *arreglo, int n) {
  if (arreglo == nullptr || n == 0) {
    cout << "El arreglo esta vacio.\n";
    return;
  }
  for (int i = 0; i < n; i++) {
    cout << "Codigo: " << arreglo[i].codigo
         << " | Nombre: " << arreglo[i].nombre
         << " | Promedio: " << arreglo[i].promedio << "\n";
  }
}

void liberarLista(Nodo *&head) {
  while (head != nullptr) {
    Nodo *tmp = head;
    head = head->next;
    delete tmp;
  }
}

int main() {
  Nodo *head = nullptr;
  insertarAlFinal(head, {101, "ana", 17.4f});
  insertarAlFinal(head, {102, "luis", 15.4f});
  insertarAlFinal(head, {103, "marta", 14.4f});

  int n = 0;
  Estudiante *arreglo = copiarListaAArreglo(head, n);

  cout << "Elementos copiados: " << n << "\n";
  mostrarArreglo(arreglo, n);
  delete[] arreglo;
  liberarLista(head);
  return 0;
}
