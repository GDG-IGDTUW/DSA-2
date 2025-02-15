class TaskManagementSystem:
    def __init__(self):
        self.tasks = {}  # task_id -> (title, description, status)

    def add_task(self, task_id, title, description):
        if task_id in self.tasks:
            print("Task ID already exists.")
            return
        self.tasks[task_id] = (title, description, "Pending")
        print(f"Task '{title}' added successfully.")

    def update_task(self, task_id, status):
        if task_id not in self.tasks:
            print("-1")  # Task does not exist
            return
        title, description, _ = self.tasks[task_id]
        self.tasks[task_id] = (title, description, status)
        print(f"Task '{title}' updated to status '{status}'.")

    def delete_task(self, task_id):
        if task_id not in self.tasks:
            print("-1")  # Task does not exist
            return
        title, _, _ = self.tasks.pop(task_id)
        print(f"Task '{title}' deleted successfully.")

    def display_tasks(self):
        if not self.tasks:
            print("No tasks available.")
            return
        for task_id, (title, description, status) in self.tasks.items():
            print(f"ID: {task_id}, Title: {title}, Description: {description}, Status: {status}")


def main():
    task_manager = TaskManagementSystem()
    
    while True:
        print("\n1. Add Task\n2. Update Task\n3. Delete Task\n4. Display Tasks\n5. Exit")
        choice = input("Enter choice: ")
        
        if choice == "5":
            break
        
        if choice == "1":
            task_id = input("Enter task ID: ")
            title = input("Enter task title: ")
            description = input("Enter task description: ")
            task_manager.add_task(task_id, title, description)
        
        elif choice == "2":
            task_id = input("Enter task ID: ")
            status = input("Enter new status: ")
            task_manager.update_task(task_id, status)
        
        elif choice == "3":
            task_id = input("Enter task ID: ")
            task_manager.delete_task(task_id)
        
        elif choice == "4":
            task_manager.display_tasks()
        
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()
