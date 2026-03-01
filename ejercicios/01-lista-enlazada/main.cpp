#include <cctype>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct Estudiante {
  int codigo;
  string nombre;
  float promedio;
};

struct Nodo {
  Estudiante data;
  Nodo *next;
};

void limpiarEntrada() {
  if (cin.fail()) {
    cin.clear();
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool esNombreValido(const string &nombre) {
  bool tieneCaracter = false;
  for (char c : nombre) {
    if (!isspace(static_cast<unsigned char>(c))) {
      tieneCaracter = true;
      break;
    }
  }
  return tieneCaracter;
}

int leerCodigo() {
  int codigo;
  while (true) {
    cout << "Ingrese codigo (> 0): ";
    if (!(cin >> codigo)) {
      cout << "Ingrese un codigo valido, debe ser un entero!\n";
      limpiarEntrada();
      continue;
    }
    limpiarEntrada();
    if (codigo <= 0) {
      cout << "El codigo debe ser mayor que 0!\n";
      continue;
    }
    return codigo;
  }
}

string leerNombre() {
  string nombre;
  while (true) {
    getline(cin, nombre);
    if (!esNombreValido(nombre)) {
      cout << "Ingrese un nombre valido! No vacio.\n";
      continue;
    }
    return nombre;
  }
}

float leerPromedio(float min = 0.0f, float max = 20.0f) {
  float promedio;
  while (true) {
    if (!(cin >> promedio)) {
      cout << "Entrada invalida debe ser un numero!\n";
      limpiarEntrada();
      continue;
    }
    if (promedio < min || promedio > max) {
      cout << "Fuera de rango.\n";
      continue;
    }
    return promedio;
  }
}

bool existeCodigo(Nodo *head, int codigo) {
  Nodo *curr = head;
  while (curr != nullptr) {
    if (curr->data.codigo == codigo) {
      return true;
    }
    curr = curr->next;
  }
  return false;
}

bool insertarEstudiante(Nodo *&head, const Estudiante &e) {
  if (existeCodigo(head, e.codigo)) {
    return false;
  }

  Nodo *nuevo = new Nodo{e, nullptr};

  if (head == nullptr) {
    head = nuevo;
    return true;
  }

  Nodo *curr = head;
  while (curr->next != nullptr) {
    curr = curr->next;
  }
  curr->next = nuevo;
  return true;
}

bool eliminarPorCodigo(Nodo *&head, int codigo) {
  if (head == nullptr) {
    return false;
  }
  if (head->data.codigo == codigo) {
    Nodo *tmp = head;
    head = head->next;
    delete tmp;
    return true;
  }
  Nodo *prev = head;
  Nodo *curr = head->next;

  while (curr != nullptr) {
    if (curr->data.codigo == codigo) {
      prev->next = curr->next;
      delete curr;
      return true;
    }
    prev = curr;
    curr = curr->next;
  }
  return false;
}

bool modificarPorCodigo(Nodo *head, int codigo) {
  Nodo *curr = head;
  while (curr != nullptr) {
    if (curr->data.codigo == codigo) {
      cout << "Nuevo nombre: \n";
      curr->data.nombre = leerNombre();
      cout << "Nuevo promedio: \n";
      curr->data.promedio = leerPromedio();
      return true;
    }
    curr = curr->next;
  }
  return false;
}

void mostrarTodos(Nodo *head) {
  if (head == nullptr) {
    cout << "Lista vacia.\n";
    return;
  }

  Nodo *curr = head;
  while (curr != nullptr) {
    cout << "Codigo: " << curr->data.codigo
         << " | Nombre: " << curr->data.nombre
         << " | Promedio: " << curr->data.promedio << "\n";
    curr = curr->next;
  }
}

void liberarLista(Nodo *&head) {
  while (head != nullptr) {
    Nodo *tmp = head;
    head = head->next;
    delete tmp;
  }
}

Estudiante crearEstudiante() {
  Estudiante e;
  e.codigo = leerCodigo();
  e.nombre = leerNombre();
  e.promedio = leerPromedio(0.0f, 20.0f);
  return e;
}

void mostrarMenu() {
  cout << "\n=== MENU ESTUDIANTES ===\n";
  cout << "1. Registrar\n";
  cout << "2. Eliminar\n";
  cout << "3. Modificar\n";
  cout << "4. Mostrar\n";
  cout << "5. Salir\n";
}

int leerOpcion(int min = 1, int max = 5) {
  int opcion;
  while (true) {
    if (cin >> opcion && opcion >= min && opcion <= max) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return opcion;
    }
    cout << "Opcion invalida.\n";
    limpiarEntrada();
  }
}

// Ejercicio 01: implementar gestion de estudiantes con lista enlazada simple.
int main() {
  Nodo *head = nullptr;

  while (true) {
    mostrarMenu();
    int opcion = leerOpcion(1, 5);
    bool salir = false;

    switch (opcion) {
    case 1: {
      Estudiante e = crearEstudiante();
      if (insertarEstudiante(head, e)) {
        cout << "Estudiante insertado.\n";
      } else {
        cout << "Codigo duplicado. No se inserto.\n";
      }
      break;
    }
    case 2: {
      int codigo = leerCodigo();
      if (eliminarPorCodigo(head, codigo)) {
        cout << "Estudiante eliminado.\n";
      } else {
        cout << "Codigo no encontrado.\n";
      }
      break;
    }
    case 3: {
      int codigo = leerCodigo();
      if (modificarPorCodigo(head, codigo)) {
        cout << "Estudiante modificado.\n";
      } else {
        cout << "Codigo no encontrado.\n";
      }
      break;
    }
    case 4: {
      mostrarTodos(head);
      break;
    }
    case 5: {
      liberarLista(head);
      cout << "Saliendo...\n";
      salir = true;
      break;
    }
    default:
      cout << "Ingrese una opcion valida.\n";
    }
    if (salir) {
      break;
    }
  }
  return 0;
}
