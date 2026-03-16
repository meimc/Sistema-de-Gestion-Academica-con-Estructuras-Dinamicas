#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <windows.h>


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
    SALIR=0
};

enum Edit{
    CODIGO=1,
    NOMBRE,
    PROMEDIO
};

enum Orden{
    PROMEDIO_ASCENDENTE=1,
    PROMEDIO_DESCENDENTE,
    CODIGO_ASCENDENTE,
    CODIGO_DESCENDENTE,
    NOMBRE_ORDEN
};

enum Busqueda{
    NOMBRE_BUSQUEDA=1,
    CODIGO_BUSQUEDA
};

//Validaciones
void validacionMenu(int &opc);
void validacionDosOpciones(int &opc);
void validacionCantidad(int &cantidad, string tramite, Estudiante *cabeza);
void validacionRegistroCodigo(Estudiante *cabeza, int &codigo);
void validacionRegistroPromedio(float &promedio);
void validacionModificar(Estudiante *cabeza, int &codigo);
void titulo();
void pausa ();
void liberarLista(Estudiante *&cabeza);
void final();

//Funciones para trabajar estructuras de datos
void registroEstudiante(Estudiante *&cabeza, int codigo, string nombre, float promedio);
void imprimirLista(Estudiante *cabeza);
void eliminarEstudiante(Estudiante *&cabeza, int codigo);
void modificarEstudiante(Estudiante *&cabeza, int codigo);
int tamanioLista (Estudiante *cabeza);
void copiarLista (Estudiante arreglo[], Estudiante *cabeza, int tam);
void mostrarArreglo(Estudiante arr[], int n);
void ordenacion (Estudiante arr[], int tamanio);
void guardarArregloEnLista(Estudiante *cabeza, Estudiante arreglo[], int tamanio);
void busqueda(Estudiante *cabeza, Estudiante arr[], int n);

float sumaPromedios(Estudiante *cabeza);
void inicialMayus(string &nombre);

//Algoritmos de ordenamiento
void burbuja(Estudiante arr[], int n);
void seleccion(Estudiante arr[], int n);
void insertionSort (Estudiante arr[], int tam);
int particion(Estudiante arr[], int inicio, int fin);
void quickSort(Estudiante arr[], int inicio, int fin);
void merge(Estudiante arr[], int inicio, int medio, int fin);
void mergeSort(Estudiante arr[], int inicio, int fin);

//Algoritmos de búsqueda
void secuencial(Estudiante *cabeza, string nombre);
void binaria(Estudiante arr[], int inicio, int fin, int valor);

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
             << "\n0. Salir"<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;
        validacionMenu(opc);

        switch (opc){
            case REGISTRO:{
            int codigo, cantidad;
            string nombre;
            float promedio;

            string registro = "registar";

            cout << "\nCantidad de registros: ";
            cin >> cantidad;
            validacionCantidad(cantidad, registro, cabeza);

            for (int i=0; i<cantidad; i++){
                cout << "\nEstudiante " << i+1 << ": " << endl;
                cout << "Código: ";
                cin >> codigo;
                validacionRegistroCodigo(cabeza, codigo);

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nombre: ";
                getline(cin, nombre);
                inicialMayus(nombre);
                
                cout << "Promedio: ";
                cin >> promedio;
                validacionRegistroPromedio(promedio);

                registroEstudiante(cabeza, codigo, nombre, promedio);
            }
            break;
            }
            case ELIMINACION:{
            int cantidad, codigo;
            string eliminacion = "eliminar";

            imprimirLista(cabeza);

            cout << "\nCantidad de alumnos a eliminar: ";
            cin >> cantidad;
            validacionCantidad(cantidad, eliminacion, cabeza);

            for (int i=0; i<cantidad; i++){
                cout << "\nCódigo de estudiante a eliminar: ";
                cin >> codigo;
                cout << endl;
                eliminarEstudiante(cabeza, codigo);
            }

            cout << "\nLista actualizada:"<<endl;
            imprimirLista(cabeza);
                
            pausa();
            break;
            }
            case MODIFICACION:{
            imprimirLista(cabeza);

            int codigo;
            cout << "\nCódigo de estudiante a modificar: ";
            cin >> codigo;
            validacionModificar(cabeza, codigo);

            modificarEstudiante(cabeza, codigo);
            break;
            }
            case ORDENAR:{
                int tamanio = tamanioLista(cabeza);
                Estudiante *arreglo = new Estudiante[tamanio];

                copiarLista(arreglo, cabeza, tamanio);
                ordenacion(arreglo, tamanio);

                int opc;
                cout << "\n¿Desea guardar los cambios?"
                     << "\n1.Si // 2.No"<<endl;
                cout << "Ingresa la opción: ";
                cin >> opc;

                validacionDosOpciones(opc);

                if(opc == 1){
                    guardarArregloEnLista(cabeza, arreglo, tamanio);
                }

                delete[] arreglo;
                break;
            }
            case BUSCAR:{
                int tamanio = tamanioLista(cabeza);
                Estudiante *arreglo = new Estudiante[tamanio];

                copiarLista(arreglo, cabeza, tamanio);
                busqueda(cabeza, arreglo, tamanio);

                delete[] arreglo;
                break;
            }
            case PROMEDIO_GENERAL:{
                if(tamanioLista(cabeza)==0){
                    cout << "\nNo hay notas existentes" << endl;
                    break;
                }

                imprimirLista(cabeza);

                cout << "\nPromedio general del grupo: " 
                     << sumaPromedios(cabeza)/tamanioLista(cabeza) << endl;
                
                pausa();
                break;
            }
            case VER_LISTA:{
                cout << endl;
                cout << "(Impresión con Lista Recursiva)" << endl;
                cout << left << setw(10) << "Codigo"
                     << setw(25) << "Nombre"
                     << setw(10) << "Promedio" << endl;

                cout << "---------------------------------------------" << endl;
                imprimirLista(cabeza);
                pausa();
                break;
            }
            default:{
                if(opc!=SALIR){
                    cout<<"\nError: Ingresa una opción válida del menú."<<endl;
                
                    pausa();
                }
                break;
            } 
        }
    }while(opc!=SALIR);
    
    final();

    liberarLista(cabeza);

    return 0;
}

