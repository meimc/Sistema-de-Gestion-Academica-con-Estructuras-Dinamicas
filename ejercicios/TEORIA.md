# Teoria Necesaria

## 1) Modelado de datos

El sistema pide manejar estudiantes con tres campos:

- `codigo` (int)
- `nombre` (string)
- `promedio` (float)

Antes de programar, defini invariantes:

- `codigo` debe ser unico.
- `promedio` en rango valido (por ejemplo 0.0 a 20.0 o 0.0 a 100.0, segun tu criterio).
- `nombre` no vacio.

Sin invariantes, todo se vuelve un quilombo cuando crece el sistema.

## 2) Lista enlazada simple

Una lista enlazada simple se compone de nodos. Cada nodo guarda datos y un puntero al siguiente.

Ventajas:

- Insercion eficiente si ya tenes la posicion.
- No requiere tamanio fijo.

Desventajas:

- Acceso secuencial (no acceso directo por indice).
- Mas propensa a errores de punteros si no cuidas memoria.

Operaciones clave:

- Insertar al final o al inicio.
- Eliminar por `codigo`.
- Modificar datos por `codigo`.
- Recorrer para mostrar o buscar.

## 3) Arreglo dinamico auxiliar

Para aplicar ciertos algoritmos de ordenamiento y busqueda binaria, conviene copiar los datos de la lista a un arreglo dinamico.

Flujo recomendado:

1. Contar nodos en la lista.
2. Reservar memoria para arreglo de ese tamanio.
3. Copiar cada estudiante al arreglo.
4. Aplicar ordenamiento.
5. Mostrar antes y despues.

## 4) Ordenamientos

Cada algoritmo tiene costo y comportamiento distinto.

- Burbuja: simple, O(n^2), util para entender swaps.
- Seleccion: O(n^2), minimiza swaps pero sigue siendo cuadratico.
- Insertion Sort: O(n^2), muy bueno en listas casi ordenadas.
- Quick Sort: promedio O(n log n), peor caso O(n^2).
- Merge Sort: O(n log n) estable, requiere memoria extra.

Clave didactica: no solo implementes; compara resultados y costos.

## 5) Busquedas

- Busqueda lineal: recorre uno por uno; sirve en lista enlazada.
- Busqueda binaria: requiere arreglo ordenado por la clave buscada.

Si haces binaria en arreglo no ordenado, el resultado puede ser incorrecto aunque compile.

## 6) Recursividad

Una funcion recursiva se llama a si misma hasta llegar a un caso base.

Para este proyecto:

- Promedio general recursivo: suma recursiva y division por cantidad total.
- Impresion recursiva: mostrar nodo actual y llamar al siguiente.

Regla de oro: si no definis bien caso base + avance, te comes recursion infinita.

## 7) Complejidad (lo minimo que tenes que dominar)

- Insercion en lista (inicio): O(1)
- Busqueda en lista: O(n)
- Copiar lista a arreglo: O(n)
- Binaria en arreglo ordenado: O(log n)
- Ordenamientos cuadraticos: O(n^2)
- Ordenamientos eficientes: O(n log n)

## 8) Errores comunes que tenes que evitar

- No liberar memoria (fugas).
- Acceder punteros nulos.
- No validar duplicados de `codigo`.
- Usar binaria sin ordenar antes.
- Mezclar logica de UI con logica de estructuras.
