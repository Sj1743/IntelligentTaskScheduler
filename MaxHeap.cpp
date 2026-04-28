#include "MaxHeap.h"

MaxHeap::MaxHeap() {
    heap = new Task[20000]; 
    heapSize = 0;
    enableLogging = true;
}

MaxHeap::~MaxHeap() {
    delete[] heap;
}

void MaxHeap::swapTasks(int i, int j) {
    Task temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void MaxHeap::heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heapCompare(heap[i], heap[parent])) {
            if (enableLogging) {
                cout << "HEAPIFY: swap index " << parent << " and " << i 
                     << " (taskID " << heap[parent].taskID << " <-> " << heap[i].taskID << ")\n";
            }
            swapTasks(i, parent);
            i = parent;
        } else break;
    }
}

void MaxHeap::heapifyDown(int i) {
    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < heapSize && heapCompare(heap[left], heap[largest])) {
            largest = left;
        }
        if (right < heapSize && heapCompare(heap[right], heap[largest])) {
            largest = right;
        }

        if (largest != i) {
            if (enableLogging) {
                cout << "HEAPIFY: swap index " << i << " and " << largest 
                     << " (taskID " << heap[i].taskID << " <-> " << heap[largest].taskID << ")\n";
            }
            swapTasks(i, largest);
            i = largest;
        } else break;
    }
}

void MaxHeap::insert(Task task) {
    if (heapSize >= 20000) return;
    heap[heapSize] = task;
    heapifyUp(heapSize);
    heapSize++;
}

Task MaxHeap::extractMax() {
    if (heapSize == 0) return Task();
    Task maxTask = heap[0];
    if (enableLogging) {
        cout << "EXTRACT MAX: " << maxTask.taskID << "\n";
    }
    heap[0] = heap[heapSize - 1];
    heapSize--;
    if (heapSize > 0) heapifyDown(0);
    return maxTask;
}

Task MaxHeap::peekMax() const {
    if (heapSize > 0) return heap[0];
    return Task();
}

void MaxHeap::buildHeap(Task arr[], int n) {
    for(int i = 0; i < n; i++) heap[i] = arr[i];
    heapSize = n;
    for (int i = (heapSize / 2) - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

bool MaxHeap::isEmpty() const { return heapSize == 0; }
void MaxHeap::setLogging(bool enable) { enableLogging = enable; }