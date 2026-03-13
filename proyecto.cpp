#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>

using namespace std;
struct Estudiante {
    int codigo;
    string nombre;
    float promedio;
    Estudiante *siguiente;
};

enum Menu{
    REGISTRO=1,
    ELIMINACION,
    MODIFICACION,
    ORDENAR,
    BUSCAR,
    PROMEDIO_GENERAL,
    VER_LISTA,
    SALIR
};

enum Edit{
    CODIGO=1,
    NOMBRE,
    PROMEDIO,
    SALIR2
};

//Validaciones
void validacionMenu(int opc);
void validacionDosOpciones(int &opc);
void validacionRegistro(int &cantidad);
void titulo();
void final();

//Funciones para trabajar estructuras de datos
void registroEstudiante(Estudiante *&cabeza, int codigo, string nombre, float promedio);
void imprimirLista(Estudiante *cabeza);
void eliminarEstudiante(Estudiante *&cabeza, int codigo);
void modificarEstudiante(Estudiante *&cabeza, int codigo);
void leerArreglo(int arr[], int n);
void mostrarArreglo(int arr[], int n);

void cambio(int &a, int &b);

//Algoritmos de ordenamiento
void burbuja(int arr[], int n);
void seleccion(int arr[], int n);
void insertionSort (int arr[], int tam);
int particion(int arr[], int inicio, int fin);
void quickSort(int arr[], int inicio, int fin);
void merge(int arr[], int inicio, int medio, int fin);
void mergeSort(int arr[], int inicio, int fin);

//Algoritmos de búsqueda
int secuencial(int arr[], int tam, int valor, int index);
int binaria(int arr[], int inicio, int fin, int valor);

int promedioGeneral ();

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Estudiante *cabeza = NULL;

    int opc;
    do{
        titulo();

        cout << "--------------- MENU ---------------"
             << "\n1. Registrar nuevo alumno"
             << "\n2. Eliminar alumno existente"
             << "\n3. Modificar datos de alumno"
             << "\n4. Ordenar lista"
             << "\n5. Buscar alumno"
             << "\n6. Promedio general del grupo"
             << "\n7. Ver lista"
             << "\n8. Salir"<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;
        validacionMenu(opc);

        switch (opc){
            case REGISTRO:{
            int codigo, cantidad;
            string nombre;
            float promedio;

            cout << "\nCantidad de registros: ";
            cin >> cantidad;
            validacionRegistro(cantidad);

            for (int i=0; i<cantidad; i++){
                cout << "\nEstudiante " << i+1 << ": " << endl;
                cout << "Código: ";
                cin >> codigo;
                cin.ignore();
                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "Promedio: ";
                cin >> promedio;
                registroEstudiante(cabeza, codigo, nombre, promedio);
            }
            break;
            }
            case ELIMINACION:{
                int cantidad, codigo;
                cout << "\nCantidad de alumnos a eliminar: ";
                cin >> cantidad;
                validacionRegistro(cantidad);

                imprimirLista(cabeza);

                for (int i=0; i<cantidad; i++){
                    cout << "\nCódigo de estudiante a eliminar: ";
                    cin >> codigo;
                    cout << endl;
                    eliminarEstudiante(cabeza, codigo);
                }
                
                break;
            }
            case MODIFICACION:{
                int codigo;
                cout << "\nCódigo de estudiante a modificar: ";
                cin >> codigo;
                cout << endl;
                modificarEstudiante(cabeza, codigo);
                break;
            }
            case ORDENAR:{
                break;
            }
            case BUSCAR:{
                break;
            }
            case PROMEDIO_GENERAL:{
                break;
            }
            case VER_LISTA:{
                imprimirLista(cabeza);
                break;
            }
            default:{
                if(opc!=8){
                    cout<<"\nError. Ingresa una opción válida del menú."<<endl;
                
                    cout << "\nPresiona [Enter] para volver al menú...";
                    cin.ignore();
                    cin.get();
                }
                break;
            } 
        }
    }while(opc!=SALIR);
    
    final();
    return 0;
}

void titulo()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║            SISTEMA DE GESTIÓN ACADÉMICA            ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

void registroEstudiante(Estudiante *&cabeza, int codigo, string nombre, float promedio){
    Estudiante *nuevo = new Estudiante();
    nuevo->codigo = codigo;
    nuevo->nombre = nombre;
    nuevo->promedio = promedio;
    nuevo->siguiente = NULL;

    if(cabeza == NULL)
        cabeza = nuevo;
    else{
        Estudiante *actual = cabeza;
        while(actual->siguiente!=NULL){
            if(actual->codigo == codigo){
                cout << "\nError: Código en uso, ingrese un código válido."<<endl;
                cout << "\nPresiona [Enter] para volver al menú...";
                cin.ignore();
                cin.get();
                return;
            }
            actual = actual->siguiente;
        }
            
        actual->siguiente = nuevo;
    }
}

void imprimirLista(Estudiante *cabeza){

    cout << endl;
    cout << left << setw(10) << "Codigo"
         << setw(25) << "Nombre"
         << setw(10) << "Promedio" << endl;

    cout << "---------------------------------------------" << endl;

    if (cabeza==NULL)
        cout << "\nError: No hay datos en la lista."<<endl;
        
    while (cabeza != NULL){
        cout << left << setw(10) << cabeza->codigo 
             << setw(25) << cabeza->nombre 
             << setw(10) << cabeza->promedio << endl;
        cabeza = cabeza->siguiente;
    }

    cout << "\nPresiona [Enter] para salir de la lista";
    cin.ignore();
    cin.get();
}

