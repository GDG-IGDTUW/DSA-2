## C++
```C++

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class CourseManager {
private:
    // courseId -> set of prerequisite courseIds
    unordered_map<long long, unordered_set<long long>> prereqMap;

public:
    CourseManager() {}

    // ADD COURSE operation
    void addCourse(long long courseId) {
        // Implement addCourse logic
    }

    // REMOVE COURSE operation
    void removeCourse(long long courseId) {
        // Implement removeCourse logic
    }

    // ADD PREREQUISITE operation
    void addPrerequisite(long long courseId, long long prereqId) {
        // Implement addPrerequisite logic
    }

    // REMOVE PREREQUISITE operation
    void removePrerequisite(long long courseId, long long prereqId) {
        // Implement removePrerequisite logic
    }

    // GET PREREQUISITES operation
    vector<long long> getPrerequisites(long long courseId) {
        // Return prerequisite list
        return {};
    }

    // GET ALL COURSES operation
    vector<long long> getAllCourses() {
        // Return all courseIds
        return {};
    }
};

int main() {
    CourseManager manager;

    manager.addCourse(101);
    manager.addCourse(102);
    manager.addPrerequisite(102, 101);

    manager.getPrerequisites(102);
    manager.getAllCourses();

    return 0;
}
```
## JAVA

```java
import java.util.*;

class CourseManager {

    // courseId -> set of prerequisite courseIds
    private Map<Long, Set<Long>> prereqMap;

    public CourseManager() {
        this.prereqMap = new HashMap<>();
    }

    // ADD COURSE operation
    public void addCourse(long courseId) {
        // Implement addCourse logic
    }

    // REMOVE COURSE operation
    public void removeCourse(long courseId) {
        // Implement removeCourse logic
    }

    // ADD PREREQUISITE operation
    public void addPrerequisite(long courseId, long prereqId) {
        // Implement addPrerequisite logic
    }

    // REMOVE PREREQUISITE operation
    public void removePrerequisite(long courseId, long prereqId) {
        // Implement removePrerequisite logic
    }

    // GET PREREQUISITES operation
    public List<Long> getPrerequisites(long courseId) {
        // Return prerequisite list
        return new ArrayList<>();
    }

    // GET ALL COURSES operation
    public List<Long> getAllCourses() {
        // Return all courseIds
        return new ArrayList<>();
    }

    public static void main(String[] args) {
        CourseManager manager = new CourseManager();

        manager.addCourse(101);
        manager.addCourse(102);
        manager.addPrerequisite(102, 101);

        System.out.println(manager.getPrerequisites(102));
        System.out.println(manager.getAllCourses());
    }
}
```
## Python
```python

class CourseManager:
    def __init__(self):
        # courseId -> set of prerequisite courseIds
        self.prereq_map = {}

    # ADD COURSE operation
    def addCourse(self, courseId):
        # Implement addCourse logic
        pass

    # REMOVE COURSE operation
    def removeCourse(self, courseId):
        # Implement removeCourse logic
        pass

    # ADD PREREQUISITE operation
    def addPrerequisite(self, courseId, prereqId):
        # Implement addPrerequisite logic
        pass

    # REMOVE PREREQUISITE operation
    def removePrerequisite(self, courseId, prereqId):
        # Implement removePrerequisite logic
        pass

    # GET PREREQUISITES operation
    def getPrerequisites(self, courseId):
        # Return prerequisite list
        return []

    # GET ALL COURSES operation
    def getAllCourses(self):
        # Return all courseIds
        return []


# Example Usage
if __name__ == "__main__":
    manager = CourseManager()

    manager.addCourse(101)
    manager.addCourse(102)
    manager.addPrerequisite(102, 101)

    print(manager.getPrerequisites(102))
    print(manager.getAllCourses())
```
