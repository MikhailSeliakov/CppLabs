#include <iostream>
#include <conio.h>
using namespace std;

void minMaxSort(int mas[], int n) {
    int imin;
    for(int i = 0; i < n-1; i++) {
        imin = i;
        for(int j = i+1; j < n; j++) {
            if(mas[j] < mas[imin]) imin = j;
        }
        // Обмен элементов
        int temp = mas[i];
        mas[i] = mas[imin];
        mas[imin] = temp;
    }
}

int main() {
    int mas[] = {2,5,-8,1,-4,6,3,-5,-9,13,0,4,9};
    int n = sizeof(mas)/sizeof(int);
    
    cout << "Исходный массив: ";
    for(int i = 0; i < n; i++) cout << mas[i] << " ";
    cout << endl;
    
    minMaxSort(mas, n);
    
    cout << "Отсортированный массив: ";
    for(int i = 0; i < n; i++) cout << mas[i] << " ";
    cout << endl;
    
    return 0;
}

void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                // Обмен элементов
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for(int j = low; j <= high-1; j++) {
        if(arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return (i+1);
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void customSort(int arr[], int n) {
    // Динамическое выделение памяти для массивов
    int* even = new int[n];
    int* odd = new int[n];
    int e = 0, o = 0;
    
    // Разделение на четные и нечетные
    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 == 0) even[e++] = arr[i];
        else odd[o++] = arr[i];
    }
    
    // Сортировка четных по возрастанию
    bubbleSort(even, e);
    
    // Сортировка нечетных по убыванию
    for(int i = 0; i < o-1; i++) {
        for(int j = 0; j < o-i-1; j++) {
            if(odd[j] < odd[j+1]) {
                int temp = odd[j];
                odd[j] = odd[j+1];
                odd[j+1] = temp;
            }
        }
    }
    
    // Сборка массива обратно
    int index = 0;
    for(int i = 0; i < e; i++) arr[index++] = even[i];
    for(int i = 0; i < o; i++) arr[index++] = odd[i];
    
    // Освобождение памяти
    delete[] even;
    delete[] odd;
}

void sortIntervalAsc(int arr[], int n, int N1, int N2) {
    if(N1 < 0 || N2 >= n || N1 > N2) return;
    
    // Используем сортировку пузырьком на интервале
    for(int i = N1; i <= N2; i++) {
        for(int j = N1; j < N2 - (i - N1); j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void sortIntervalDesc(int arr[], int n, int N1, int N2) {
    if(N1 < 0 || N2 >= n || N1 > N2) return;
    
    // Используем модифицированную сортировку пузырьком на интервале
    for(int i = N1; i <= N2; i++) {
        for(int j = N1; j < N2 - (i - N1); j++) {
            if(arr[j] < arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}