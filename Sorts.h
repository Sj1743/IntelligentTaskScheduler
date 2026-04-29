#ifndef SORTS_H
#define SORTS_H
#include "Task.h"
using namespace std;

class Sorts {
private:
    static void swapTasks(Task& a, Task& b) {
        Task temp = a;
        a = b;
        b = temp;
    }
    static int partition(Task arr[], int low, int high) {
        Task pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (sortCompare(arr[j], pivot)) {
                i++;
                swapTasks(arr[i], arr[j]);
            }
        }
        swapTasks(arr[i + 1], arr[high]);
        return (i + 1);
    }

    static void quickSortHelper(Task arr[], int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortHelper(arr, low, pi - 1);
            quickSortHelper(arr, pi + 1, high);
        }
    }

    static void heapify(Task arr[], int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && sortCompare(arr[largest], arr[l])) largest = l;
        if (r < n && sortCompare(arr[largest], arr[r])) largest = r;

        if (largest != i) {
            swapTasks(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
    static void copyArray(Task source[], Task dest[], int n) {
        for(int i = 0; i < n; i++) dest[i] = source[i];
    }

public:
    static void insertionSort(Task originalArr[], int n) {
        Task* arr = new Task[20000];
        copyArray(originalArr, arr, n);
        for (int i = 1; i < n; i++) {
            Task key = arr[i];
            int j = i - 1;
            while (j >= 0 && sortCompare(key, arr[j])) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
        cout << "--- Insertion Sort Results ---\n";
        for (int i = 0; i < n; i++) arr[i].print();
        delete[] arr;
    }

    static void quickSort(Task originalArr[], int n) {
        Task* arr = new Task[20000];
        copyArray(originalArr, arr, n);
        quickSortHelper(arr, 0, n - 1);
        cout << "--- Quick Sort Results ---\n";
        for (int i = 0; i < n; i++) arr[i].print();
        delete[] arr; 
    }

    static void heapSort(Task originalArr[], int n) {
        Task* arr = new Task[20000];
        copyArray(originalArr, arr, n);
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        for (int i = n - 1; i > 0; i--) {
            swapTasks(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
        cout << "--- Heap Sort Results ---\n";
        for (int i = 0; i < n; i++) arr[i].print();
        delete[] arr;
    }
};

#endif