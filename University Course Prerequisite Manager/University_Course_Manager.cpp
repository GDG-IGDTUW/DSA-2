#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class CourseManager {
private:
    // courseId -> set of prerequisites
    unordered_map<long long, unordered_set<long long>> prereqMap;

public:
    // Add a new course
    void addCourse(long long courseId) {
        if (prereqMap.find(courseId) == prereqMap.end()) {
            prereqMap[courseId] = {};
        }
    }

    // Remove a course completely
    void removeCourse(long long courseId) {
        if (prereqMap.find(courseId) == prereqMap.end()) return;

        // Remove course itself
        prereqMap.erase(courseId);

        // Remove it from other courses' prerequisite lists
        for (auto &pair : prereqMap) {
            pair.second.erase(courseId);
        }
    }

    // Add prerequisite
    void addPrerequisite(long long courseId, long long prereqId) {
        if (courseId == prereqId) return;

        if (prereqMap.find(courseId) == prereqMap.end()) return;
        if (prereqMap.find(prereqId) == prereqMap.end()) return;

        prereqMap[courseId].insert(prereqId);
    }

    // Remove prerequisite
    void removePrerequisite(long long courseId, long long prereqId) {
        if (prereqMap.find(courseId) == prereqMap.end()) return;

        prereqMap[courseId].erase(prereqId);
    }

    // Get prerequisites of a course
    vector<long long> getPrerequisites(long long courseId) {
        vector<long long> result;

        if (prereqMap.find(courseId) == prereqMap.end()) return result;

        for (long long prereq : prereqMap[courseId]) {
            result.push_back(prereq);
        }

        return result;
    }

    // Get all courses
    vector<long long> getAllCourses() {
        vector<long long> courses;

        for (auto &pair : prereqMap) {
            courses.push_back(pair.first);
        }

        return courses;
    }
};

// Utility to print vector in required format
void printList(const vector<long long>& v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size()) cout << ", ";
    }
    cout << "]\n";
}

int main() {
    CourseManager manager;

    manager.addCourse(101);
    manager.addCourse(102);
    manager.addPrerequisite(102, 101);

    printList(manager.getPrerequisites(102));
    printList(manager.getAllCourses());

    return 0;
}
