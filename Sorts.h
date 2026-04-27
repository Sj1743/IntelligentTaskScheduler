#ifndef SORTS_H
#define SORTS_H

#include "Task.h"
#include <vector>

class Sorts {
private:
    static int partition(std::vector<Task>& arr, int low, int high) {
        Task pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (sortCompare(arr[j], pivot)) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    static void quickSortHelper(std::vector<Task>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortHelper(arr, low, pi - 1);
            quickSortHelper(arr, pi + 1, high);
        }
    }

    static void heapify(std::vector<Task>& arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && sortCompare(arr[largest], arr[l])) largest = l;
        if (r < n && sortCompare(arr[largest], arr[r])) largest = r;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

public:
    static void insertionSort(std::vector<Task> arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            Task key = arr[i];
            int j = i - 1;
            while (j >= 0 && sortCompare(key, arr[j])) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
        std::cout << "--- Insertion Sort Results ---\n";
        for (const auto& t : arr) t.print();
    }

    static void quickSort(std::vector<Task> arr) {
        quickSortHelper(arr, 0, arr.size() - 1);
        std::cout << "--- Quick Sort Results ---\n";
        for (const auto& t : arr) t.print();
    }

    static void heapSort(std::vector<Task> arr) {
        int n = arr.size();
        for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
        std::cout << "--- Heap Sort Results ---\n";
        for (const auto& t : arr) t.print();
    }
};

#endif