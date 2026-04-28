#include <iostream>
#include <chrono>
#include <cstdlib>
#include "Task.h"
#include "AVLTree.h"
#include "RedBlackTree.h"
#include "TwoThreeTree.h"
#include "MaxHeap.h"
#include "Sorts.h"

using namespace std;

void runFixedTestSequence(AVLTree& avl, RedBlackTree& rbt, TwoThreeTree& tt, MaxHeap& heap, Task masterList[], int& masterCount) {
    cout << "\n=== RUNNING FIXED TEST SEQUENCE ===\n";
    
    Task fixedTasks[7];
    fixedTasks[0] = Task(45, "Task45", 80, 5);
    fixedTasks[1] = Task(25, "Task25", 60, 10);
    fixedTasks[2] = Task(55, "Task55", 90, 3);
    fixedTasks[3] = Task(15, "Task15", 70, 8);
    fixedTasks[4] = Task(35, "Task35", 50, 12);
    fixedTasks[5] = Task(65, "Task65", 95, 2);
    fixedTasks[6] = Task(5, "Task5", 75, 7);

    for (int i = 0; i < 7; i++) {
        avl.insert(fixedTasks[i]);
        rbt.insert(fixedTasks[i]);
        tt.insert(fixedTasks[i]);
        heap.insert(fixedTasks[i]);
        masterList[masterCount] = fixedTasks[i];
        masterCount++;
    }

    avl.deleteTask(25);
    heap.extractMax();
    heap.extractMax();
}

void runPerformanceBenchmark(AVLTree& avl, RedBlackTree& rbt, TwoThreeTree& tt) {
    cout << "\n=== RUNNING PERFORMANCE BENCHMARK (10,000 insertions) ===\n";
    
    avl.setLogging(false);
    rbt.setLogging(false);
    tt.setLogging(false);
    
    srand(2026);

    Task* randomTasks = new Task[10000];

    for (int i = 0; i < 10000; i++) {
        int id = rand() % 1000000 + 1; 
        randomTasks[i] = Task(id, "RandomTask", rand() % 100 + 1, rand() % 365 + 1);
    }

    auto startAVL = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) avl.insert(randomTasks[i]);
    auto endAVL = chrono::high_resolution_clock::now();
    auto durationAVL = chrono::duration_cast<chrono::milliseconds>(endAVL - startAVL).count();

    auto startRBT = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) rbt.insert(randomTasks[i]);
    auto endRBT = chrono::high_resolution_clock::now();
    auto durationRBT = chrono::duration_cast<chrono::milliseconds>(endRBT - startRBT).count();

    auto startTT = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) tt.insert(randomTasks[i]);
    auto endTT = chrono::high_resolution_clock::now();
    auto durationTT = chrono::duration_cast<chrono::milliseconds>(endTT - startTT).count();

    cout << "AVL Tree Insertion Time: " << durationAVL << " ms\n";
    cout << "Red-Black Tree Insertion Time: " << durationRBT << " ms\n";
    cout << "2-3 Tree Insertion Time: " << durationTT << " ms\n";

    avl.setLogging(true);
    rbt.setLogging(true);
    tt.setLogging(true);

    delete[] randomTasks;

int main() {
    AVLTree avl;
    RedBlackTree rbt;
    TwoThreeTree tt;
    MaxHeap heap;
    
    Task* masterList = new Task[20000]; 
    int masterCount = 0;

    int choice;
    do {
        cout << "\n--- Intelligent Task Scheduler Menu ---\n";
        cout << "1. Insert a Task\n";
        cout << "2. Delete Task from AVL\n";
        cout << "3. Search for a Task\n";
        cout << "4. Print Trees\n";
        cout << "5. Extract Max (Heap)\n";
        cout << "6. Run Sorting Algorithms\n";
        cout << "7. Run Fixed Test Sequence\n";
        cout << "8. Run Performance Benchmark\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, prio, dead;
            string desc;
            cout << "ID: "; cin >> id;
            cout << "Priority: "; cin >> prio;
            cout << "Deadline: "; cin >> dead;
            cout << "Desc: "; cin >> desc;
            Task t(id, desc, prio, dead);
            avl.insert(t); rbt.insert(t); tt.insert(t); heap.insert(t); 
            masterList[masterCount] = t;
            masterCount++;
        } else if (choice == 2) {
            int id;
            cout << "Enter ID to delete: "; cin >> id;
            avl.deleteTask(id);
        } else if (choice == 3) {
            int id;
            cout << "Enter ID to search: "; cin >> id;
            Task* t = avl.search(id);
            if(t != NULL) t->print();
            else cout << "Not found.\n";
        } else if (choice == 4) {
            avl.prettyPrint(); rbt.prettyPrint(); tt.prettyPrint();
        } else if (choice == 5) {
            heap.extractMax();
        } else if (choice == 6) {
            Sorts::insertionSort(masterList, masterCount);
            Sorts::quickSort(masterList, masterCount);
            Sorts::heapSort(masterList, masterCount);
        } else if (choice == 7) {
            runFixedTestSequence(avl, rbt, tt, heap, masterList, masterCount);
        } else if (choice == 8) {
            runPerformanceBenchmark(avl, rbt, tt);
        }

    } while (choice != 9);

    delete[] masterList;
    return 0;
}