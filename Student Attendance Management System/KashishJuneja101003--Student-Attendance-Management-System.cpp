#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

// Enum for Attendance Status
enum class AttendanceStatus { Present, Absent, Late };

// Convert Enum to String
string statusToString(AttendanceStatus status) {
    switch (status) {
        case AttendanceStatus::Present: return "Present";
        case AttendanceStatus::Absent: return "Absent";
        case AttendanceStatus::Late: return "Late";
        default: return "Unknown";
    }
}

// Student Class
class Student {
public:
    string name;
    int rollNumber;
    string className;
    vector<AttendanceStatus> attendanceRecord;

    Student(string n, int roll, string c) : name(std::move(n)), rollNumber(roll), className(std::move(c)) {}

    void markAttendance(AttendanceStatus status) {
        attendanceRecord.push_back(status);
    }

    void viewAttendance() const {
        cout << "\nAttendance record for " << name << " (Roll No: " << rollNumber << "):\n";
        if (attendanceRecord.empty()) {
            cout << "No attendance records available.\n";
        } else {
            for (const auto& status : attendanceRecord) {
                cout << "- " << statusToString(status) << endl;
            }
        }
    }
};

// Attendance System Class
class AttendanceSystem {
private:
    unordered_map<int, unique_ptr<Student>> students;

public:
    void addStudent(const string& name, int rollNumber, const string& className) {
        if (students.find(rollNumber) != students.end()) {
            cout << "Student with this roll number already exists!\n";
            return;
        }
        students[rollNumber] = make_unique<Student>(name, rollNumber, className);
        cout << "Student added successfully!\n";
    }

    void markAttendance(int rollNumber, AttendanceStatus status) {
        if (students.find(rollNumber) != students.end()) {
            students[rollNumber]->markAttendance(status);
            cout << "Attendance marked successfully!\n";
        } else {
            cout << "Student not found!\n";
        }
    }

    void viewAttendance(int rollNumber) const {
        if (students.find(rollNumber) != students.end()) {
            students.at(rollNumber)->viewAttendance();
        } else {
            cout << "Student not found!\n";
        }
    }

    void removeStudent(int rollNumber) {
        if (students.erase(rollNumber)) {
            cout << "Student removed successfully!\n";
        } else {
            cout << "Student not found!\n";
        }
    }

    void saveDataToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cerr << "Error opening file for writing!\n";
            return;
        }

        for (const auto& pair : students) {
            file << pair.second->rollNumber << "," << pair.second->name << "," << pair.second->className << "\n";
        }

        cout << "Data saved successfully!\n";
    }

    void loadDataFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file for reading!\n";
            return;
        }

        students.clear();
        string name, className;
        int rollNumber;

        while (file >> rollNumber) {
            file.ignore(); // Ignore comma
            getline(file, name, ',');
            getline(file, className);

            students[rollNumber] = make_unique<Student>(name, rollNumber, className);
        }

        cout << "Data loaded successfully!\n";
    }
};

// Function to Handle String Input
string getInputString(const string& prompt) {
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Properly handle leftover newlines
    string input;
    getline(cin, input);
    return input;
}

// Function to Get Attendance Status from User
AttendanceStatus getAttendanceStatus() {
    int statusInput;
    while (true) {
        cout << "Enter attendance status (1: Present, 2: Absent, 3: Late): ";
        cin >> statusInput;
        if (statusInput >= 1 && statusInput <= 3) {
            return static_cast<AttendanceStatus>(statusInput - 1);
        }
        cout << "Invalid input! Please enter a valid option.\n";
    }
}

// Main Function
int main() {
    AttendanceSystem system;
    system.loadDataFromFile("students.txt"); // Load saved data

    while (true) {
        cout << "\n----- Student Attendance Management System -----\n"
             << "1. Add Student\n"
             << "2. Mark Attendance\n"
             << "3. View Attendance\n"
             << "4. Remove Student\n"
             << "5. Save & Exit\n"
             << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name = getInputString("Enter student name: ");
                int rollNumber;
                cout << "Enter roll number: ";
                cin >> rollNumber;
                string className = getInputString("Enter class name: ");
                system.addStudent(name, rollNumber, className);
                break;
            }
            case 2: {
                int rollNumber;
                cout << "Enter roll number: ";
                cin >> rollNumber;
                AttendanceStatus status = getAttendanceStatus();
                system.markAttendance(rollNumber, status);
                break;
            }
            case 3: {
                int rollNumber;
                cout << "Enter roll number: ";
                cin >> rollNumber;
                system.viewAttendance(rollNumber);
                break;
            }
            case 4: {
                int rollNumber;
                cout << "Enter roll number: ";
                cin >> rollNumber;
                system.removeStudent(rollNumber);
                break;
            }
            case 5:
                system.saveDataToFile("students.txt");
                cout << "Exiting the system.\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
