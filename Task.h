#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>

struct Task {
    int taskID;
    std::string description;
    int priority;
    int deadline;
    
    // Default constructor
    Task() : taskID(0), description(""), priority(0), deadline(0) {}
    
    // Parameterized constructor
    Task(int id, const std::string& desc, int prio, int dead)
        : taskID(id), description(desc), priority(prio), deadline(dead) {}
    
    // For printing
    void print() const {
        std::cout << "TaskID: " << taskID 
                  << ", Priority: " << priority 
                  << ", Deadline: " << deadline 
                  << ", Desc: " << description << std::endl;
    }
};

// Comparison function for heap (priority first, then deadline, then taskID)
inline bool heapCompare(const Task& a, const Task& b) {
    if (a.priority != b.priority)
        return a.priority > b.priority; // higher priority first
    if (a.deadline != b.deadline)
        return a.deadline < b.deadline; // smaller deadline first
    return a.taskID < b.taskID; // smaller taskID first
}

// Comparison function for sorting (deadline first, then priority, then taskID)
inline bool sortCompare(const Task& a, const Task& b) {
    if (a.deadline != b.deadline)
        return a.deadline < b.deadline; // smaller deadline first
    if (a.priority != b.priority)
        return a.priority > b.priority; // higher priority first
    return a.taskID < b.taskID; // smaller taskID first
}

#endif
