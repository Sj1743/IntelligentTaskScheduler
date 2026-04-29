#ifndef TASK_H
#define TASK_H
#include <string>
#include <iostream>
using namespace std;

struct Task {
    int taskID;
    string description;
    int priority;
    int deadline;

    Task() {
        taskID = 0;
        description = "";
        priority = 0;
        deadline = 0;
    }

    Task(int id, string desc, int prio, int dead) {
        taskID = id;
        description = desc;
        priority = prio;
        deadline = dead;
    }
    
    void print() const {
        cout << "TaskID: " << taskID 
             << ", Priority: " << priority 
             << ", Deadline: " << deadline 
             << ", Desc: " << description << "\n";
    }
};

inline bool heapCompare(const Task& a, const Task& b) {
    if (a.priority != b.priority) return a.priority > b.priority;
    if (a.deadline != b.deadline) return a.deadline < b.deadline;
    return a.taskID < b.taskID;
}

inline bool sortCompare(const Task& a, const Task& b) {
    if (a.deadline != b.deadline) return a.deadline < b.deadline;
    if (a.priority != b.priority) return a.priority > b.priority;
    return a.taskID < b.taskID;
}

#endif