void titulo(){
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

void pausa (){
    cout << "\nPresiona [Enter] para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
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
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void imprimirLista(Estudiante *cabeza){
    if (cabeza==NULL){
        return;
    }
    
    cout << left << setw(10) << cabeza->codigo 
         << setw(25) << cabeza->nombre 
         << setw(10) << cabeza->promedio << endl;

    imprimirLista(cabeza->siguiente);
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
        cout << "--------------- MENU ---------------"
             << "\n1. Cambiar código"
             << "\n2. Cambiar nombre"
             << "\n3. Cambiar promedio"<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;
        validacionMenu(opc);

        switch (opc){
            case CODIGO:{
                cout << "Ingresa el nuevo código: ";
                cin >> actual->codigo;
                validacionRegistroCodigo(cabeza, actual->codigo);
                break;
            }
            case NOMBRE:{
                cout << "Ingresa el nuevo nombre: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, actual->nombre);
                break;
            }
            case PROMEDIO:{
                cout << "Ingresa el nuevo promedio: ";
                cin >> actual->promedio;
                validacionRegistroPromedio(actual->promedio);
                break;
            }
            default:{
                    cout<<"\nError. Ingresa una opción válida del menú."<<endl;
                
                    pausa();
                }
                break;
        }
}

int tamanioLista (Estudiante *cabeza){
    int contador=0;
    while(cabeza!=NULL){
        contador++;
        cabeza=cabeza->siguiente;
    }
    return contador;
}

void copiarLista (Estudiante arreglo[], Estudiante *cabeza, int tamanio){
    for (int i=0; i<tamanio; i++){
        arreglo[i].codigo=cabeza->codigo;
        arreglo[i].nombre=cabeza->nombre;
        arreglo[i].promedio=cabeza->promedio;
        cabeza=cabeza->siguiente;
    }
}

void mostrarArreglo(Estudiante arr[], int n){
    cout << endl;
    cout << left << setw(10) << "Codigo"
         << setw(25) << "Nombre"
         << setw(10) << "Promedio" << endl;

    cout << "---------------------------------------------" << endl;
    cout << "(Impresión con Arreglo)" << endl;

    if (n<=0)
        cout << "\nError: No hay datos en la lista."<<endl;

    for (int i=0; i<n; i++){
        cout << left << setw(10) << arr[i].codigo
             << setw(25) << arr[i].nombre
             << setw(10) << arr[i].promedio << endl;
    }
    cout << endl;
}

float sumaPromedios(Estudiante *cabeza){
    if(cabeza == NULL)
        return 0;

    return cabeza->promedio+sumaPromedios(cabeza->siguiente);
}

void ordenacion (Estudiante arr[], int tamanio){

    mostrarArreglo(arr, tamanio);

    int opc;
        cout << "---------- MENÚ PARA ORDENAR ----------"
             << "\n1. Ordenar por promedio ascendente (Burbuja)"
             << "\n2. Ordenar por promedio descendente (Quick Sort)"
             << "\n3. Ordenar por código ascendente (Selección)"
             << "\n4. Ordenar por código descendente (Merge Sort)"
             << "\n5. Orden alfabetico (Insertion Sort)"<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;

        switch (opc){
        case PROMEDIO_ASCENDENTE:{
            burbuja(arr, tamanio);
            mostrarArreglo(arr, tamanio);
            break;
        }
        case PROMEDIO_DESCENDENTE:{
            quickSort(arr, 0, tamanio-1);
            mostrarArreglo(arr, tamanio);
            break;
        }
        case CODIGO_ASCENDENTE:{
            seleccion(arr, tamanio);
            mostrarArreglo(arr, tamanio);
            break;
        }
        case CODIGO_DESCENDENTE:{
            mergeSort(arr, 0, tamanio-1);
            mostrarArreglo(arr, tamanio);
            break;
        }
        case NOMBRE_ORDEN:{
            insertionSort(arr, tamanio);
            mostrarArreglo(arr, tamanio);
            break;
        }
        default:{
            cout<<"\nError. Ingresa una opción válida del menú."<<endl;
                
            cout << "\nPresiona [Enter] para volver al menú...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            break;
        }
    }
}

void guardarArregloEnLista(Estudiante *cabeza, Estudiante arreglo[], int tamanio){
    Estudiante *actual = cabeza;

    for(int i = 0; i < tamanio && actual != NULL; i++){
        actual->codigo = arreglo[i].codigo;
        actual->nombre = arreglo[i].nombre;
        actual->promedio = arreglo[i].promedio;

        actual = actual->siguiente;
    }
}

void busqueda(Estudiante *cabeza, Estudiante arr[], int n){
    if(n == 0){
        cout << "\nNo hay estudiantes registrados." << endl;
        pausa();
        return;
    }
        
    int opc;
        cout << "---------- MENÚ PARA BÚSQUEDA ----------"
             << "\n1. Buscar por nombre (Lineal)"
             << "\n2. Buscar por código (Binaria)"<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;

        switch (opc){
        case NOMBRE_BUSQUEDA:{
            string nombre;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout <<"\nIngresa el nombre a buscar:";
            getline(cin, nombre);
            
            inicialMayus(nombre);

            secuencial(cabeza, nombre);
            
            pausa();
            break;
        }
        case CODIGO_BUSQUEDA:{
            int codigo;
            cout <<"\nIngresa el código a buscar:";
            cin >> codigo;
            validacionModificar(cabeza, codigo);

            seleccion (arr, n);

            binaria(arr, 0, n-1, codigo);

            pausa();
            break;
        }
        default:{
            cout<<"\nError. Ingresa una opción válida del menú."<<endl;
                
            pausa();
            break;
        }
    }
}

void inicialMayus(string &nombre){
    for(int i = 0; i < nombre.length(); i++){
        nombre[i] = tolower(nombre[i]);

        if(i == 0 || nombre[i-1] == ' ')
            nombre[i] = toupper(nombre[i]);
    }
}

void burbuja(Estudiante arr[], int n){
    for(int i=0; i<n-1; i++){
        for (int j=0; j<n-1-i; j++){
            if(arr[j].promedio>arr[j+1].promedio){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void seleccion(Estudiante arr[], int n){
    for(int i=0; i<n-1; i++){
        int min = i;

        for (int j=i+1; j<n; j++){
            if (arr[j].codigo < arr[min].codigo) {
                min = j;
            }
        }

        if (min != i) {
            swap(arr[i], arr[min]);
        }
    }
}

void insertionSort (Estudiante arr[], int tam){

    for (int i=1; i<tam; i++){

        Estudiante extracto = arr[i];
        int j = i-1;
        
        while (j>=0 && arr[j].nombre>extracto.nombre){
            arr[j+1]=arr[j];
            j--;
        }
    
        arr[j+1] = extracto;
    }

}

int particion(Estudiante arr[], int inicio, int fin) {
    float pivote = arr[fin].promedio; 
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (arr[j].promedio > pivote) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[fin]);
    return i + 1;
}

void quickSort(Estudiante arr[], int inicio, int fin) {
    if (inicio < fin) {
        int pivote = particion(arr, inicio, fin);

        quickSort(arr, inicio, pivote - 1);
        quickSort(arr, pivote + 1, fin);
    }
}

void merge(Estudiante arr[], int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    Estudiante *izquierda = new Estudiante[n1];
    Estudiante *derecha = new Estudiante[n2];

    for (int i = 0; i < n1; i++)
        izquierda[i] = arr[inicio + i];

    for (int j = 0; j < n2; j++)
        derecha[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (izquierda[i].codigo >= derecha[j].codigo) {
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

    delete[] izquierda;
    delete[] derecha;
}

void mergeSort(Estudiante arr[], int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;

        mergeSort(arr, inicio, medio);
        mergeSort(arr, medio + 1, fin);

        merge(arr, inicio, medio, fin);
    }
}

void secuencial(Estudiante *cabeza, string nombre){
    int aux=0;
    while(cabeza!=NULL){
        if (cabeza->nombre.find(nombre) != string::npos){
            if(aux == 0)
                cout << "\nDatos del alumno(s) encontrado(s): " << endl;
            aux++;
            cout << left << setw(10) << cabeza->codigo 
                 << setw(25) << cabeza->nombre 
                 << setw(10) << cabeza->promedio << endl;
        }
        cabeza=cabeza->siguiente;
    }

    if(aux == 0)
        cout << "\nAlumno no encontrado" << endl;
}

void binaria(Estudiante arr[], int inicio, int fin, int codigo){
    if (inicio>fin){
        cout << "Alumno no encontrado" << endl;
        pausa();
        return;
    }

    int medio = (inicio + fin)/2;

    if (codigo==arr[medio].codigo){
        cout << "\nDatos del alumno encontrado: " << endl;
        cout << left << setw(10) << arr[medio].codigo 
             << setw(25) << arr[medio].nombre 
             << setw(10) << arr[medio].promedio  << endl;
        return;
    }else if (codigo<arr[medio].codigo){
        binaria(arr, inicio, medio-1, codigo);
    }else{
        binaria(arr, medio+1, fin, codigo);
    }
}

void validacionMenu(int &opc) {
    while (opc<0 || opc>7 || cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nError. Ingresa una opción del menú: ";
        cin >> opc;
    }
}

void validacionDosOpciones(int &opc) {
    while ((opc != 1 && opc != 2) || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error. Ingresa una opción válida." << endl;
        cin >> opc;
    }
}

void validacionCantidad(int &cantidad, string tramite, Estudiante *cabeza) {
    int opc=2;
    while ((cantidad < 1 && opc == 2) || cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nError: Debe "<< tramite <<" al menos 1 alumno."
             << "\n¿Desea volver al menú principal?\n1. SI // 2. NO"
             << "\nSeleccione una opcion: ";
        cin >> opc;

        if (opc == 2){
            cout << "\nIngrese la cantidad a "<< tramite <<": ";
            cin >> cantidad;
        }
    }

    while(tramite=="eliminar"&&(cantidad>tamanioLista(cabeza) ||cantidad < 1) || cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nError: Ingrese una cantidad de alumnos a "<< tramite <<" válida."
             << "\nIngrese la cantidad a "<< tramite <<": ";
            cin >> cantidad;
    }
}

void validacionRegistroCodigo(Estudiante *cabeza, int &codigo){
    Estudiante *actual = cabeza;
    while (cin.fail()||codigo<=99) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nError: Código no válido, ingrese números positivos de 3 dígitos mínimo como código."
                 << "\nNuevo código: ";
            cin >> codigo;
    }
    while (actual!=NULL){
        if (cin.fail()||codigo<=99) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nError: Código no válido, ingrese números positivos de 3 dígitos mínimo como código."
                 << "\nNuevo código: ";
            cin >> codigo;
            actual=cabeza;
        }else if(actual->codigo == codigo){
            cout << "\nError: Código en uso, ingrese un código válido."
                 << "\nNuevo código: ";
            cin >> codigo;
            actual=cabeza;
        }
        actual=actual->siguiente;
    }
}

void validacionRegistroPromedio(float &promedio){
    while(cin.fail()||promedio<0||promedio>20){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nError: Promedio fuera del rango, ingrese un promedio válido."
             << "\nNuevo promedio: ";
        cin >> promedio;
    }
}

void validacionModificar(Estudiante *cabeza, int &codigo){
    bool encontrado = false;
    while(!encontrado){
        while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nError: Ingresa un código válido."
             << "\nCódigo: ";
        cin >> codigo;
        }

        Estudiante *actual = cabeza;

        while(actual!=NULL){
            if(actual->codigo==codigo){
                encontrado = true;
                return;
            }
            actual = actual->siguiente;
        }

        if(!encontrado){
            cout << "\nError: Ingresa un código existente."
                 << "\nCódigo: ";
            cin >> codigo;
        }  
    }     
}

void liberarLista(Estudiante *&cabeza){
    while(cabeza != NULL){
        Estudiante *temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void final() {
    cout << endl
         << endl
         << "--------------------- Gracias ------------------------" << endl
         << endl;
}