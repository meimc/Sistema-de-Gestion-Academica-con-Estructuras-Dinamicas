#include <cctype>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Ejercicio 00: definir la estructura base y menu inicial del sistema.

struct Estudiante {
  int codigo;
  string nombre;
  float promedio;
};

void limpiarEntrada() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool esNombreValido(const string &nombre) {
  for (char c : nombre) {
    if (!isspace(static_cast<unsigned char>(c))) {
      return true;
    }
  }
  return false;
}

int leerCodigo() {
  int codigo;
  while (true) {
    cout << "Codigo (> 0): ";
    if (!(cin >> codigo)) {
      cout << "Entrada invalida. Debe ser un entero.\n";
      limpiarEntrada();
      continue;
    }
    limpiarEntrada();
    if (codigo <= 0) {
      cout << "Codigo invalido, Debe ser mayor que 0.\n";
      continue;
    }
    return codigo;
  }
}

string leerNombre() {
  string nombre;
  while (true) {
    cout << "Nombre: ";
    getline(cin, nombre);
    if (!esNombreValido(nombre)) {
      cout << "Error: nombre vacio.\n";
      continue;
    }
    return nombre;
  }
}

float leerPromedio(float min = 0.0f, float max = 20.0f) {
  float promedio;
  while (true) {
    cout << "Promedio (" << min << " - " << max << "): ";
    if (!(cin >> promedio)) {
      cout << "Entrada invalida. Debe de ser un numero.\n";
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
    cout << "Elige una opcion: ";
    if (cin >> opcion && opcion >= min && opcion <= max) {
      limpiarEntrada();
      return opcion;
    }
    limpiarEntrada();
  }
}

int main() {
  mostrarMenu();
  leerOpcion();
  return 0;
}
