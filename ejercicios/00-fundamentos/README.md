# Ejercicio 00 - Fundamentos y modelo

## Objetivo

Definir la estructura base del sistema (`Estudiante`) y construir un menu de consola robusto para preparar los ejercicios siguientes.

## Teoria necesaria (sin chamuyo)

### 1) Modelado de datos

Antes de programar estructuras complejas, primero tenes que modelar bien la entidad principal.

Para este proyecto:

- `codigo` (`int`): identificador unico.
- `nombre` (`string`): nombre del estudiante.
- `promedio` (`float`): nota acumulada.

Si no definis reglas desde el inicio, despues se rompe todo. Minimo de invariantes:

- `codigo > 0`
- `nombre` no vacio
- `promedio` en rango valido

### 2) Separacion de responsabilidades

No mezcles todo en `main()`. Separar te ahorra quilombo luego.

- Funciones de entrada/validacion
- Funcion para mostrar menu
- Funcion para procesar opcion

Esto te deja el codigo mantenible y reutilizable cuando metas lista enlazada.

### 3) Validacion de entrada en consola

En C++, cuando el usuario mete texto donde va un numero, `cin` entra en estado de error.

Tenes que dominar este flujo:

1. Leer dato.
2. Verificar si fallo.
3. Limpiar estado (`cin.clear()`).
4. Limpiar buffer (`cin.ignore(...)`).
5. Volver a pedir.

Si no haces esto, el menu queda trabado o salta opciones solo.

### 4) Flujo de programa por menu

El patron basico es:

- Mostrar opciones.
- Leer opcion validada.
- Ejecutar accion con `switch`.
- Repetir hasta salir.

Este esqueleto lo vas a reutilizar en TODO el sistema.

## Consigna practica

1. Crea `struct Estudiante` con `codigo`, `nombre`, `promedio`.
2. Crea un menu de consola con opciones:
   - Registrar
   - Eliminar
   - Modificar
   - Mostrar
   - Salir
3. Implementa validaciones basicas de entrada para opcion, codigo y promedio.
4. Deja funciones separadas (no toda la logica dentro de `main`).

## Ejercicios cortos de practica

1. **Validar entero**: funcion que no retorna hasta recibir un `int` valido.
2. **Validar float en rango**: por ejemplo `0.0` a `20.0`.
3. **Menu resiliente**: probar entradas invalidas seguidas (`a`, `-1`, `100`, etc.) y que el programa siga estable.

## Criterios de aceptacion

- El menu no se rompe ante entradas invalidas.
- La estructura de datos esta clara y reutilizable.
- Las validaciones evitan estados inconsistentes.
- El codigo base queda listo para conectar con lista enlazada en el siguiente ejercicio.
