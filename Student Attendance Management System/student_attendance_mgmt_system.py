class AttendanceManagementSystem:
  # Defining dictionary to store student IDs (Acts as th database) 
  def __init__(self):
        self.attendance = {}

    # To add a new student to the attendance system
    def add_student(self, student_id, name):
        if student_id in self.attendance:
            print("Student ID already exists.")
            return
        self.attendance[student_id] = (name, 0)
        print(f"Student '{name}' added successfully.")

    # Marking attendance for an existing student
    def mark_attendance(self, student_id):
        if student_id not in self.attendance:
            print("-1")  # Student not found
            return
        name, count = self.attendance[student_id]
        self.attendance[student_id] = (name, count + 1)
        print(f"Attendance marked for '{name}'. Total: {count + 1}")

    # To show attendance records status
    def display_attendance(self):
        if not self.attendance:
            print("No students available.")
            return
        for student_id, (name, count) in self.attendance.items():
            print(f"ID: {student_id}, Name: {name}, Attendance Count: {count}")

    # Removing a student from the attendance system
    def remove_student(self, student_id):
        if student_id not in self.attendance:
            print("-1")  # Student not found
            return
        name, _ = self.attendance.pop(student_id)
        print(f"Student '{name}' removed successfully.")


def main():
    attendance_system = AttendanceManagementSystem()
    
    while True:
        # Display menu options
        print("\n1. Add Student\n2. Mark Attendance\n3. Display Attendance\n4. Remove Student\n5. Exit")
        choice = input("Enter choice: ")
        
        if choice == "5":
            break  # Exit the program
        
        if choice == "1":
            # Adding a new student
            student_id = input("Enter student ID: ")
            name = input("Enter student name: ")
            attendance_system.add_student(student_id, name)
        
        elif choice == "2":
            # Marking attendance for a student
            student_id = input("Enter student ID: ")
            attendance_system.mark_attendance(student_id)
        
        elif choice == "3":
            # Display all attendance records
            attendance_system.display_attendance()
        
        elif choice == "4":
            # Removing a student
            student_id = input("Enter student ID: ")
            attendance_system.remove_student(student_id)
        
        else:
            print("Invalid choice.")

## Entry point in program
if __name__ == "__main__":
    main()
