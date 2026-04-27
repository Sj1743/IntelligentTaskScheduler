#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "Task.h"
#include <vector>
#include <iostream>

class MaxHeap {
private:
    std::vector<Task> heap;
    bool enableLogging;
    
    void heapifyDown(int i);
    void heapifyUp(int i);

public:
    MaxHeap() : enableLogging(true) {}
    void insert(const Task& task);
    Task extractMax();
    Task peekMax() const;
    void buildHeap(const std::vector<Task>& tasks);
    bool isEmpty() const;
    void setLogging(bool enable);
};

#endif