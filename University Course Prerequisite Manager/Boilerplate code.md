## C++
```C++

#include <bits/stdc++.h>
using namespace std;

class CourseManager {
private:
    unordered_map<long long, unordered_set<long long>> prereqMap;

public:
    void addCourse(long long courseId) {
        prereqMap[courseId]; // creates empty set if not exists
    }

    void removeCourse(long long courseId) {
        prereqMap.erase(courseId);
        for (auto &p : prereqMap) {
            p.second.erase(courseId);
        }
    }

    void addPrerequisite(long long courseId, long long prereqId) {
        prereqMap[courseId].insert(prereqId);
        prereqMap[prereqId]; // ensure prereq course exists
    }

    void removePrerequisite(long long courseId, long long prereqId) {
        if (prereqMap.count(courseId)) {
            prereqMap[courseId].erase(prereqId);
        }
    }

    vector<long long> getPrerequisites(long long courseId) {
        vector<long long> res;
        if (prereqMap.count(courseId)) {
            for (auto x : prereqMap[courseId])
                res.push_back(x);
        }
        sort(res.begin(), res.end());
        return res;
    }

    vector<long long> getAllCourses() {
        vector<long long> res;
        for (auto &p : prereqMap)
            res.push_back(p.first);
        sort(res.begin(), res.end());
        return res;
    }
};

## JAVA

```java
import java.util.*;

class CourseManager {
    private Map<Long, Set<Long>> prereqMap = new HashMap<>();

    public void addCourse(long courseId) {
        prereqMap.putIfAbsent(courseId, new HashSet<>());
    }

    public void removeCourse(long courseId) {
        prereqMap.remove(courseId);
        for (Set<Long> prereqs : prereqMap.values()) {
            prereqs.remove(courseId);
        }
    }

    public void addPrerequisite(long courseId, long prereqId) {
        prereqMap.putIfAbsent(courseId, new HashSet<>());
        prereqMap.putIfAbsent(prereqId, new HashSet<>());
        prereqMap.get(courseId).add(prereqId);
    }

    public void removePrerequisite(long courseId, long prereqId) {
        if (prereqMap.containsKey(courseId)) {
            prereqMap.get(courseId).remove(prereqId);
        }
    }

    public List<Long> getPrerequisites(long courseId) {
        List<Long> res = new ArrayList<>();
        if (prereqMap.containsKey(courseId)) {
            res.addAll(prereqMap.get(courseId));
        }
        Collections.sort(res);
        return res;
    }

    public List<Long> getAllCourses() {
        List<Long> res = new ArrayList<>(prereqMap.keySet());
        Collections.sort(res);
        return res;
    }
}

## Python
```python

class CourseManager:
    def __init__(self):
        self.prereq_map = {}

    def addCourse(self, courseId):
        if courseId not in self.prereq_map:
            self.prereq_map[courseId] = set()

    def removeCourse(self, courseId):
        self.prereq_map.pop(courseId, None)
        for prereqs in self.prereq_map.values():
            prereqs.discard(courseId)

    def addPrerequisite(self, courseId, prereqId):
        self.prereq_map.setdefault(courseId, set()).add(prereqId)
        self.prereq_map.setdefault(prereqId, set())

    def removePrerequisite(self, courseId, prereqId):
        if courseId in self.prereq_map:
            self.prereq_map[courseId].discard(prereqId)

    def getPrerequisites(self, courseId):
        return sorted(self.prereq_map.get(courseId, []))

    def getAllCourses(self):
        return sorted(self.prereq_map.keys())


