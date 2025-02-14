import java.util.*;

// Class representing a student with attributes: name, roll number, class, and attendance record
class Student {
    String name;
    int rollNumber;
    String studentClass;
    List<String> attendance;

    public Student(String name, int rollNumber, String studentClass) {
        this.name = name;
        this.rollNumber = rollNumber;
        this.studentClass = studentClass;
        this.attendance = new ArrayList<>();
    }
}

public class SonamKumari29_StudentAttendanceMgmtSys {
    private static Map<Integer, Student> students = new HashMap<>();

    // Adds a new student to the system
    public static String addStudent(String name, int rollNumber, String studentClass) {
        if (students.containsKey(rollNumber)) {
            return "Error: Student with Roll No: " + rollNumber + " already exists in database";
        }
        students.put(rollNumber, new Student(name, rollNumber, studentClass));
        return "Student added: " + name + ", Roll No: " + rollNumber;
    }

    // Marks attendance for a student with the given roll number
    public static String markAttendance(int rollNumber, String status) {
        if (!students.containsKey(rollNumber)) {
            return "Error: Student with Roll No: " + rollNumber + " does not exist";
        }
        if (!status.equals("Present") && !status.equals("Absent") && !status.equals("Late")) {
            return "Error: Invalid attendance status";
        }
        students.get(rollNumber).attendance.add(status);
        return "Attendance marked for Roll No: " + rollNumber + " as " + status;
    }

    // Displays the attendance record of a student
    public static String viewAttendance(int rollNumber) {
        if (!students.containsKey(rollNumber)) {
            return "Error: Student with Roll No: " + rollNumber + " does not exist";
        }
        List<String> attendance = students.get(rollNumber).attendance;
        if (attendance.isEmpty()) {
            return "No attendance records found for Roll No: " + rollNumber;
        }
        StringBuilder record = new StringBuilder("Attendance record for Roll No: " + rollNumber + ":\n");
        for (int i = 0; i < attendance.size(); i++) {
            record.append(i + 1).append(". ").append(attendance.get(i)).append("\n");
        }
        return record.toString();
    }

    // Removes a student from the system
    public static String removeStudent(int rollNumber) {
        if (!students.containsKey(rollNumber)) {
            return "Error: Student with Roll No: " + rollNumber + " does not exist";
        }
        students.remove(rollNumber);
        return "Student with Roll No: " + rollNumber + " removed successfully";
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("Choose an operation: Add Student, Mark Attendance, View Attendance, Remove Student, Exit");
            String operation = scanner.nextLine();
            if (operation.equalsIgnoreCase("Exit")) {
                break;
            }
            switch (operation) {
                case "Add Student":
                    System.out.print("Name: ");
                    String name = scanner.nextLine();
                    System.out.print("Roll Number: ");
                    int rollNumber = Integer.parseInt(scanner.nextLine());
                    System.out.print("Class: ");
                    String studentClass = scanner.nextLine();
                    System.out.println(addStudent(name, rollNumber, studentClass));
                    break;
                case "Mark Attendance":
                    System.out.print("Roll Number: ");
                    rollNumber = Integer.parseInt(scanner.nextLine());
                    System.out.print("Status (Present/Absent/Late): ");
                    String status = scanner.nextLine();
                    System.out.println(markAttendance(rollNumber, status));
                    break;
                case "View Attendance":
                    System.out.print("Roll Number: ");
                    rollNumber = Integer.parseInt(scanner.nextLine());
                    System.out.println(viewAttendance(rollNumber));
                    break;
                case "Remove Student":
                    System.out.print("Roll Number: ");
                    rollNumber = Integer.parseInt(scanner.nextLine());
                    System.out.println(removeStudent(rollNumber));
                    break;
                default:
                    System.out.println("Invalid operation. Please try again.");
            }
        }
        scanner.close();
    }
}