void eliminarEstudiante(Estudiante *&cabeza, int codigo){
    Estudiante *eliminado = cabeza;
    Estudiante *aux = NULL;

    while(eliminado != NULL && eliminado->codigo != codigo){
            aux = eliminado;
            eliminado = eliminado->siguiente;
        }

    if(eliminado == NULL){
        cout << "Error: No existe el código."<<endl;
        return;
    }

    if(aux == NULL)
        cabeza = eliminado->siguiente;
    else
        aux->siguiente = eliminado->siguiente;
    
    delete eliminado;
}

void modificarEstudiante(Estudiante *&cabeza, int codigo){
    Estudiante *actual = cabeza;

    while(actual != NULL && actual->codigo != codigo){
            actual = actual->siguiente;
        }

    if(actual == NULL){
        cout << "Error: No existe el código."<<endl;
        return;
    }
    int opc;
    do{
        cout << "--------------- MENU ---------------"
             << "\n1. Cambiar código"
             << "\n2. Cambiar nombre"
             << "\n3. Cambiar promedio"
             << "\n4. Salir"<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;
        validacionMenu(opc);

        switch (opc){
            case CODIGO:{
                cout << "Ingresa el nuevo código: ";
                cin >> actual->codigo;
                break;
            }
            case NOMBRE:{
                cout << "Ingresa el nuevo nombre: ";
                cin.ignore();
                getline(cin, actual->nombre);
                break;
            }
            case PROMEDIO:{
                cout << "Ingresa el nuevo promedio: ";
                cin >> actual->promedio;
                break;
            }
            default:
            if(opc!=4){
                    cout<<"\nError. Ingresa una opción válida del menú."<<endl;
                
                    cout << "\nPresiona [Enter] para volver al menú...";
                    cin.ignore();
                    cin.get();
                }
                break;
        }
    }while(opc!=SALIR2);
}

void leerArreglo(int arr[], int n){
    for (int i=0; i<n; i++){
        cout << i+1 << ".- ";
        cin >> arr[i];
    }
}

void mostrarArreglo(int arr[], int n){
    for (int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void cambio(int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

void burbuja(int arr[], int n){
    for(int i=0; i<n-1; i++){
        for (int j=0; j<n-1-i; j++){
            if(arr[j]>arr[j+1]){
                cambio(arr[j], arr[j+1]);
            }
        }
    }
}

void seleccion(int arr[], int n){
    for(int i=0; i<n-1; i++){
        int min = i;

        for (int j=i+1; j<n; j++){
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        if (min != i) {
            cambio(arr[i], arr[min]);
        }
    }
}

void insertionSort (int arr[], int tam){
    int min = arr[0];
    for (int i=1; i<tam; i++){
        int extracto = arr[i];
        int j = i-1;
        
        while (j>=0 && arr[j]>extracto){
            arr[j+1]=arr[j];
            j--;
        }
    
        arr[j+1]= extracto;
    }

}

int particion(int arr[], int inicio, int fin) {
    int pivote = arr[fin]; 
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (arr[j] < pivote) {
            i++;
            cambio(arr[i], arr[j]);
        }
    }

    cambio(arr[i + 1], arr[fin]);
    return i + 1;
}

void quickSort(int arr[], int inicio, int fin) {
    if (inicio < fin) {
        int pivote = particion(arr, inicio, fin);

        quickSort(arr, inicio, pivote - 1);
        quickSort(arr, pivote + 1, fin);
    }
}

void merge(int arr[], int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    int izquierda[n1], derecha[n2];

    for (int i = 0; i < n1; i++)
        izquierda[i] = arr[inicio + i];

    for (int j = 0; j < n2; j++)
        derecha[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (izquierda[i] <= derecha[j]) {
            arr[k] = izquierda[i];
            i++;
        } else {
            arr[k] = derecha[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = izquierda[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = derecha[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;

        mergeSort(arr, inicio, medio);
        mergeSort(arr, medio + 1, fin);

        merge(arr, inicio, medio, fin);
    }
}

int secuencial(int arr[], int tam, int valor, int index){
    if(index==tam)
        return -1;
    if(arr[index]==valor)
        return index;

    return secuencial(arr, tam, valor, index+1);
}

int binaria(int arr[], int inicio, int fin, int valor){
    if (inicio>fin)
        return -1;

    int medio = (inicio + fin)/2;

    if (valor==arr[medio]){
        return medio;
    }else if (valor<arr[medio]){
        return binaria(arr, inicio, medio-1, valor);
    }else{
        return binaria(arr, medio+1, fin, valor);
    }
}

void validacionMenu(int opc) {
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
    }
}

void validacionDosOpciones(int &opc) {
    while (opc != 1 || opc != 2 || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error. Ingresa una opción válida." << endl;
        cin >> opc;
    }
}

void validacionRegistro(int &cantidad) {
    int opc=2;
    while ((cantidad < 1 && opc == 2) || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Error. ¿Desea volver al menú principal?\n1. SI // 2. NO"<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;
        validacionDosOpciones(opc);
        if (opc == 2){
            cout << "\nDebe hacer el registro de al menos 1 alumno" << endl;
            cout << "Ingrese la cantidad de registros: ";
            cin >> cantidad;
        }
        
    }
}

void final() {
    cout << endl
         << endl
         << "--------------------- Gracias ------------------------" << endl
         << endl;
}