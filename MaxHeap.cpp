#include "MaxHeap.h"

void MaxHeap::heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heapCompare(heap[i], heap[parent])) {
            if (enableLogging) {
                std::cout << "HEAPIFY: swap index " << parent << " and " << i 
                          << " (taskID " << heap[parent].taskID << " <-> " << heap[i].taskID << ")" << std::endl;
            }
            std::swap(heap[i], heap[parent]);
            i = parent;
        } else break;
    }
}

void MaxHeap::heapifyDown(int i) {
    int size = heap.size();
    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < size && heapCompare(heap[left], heap[largest])) {
            largest = left;
        }
        if (right < size && heapCompare(heap[right], heap[largest])) {
            largest = right;
        }

        if (largest != i) {
            if (enableLogging) {
                std::cout << "HEAPIFY: swap index " << i << " and " << largest 
                          << " (taskID " << heap[i].taskID << " <-> " << heap[largest].taskID << ")" << std::endl;
            }
            std::swap(heap[i], heap[largest]);
            i = largest;
        } else break;
    }
}

void MaxHeap::insert(const Task& task) {
    heap.push_back(task);
    heapifyUp(heap.size() - 1);
}

Task MaxHeap::extractMax() {
    if (heap.empty()) return Task();
    Task maxTask = heap[0];
    if (enableLogging) {
        std::cout << "EXTRACT MAX: " << maxTask.taskID << std::endl;
    }
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) heapifyDown(0);
    return maxTask;
}

Task MaxHeap::peekMax() const {
    if (!heap.empty()) return heap[0];
    return Task();
}

void MaxHeap::buildHeap(const std::vector<Task>& tasks) {
    heap = tasks;
    for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

bool MaxHeap::isEmpty() const { return heap.empty(); }
void MaxHeap::setLogging(bool enable) { enableLogging = enable; }