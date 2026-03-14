#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ratio>
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
  Nodo* next;
};

void insertarAlFinal(Nodo*& head, const Estudiante& e) {
  Nodo* nuevo = new Nodo{e, nullptr};
  if (head == nullptr) {
    head = nuevo;
    return;
  }
  Nodo* curr = head;
  while (curr->next != nullptr) {
    curr = curr->next;
  }
  curr->next = nuevo;
}

int contarNodos(const Nodo* head) {
  int total = 0;
  const Nodo* curr = head;
  while (curr != nullptr) {
    total++;
    curr = curr->next;
  }
  return total;
}

Estudiante* copiarListaAArreglo(const Nodo* head, int& n) {
  n = contarNodos(head);
  if (n == 0) {
    return nullptr;
  }

  Estudiante* arreglo = new Estudiante[n];
  const Nodo* curr = head;
  int i = 0;
  while (curr != nullptr) {
    arreglo[i] = curr->data;
    i++;
    curr = curr->next;
  }
  return arreglo;
}

void liberarLista(Nodo*& head) {
  while (head != nullptr) {
    Nodo* tmp = head;
    head = head->next;
    delete tmp;
  }
}

void mostrarArreglo(const Estudiante* arreglo, int n, const string& titulo) {
  cout << "\n=== " << titulo << " ===\n";
  if (arreglo == nullptr || n == 0) {
    cout << "Arreglo vacio.\n";
    return;
  }
  for (int i = 0; i < n; i++) {
    cout << i << ": Codigo: " << arreglo[i].codigo << " |  Nombre: " << arreglo[i].nombre
         << " | Promedio: " << arreglo[i].promedio << "\n";
  }
}

// Ordenamientos
void ordenamientoBurbuja(Estudiante* arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j].promedio > arr[j + 1].promedio) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void ordenarSeleccion(Estudiante* arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    int minIdx = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j].codigo < arr[minIdx].codigo) {
        minIdx = j;
      }
    }
    if (minIdx != i) {
      swap(arr[i], arr[minIdx]);
    }
  }
}

void ordenarInsercion(Estudiante* arr, int n) {
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

void quicksortHelper(Estudiante* arr, int low, int high, bool ascendente) {
  if (low < high) {
    float pivote = arr[(low + high) / 2].promedio;
    int i = low;
    int j = high;

    while (i <= j) {
      if (ascendente) {
        while (arr[i].promedio < pivote) i++;
        while (arr[j].promedio > pivote) j--;
      } else {
        while (arr[i].promedio > pivote) i++;
        while (arr[j].promedio < pivote) j--;
      }

      if (i <= j) {
        swap(arr[i], arr[j]);
        i++;
        j--;
      }
    }

    quicksortHelper(arr, low, j, ascendente);
    quicksortHelper(arr, i, high, ascendente);
  }
}

void ordenarQuickSort(Estudiante* arr, int n, bool ascendente = false) {
  quicksortHelper(arr, 0, n - 1, ascendente);
}

void merge(Estudiante* arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  Estudiante* L = new Estudiante[n1];
  Estudiante* R = new Estudiante[n2];

  for (int i = 0; i < n1; i++) {
    L[i] = arr[left + i];
  }
  for (int j = 0; j < n2; j++) {
    R[j] = arr[mid + 1 + j];
  }

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i].codigo <= R[j].codigo)
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }
  while (i < n1) {
    arr[k++] = L[i++];
  }
  while (j < n2) {
    arr[k++] = R[j++];
  }

  delete[] L;
  delete[] R;
}

void mergeSortHelper(Estudiante* arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

void ordenarMergeSort(Estudiante* arr, int n) {
  if (n > 1) mergeSortHelper(arr, 0, n - 1);
}

int main() {
  cout << "=== ejercicio 03: ordenamientos ===" << endl;

  Nodo* lista = nullptr;
  insertarAlFinal(lista, {105, "zulema", 8.5});
  insertarAlFinal(lista, {101, "ana", 9.0});
  insertarAlFinal(lista, {104, "pedro", 7.2});
  insertarAlFinal(lista, {102, "carlos", 9.8});
  insertarAlFinal(lista, {103, "beatriz", 9.5});

  int n;
  Estudiante* arrOriginal = copiarListaAArreglo(lista, n);
  Estudiante* arrAux = new Estudiante[n];

  // lambda para resetear datos antes de cada algoritmo
  auto reset = [&]() {
    for (int i = 0; i < n; i++) arrAux[i] = arrOriginal[i];
  };

  // 1. Burbuja por promedio
  reset();
  mostrarArreglo(arrAux, n, "Original (antes de Burbuja)");
  ordenamientoBurbuja(arrAux, n);
  mostrarArreglo(arrAux, n, "Burbuja por Promedio (Asc)");

  // 2. Seleccion por codigo
  reset();
  mostrarArreglo(arrAux, n, "Original (antes de Seleccion)");
  ordenarSeleccion(arrAux, n);
  mostrarArreglo(arrAux, n, "Seleccion por Codigo (Asc)");

  // 3. Insertion Sort por nombre
  reset();
  mostrarArreglo(arrAux, n, "Original (antes de Insercion)");
  ordenarInsercion(arrAux, n);
  mostrarArreglo(arrAux, n, "Insercion por Nombre (A-Z)");

  // 4. Quick Sort por promedio
  reset();
  mostrarArreglo(arrAux, n, "Original (antes de QuickSort)");
  ordenarQuickSort(arrAux, n, true);
  mostrarArreglo(arrAux, n, "QuickSort por Promedio (Asc)");

  // 5. Merge Sort por codigo
  reset();
  mostrarArreglo(arrAux, n, "Original (antes de MergeSort)");
  ordenarMergeSort(arrAux, n);
  mostrarArreglo(arrAux, n, "MergeSort por Codigo (Asc)");

  // Limpieza
  delete[] arrOriginal;
  delete[] arrAux;
  liberarLista(lista);

  return 0;
}