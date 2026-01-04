C++ Boilerplate code
#include <bits/stdc++.h>
using namespace std;

class CourseManager {
private:
    // courseId -> set of prerequisite courseIds
    unordered_map<long long, unordered_set<long long>> prereqMap;

public:
    void addCourse(long long courseId) {
        // TODO: Implement
    }

    void removeCourse(long long courseId) {
        // TODO: Implement
    }

    void addPrerequisite(long long courseId, long long prereqId) {
        // TODO: Implement
    }

    void removePrerequisite(long long courseId, long long prereqId) {
        // TODO: Implement
    }

    vector<long long> getPrerequisites(long long courseId) {
        // TODO: Implement
        return {};
    }

    vector<long long> getAllCourses() {
        // TODO: Implement
        return {};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    CourseManager manager;

    while (Q--) {
        string op;
        cin >> op;

        if (op == "addCourse") {
            long long courseId;
            cin >> courseId;
            manager.addCourse(courseId);
        }
        else if (op == "removeCourse") {
            long long courseId;
            cin >> courseId;
            manager.removeCourse(courseId);
        }
        else if (op == "addPrerequisite") {
            long long courseId, prereqId;
            cin >> courseId >> prereqId;
            manager.addPrerequisite(courseId, prereqId);
        }
        else if (op == "removePrerequisite") {
            long long courseId, prereqId;
            cin >> courseId >> prereqId;
            manager.removePrerequisite(courseId, prereqId);
        }
        else if (op == "getPrerequisites") {
            long long courseId;
            cin >> courseId;
            auto res = manager.getPrerequisites(courseId);

            cout << "[";
            for (int i = 0; i < res.size(); i++) {
                cout << res[i];
                if (i + 1 < res.size()) cout << ", ";
            }
            cout << "]\n";
        }
        else if (op == "getAllCourses") {
            auto res = manager.getAllCourses();

            cout << "[";
            for (int i = 0; i < res.size(); i++) {
                cout << res[i];
                if (i + 1 < res.size()) cout << ", ";
            }
            cout << "]\n";
        }
    }

    return 0;
}
Java Boilerplate code
import java.util.*;

class CourseManager {
    // courseId -> set of prerequisite courseIds
    private Map<Long, Set<Long>> prereqMap = new HashMap<>();

    public void addCourse(long courseId) {
        // TODO: Implement
    }

    public void removeCourse(long courseId) {
        // TODO: Implement
    }

    public void addPrerequisite(long courseId, long prereqId) {
        // TODO: Implement
    }

    public void removePrerequisite(long courseId, long prereqId) {
        // TODO: Implement
    }

    public List<Long> getPrerequisites(long courseId) {
        // TODO: Implement
        return new ArrayList<>();
    }

    public List<Long> getAllCourses() {
        // TODO: Implement
        return new ArrayList<>();
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int Q = sc.nextInt();

        CourseManager manager = new CourseManager();

        while (Q-- > 0) {
            String op = sc.next();

            switch (op) {
                case "addCourse":
                    manager.addCourse(sc.nextLong());
                    break;

                case "removeCourse":
                    manager.removeCourse(sc.nextLong());
                    break;

                case "addPrerequisite":
                    manager.addPrerequisite(sc.nextLong(), sc.nextLong());
                    break;

                case "removePrerequisite":
                    manager.removePrerequisite(sc.nextLong(), sc.nextLong());
                    break;

                case "getPrerequisites": {
                    long courseId = sc.nextLong();
                    List<Long> res = manager.getPrerequisites(courseId);
                    System.out.println(res);
                    break;
                }

                case "getAllCourses": {
                    List<Long> res = manager.getAllCourses();
                    System.out.println(res);
                    break;
                }
            }
        }
        sc.close();
    }
}
Python Boilerplate code
class CourseManager:
    def __init__(self):
        # courseId -> set of prerequisite courseIds
        self.prereq_map = {}

    def addCourse(self, courseId):
        # TODO: Implement
        pass

    def removeCourse(self, courseId):
        # TODO: Implement
        pass

    def addPrerequisite(self, courseId, prereqId):
        # TODO: Implement
        pass

    def removePrerequisite(self, courseId, prereqId):
        # TODO: Implement
        pass

    def getPrerequisites(self, courseId):
        # TODO: Implement
        return []

    def getAllCourses(self):
        # TODO: Implement
        return []


def main():
    import sys
    input = sys.stdin.read
    data = input().split()

    Q = int(data[0])
    idx = 1

    manager = CourseManager()

    for _ in range(Q):
        op = data[idx]
        idx += 1

        if op == "addCourse":
            courseId = int(data[idx])
            idx += 1
            manager.addCourse(courseId)

        elif op == "removeCourse":
            courseId = int(data[idx])
            idx += 1
            manager.removeCourse(courseId)

        elif op == "addPrerequisite":
            courseId = int(data[idx])
            prereqId = int(data[idx + 1])
            idx += 2
            manager.addPrerequisite(courseId, prereqId)

        elif op == "removePrerequisite":
            courseId = int(data[idx])
            prereqId = int(data[idx + 1])
            idx += 2
            manager.removePrerequisite(courseId, prereqId)

        elif op == "getPrerequisites":
            courseId = int(data[idx])
            idx += 1
            print(manager.getPrerequisites(courseId))

        elif op == "getAllCourses":
            print(manager.getAllCourses())


if __name__ == "__main__":
    main()
