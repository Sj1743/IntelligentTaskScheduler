#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include "Task.h"
#include "AVLTree.h"
#include "RedBlackTree.h"
#include "TwoThreeTree.h"
#include "MaxHeap.h"
#include "Sorts.h"

void runFixedTestSequence(AVLTree& avl, RedBlackTree& rbt, TwoThreeTree& tt, MaxHeap& heap, std::vector<Task>& masterList) {
    std::cout << "\n=== RUNNING FIXED TEST SEQUENCE ===\n";
    
    std::vector<Task> fixedTasks = {
        Task(45, "Task45", 80, 5), Task(25, "Task25", 60, 10),
        Task(55, "Task55", 90, 3), Task(15, "Task15", 70, 8),
        Task(35, "Task35", 50, 12), Task(65, "Task65", 95, 2),
        Task(5, "Task5", 75, 7)
    };

    for (const auto& task : fixedTasks) {
        avl.insert(task);
        rbt.insert(task);
        tt.insert(task);
        heap.insert(task);
        masterList.push_back(task);
    }

    avl.deleteTask(25);
    heap.extractMax();
    heap.extractMax();
}

void runPerformanceBenchmark(AVLTree& avl, RedBlackTree& rbt, TwoThreeTree& tt) {
    std::cout << "\n=== RUNNING PERFORMANCE BENCHMARK (10,000 insertions) ===\n";
    
    // Disable logging for benchmarking per instructions
    avl.setLogging(false);
    rbt.setLogging(false);
    tt.setLogging(false);
    
    srand(2026); // Set specific seed

    // Generate 10,000 random tasks
    std::vector<Task> randomTasks;
    for (int i = 0; i < 10000; ++i) {
        // Random taskID between 1 and 1000000
        int id = rand() % 1000000 + 1; 
        randomTasks.push_back(Task(id, "RandomTask", rand() % 100 + 1, rand() % 365 + 1));
    }

    // Benchmark AVL Tree
    auto startAVL = std::chrono::high_resolution_clock::now();
    for (const auto& t : randomTasks) avl.insert(t);
    auto endAVL = std::chrono::high_resolution_clock::now();
    auto durationAVL = std::chrono::duration_cast<std::chrono::milliseconds>(endAVL - startAVL).count();

    // Benchmark Red-Black Tree
    auto startRBT = std::chrono::high_resolution_clock::now();
    for (const auto& t : randomTasks) rbt.insert(t);
    auto endRBT = std::chrono::high_resolution_clock::now();
    auto durationRBT = std::chrono::duration_cast<std::chrono::milliseconds>(endRBT - startRBT).count();

    // Benchmark 2-3 Tree
    auto startTT = std::chrono::high_resolution_clock::now();
    for (const auto& t : randomTasks) tt.insert(t);
    auto endTT = std::chrono::high_resolution_clock::now();
    auto durationTT = std::chrono::duration_cast<std::chrono::milliseconds>(endTT - startTT).count();

    std::cout << "AVL Tree Insertion Time: " << durationAVL << " ms\n";
    std::cout << "Red-Black Tree Insertion Time: " << durationRBT << " ms\n";
    std::cout << "2-3 Tree Insertion Time: " << durationTT << " ms\n";

    // Re-enable logging
    avl.setLogging(true);
    rbt.setLogging(true);
    tt.setLogging(true);
}

int main() {
    AVLTree avl;
    RedBlackTree rbt;
    TwoThreeTree tt;
    MaxHeap heap;
    std::vector<Task> masterList;

    int choice;
    do {
        std::cout << "\n--- Intelligent Task Scheduler Menu ---\n";
        std::cout << "1. Insert a Task\n";
        std::cout << "2. Delete Task from AVL\n";
        std::cout << "3. Search for a Task\n";
        std::cout << "4. Print Trees\n";
        std::cout << "5. Extract Max (Heap)\n";
        std::cout << "6. Run Sorting Algorithms\n";
        std::cout << "7. Run Fixed Test Sequence\n";
        std::cout << "8. Run Performance Benchmark\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int id, prio, dead;
            std::string desc;
            std::cout << "ID: "; std::cin >> id;
            std::cout << "Priority: "; std::cin >> prio;
            std::cout << "Deadline: "; std::cin >> dead;
            std::cout << "Desc: "; std::cin >> desc;
            Task t(id, desc, prio, dead);
            avl.insert(t); rbt.insert(t); tt.insert(t); heap.insert(t); masterList.push_back(t);
        } else if (choice == 2) {
            int id;
            std::cout << "Enter ID to delete: "; std::cin >> id;
            avl.deleteTask(id);
        } else if (choice == 3) {
            int id;
            std::cout << "Enter ID to search: "; std::cin >> id;
            Task* t = avl.search(id);
            if(t) t->print();
            else std::cout << "Not found.\n";
        } else if (choice == 4) {
            avl.prettyPrint(); rbt.prettyPrint(); tt.prettyPrint();
        } else if (choice == 5) {
            heap.extractMax();
        } else if (choice == 6) {
            Sorts::insertionSort(masterList);
            Sorts::quickSort(masterList);
            Sorts::heapSort(masterList);
        } else if (choice == 7) {
            runFixedTestSequence(avl, rbt, tt, heap, masterList);
        } else if (choice == 8) {
            runPerformanceBenchmark(avl, rbt, tt);
        }

    } while (choice != 9);

    return 0;
}