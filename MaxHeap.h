#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "Task.h"
using namespace std;

class MaxHeap {
private:
    Task* heap;
    int heapSize;
    bool enableLogging;
    
    void swapTasks(int i, int j);
    void heapifyDown(int i);
    void heapifyUp(int i);

public:
    MaxHeap();
    ~MaxHeap();
    void insert(Task task);
    Task extractMax();
    Task peekMax() const;
    void buildHeap(Task arr[], int n);
    bool isEmpty() const;
    void setLogging(bool enable);
};

#endif