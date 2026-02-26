#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

struct Estudiante {
    int codigo;
    string nombre;
    float promedio;
};

void mostrarArreglo(int arr[], int n);

void cambio(int &a, int &b);

void burbuja(int arr[], int n);

void seleccion(int arr[], int n);

void insertionSort (int arr[], int tam);

int particion(int arr[], int inicio, int fin);
void quickSort(int arr[], int inicio, int fin);

void merge(int arr[], int inicio, int medio, int fin);
void mergeSort(int arr[], int inicio, int fin);

int secuencial(int arr[], int tam, int valor, int index);

int binaria(int arr[], int inicio, int fin, int valor);

int promedioGeneral ();

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    

    return 0;
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