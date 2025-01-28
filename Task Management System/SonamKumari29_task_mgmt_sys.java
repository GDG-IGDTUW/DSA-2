import java.util.*;

class SonamKumari29_task_mgmt_sys {

    // Inner class to represent a Task
    private class Task {
        int id;
        int time;
        int priority;

        Task(int id, int time, int priority) {
            this.id = id;
            this.time = time;
            this.priority = priority;
        }
    }

    // PriorityQueue to store tasks, ordered by priority and then by time
    private PriorityQueue<Task> taskQueue;

    // HashMap to map task_id to its task object
    private Map<Integer, Task> taskMap;

    // Constructor to initialize the task manager
    public SonamKumari29_task_mgmt_sys() {
        // PriorityQueue sorts tasks first by priority (descending), then by time (ascending)
        taskQueue = new PriorityQueue<>((a, b) -> {
            if (a.priority == b.priority) {
                return Integer.compare(a.time, b.time); // If same priority, pick the task with shorter time
            }
            return Integer.compare(b.priority, a.priority); // Higher priority comes first
        });
        taskMap = new HashMap<>();
    }

    // Method to add a task
    public void addTask(int id, int time, int priority) {
        Task newTask = new Task(id, time, priority);
        taskQueue.offer(newTask);  // Add task to the priority queue
        taskMap.put(id, newTask);  // Map the task_id to the task object
    }

    // Method to get the task with the highest priority
    public int getHighestPriorityTask() {
        if (taskQueue.isEmpty()) {
            return -1;  // Return -1 if there are no tasks
        }
        return taskQueue.peek().id;  // Return the ID of the task with the highest priority
    }

    // Method to remove a task by id
    public void removeTask(int id) {
        Task taskToRemove = taskMap.remove(id);  // Remove from map
        if (taskToRemove != null) {
            taskQueue.remove(taskToRemove);  // Remove from priority queue
        }
    }

    // Main method to run the task manager system
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        SonamKumari29_task_mgmt_sys manager = new SonamKumari29_task_mgmt_sys();

        int n = scanner.nextInt();
        for (int i = 0; i < n; ++i) {
            int id = scanner.nextInt();
            int time = scanner.nextInt();
            int priority = scanner.nextInt();
            manager.addTask(id, time, priority);
        }

        int q = scanner.nextInt();
        while (q-- > 0) {
            int queryType = scanner.nextInt();
            if (queryType == 1) {
                int id = scanner.nextInt();
                int time = scanner.nextInt();
                int priority = scanner.nextInt();
                manager.addTask(id, time, priority);
            } else if (queryType == 2) {
                System.out.println(manager.getHighestPriorityTask());
            } else if (queryType == 3) {
                int id = scanner.nextInt();
                manager.removeTask(id);
            }
        }

        scanner.close();
    }
}
