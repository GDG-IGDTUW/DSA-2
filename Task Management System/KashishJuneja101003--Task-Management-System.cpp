#include <iostream>
#include <set>
#include <unordered_map>
#include <memory>

using namespace std;

class TaskManager {
private:
    struct Task {
        int id, time, priority;

        bool operator<(const Task &other) const {
            if (priority == other.priority)
                return time < other.time;  // Earlier time comes first
            return priority > other.priority;  // Higher priority comes first
        }
    };

    set<Task> taskSet;  // Maintains tasks sorted by priority and time
    unordered_map<int, set<Task>::iterator> taskMap;  // Maps ID to task iterator

public:
    // Add a new task or update an existing task
    void addTask(int id, int time, int priority) {
        if (taskMap.find(id) != taskMap.end()) {
            taskSet.erase(taskMap[id]); // Remove old task if it exists
        }
        Task newTask = {id, time, priority};
        auto it = taskSet.insert(newTask).first;
        taskMap[id] = it;
    }

    // Get the highest-priority task
    int getHighestPriorityTask() {
        return taskSet.empty() ? -1 : taskSet.begin()->id;
    }

    // Remove a task by ID
    void removeTask(int id) {
        if (taskMap.find(id) != taskMap.end()) {
            taskSet.erase(taskMap[id]);
            taskMap.erase(id);
            cout << "Task " << id << " removed successfully.\n";
        } else {
            cout << "Task not found!\n";
        }
    }

    // Update the priority or time of an existing task
    void updateTask(int id, int newTime, int newPriority) {
        if (taskMap.find(id) == taskMap.end()) {
            cout << "Task not found!\n";
            return;
        }
        addTask(id, newTime, newPriority);
        cout << "Task " << id << " updated successfully.\n";
    }

    // Check if a task exists
    bool taskExists(int id) {
        return taskMap.find(id) != taskMap.end();
    }

    // Get details of a specific task
    void getTaskDetails(int id) {
        if (taskMap.find(id) == taskMap.end()) {
            cout << "Task not found!\n";
            return;
        }
        auto task = *taskMap[id];
        cout << "Task ID: " << task.id << ", Time: " << task.time << ", Priority: " << task.priority << endl;
    }

    // Display all tasks sorted by priority and time
    void listAllTasks() {
        if (taskSet.empty()) {
            cout << "No tasks available.\n";
            return;
        }
        cout << "\n--- Task List (Sorted by Priority & Time) ---\n";
        cout << "ID\tTime\tPriority\n";
        for (const Task &task : taskSet) {
            cout << task.id << "\t" << task.time << "\t" << task.priority << endl;
        }
    }

    // Clear all tasks
    void clearAllTasks() {
        taskSet.clear();
        taskMap.clear();
        cout << "All tasks removed.\n";
    }
};

// Function to handle user interaction
void handleUserInput(TaskManager &manager) {
    int q;
    cin >> q;
    while (q--) {
        int queryType;
        cin >> queryType;

        if (queryType == 1) {  // Add task
            int id, time, priority;
            cin >> id >> time >> priority;
            manager.addTask(id, time, priority);
        } else if (queryType == 2) {  // Get highest-priority task
            cout << "Highest Priority Task ID: " << manager.getHighestPriorityTask() << endl;
        } else if (queryType == 3) {  // Remove task
            int id;
            cin >> id;
            manager.removeTask(id);
        } else if (queryType == 4) {  // Update task
            int id, newTime, newPriority;
            cin >> id >> newTime >> newPriority;
            manager.updateTask(id, newTime, newPriority);
        } else if (queryType == 5) {  // Check task existence
            int id;
            cin >> id;
            cout << (manager.taskExists(id) ? "Task exists" : "Task does not exist") << endl;
        } else if (queryType == 6) {  // Get task details
            int id;
            cin >> id;
            manager.getTaskDetails(id);
        } else if (queryType == 7) {  // List all tasks
            manager.listAllTasks();
        } else if (queryType == 8) {  // Clear all tasks
            manager.clearAllTasks();
        } else {
            cout << "Invalid query type.\n";
        }
    }
}

int main() {
    TaskManager manager;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int id, time, priority;
        cin >> id >> time >> priority;
        manager.addTask(id, time, priority);
    }

    handleUserInput(manager);
    return 0;
}
