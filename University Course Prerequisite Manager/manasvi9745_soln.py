class CourseManager:
    def __init__(self):
        # courseId -> set of prerequisite courseIds
        self.prereq_map = {}

    # ADD COURSE operation
    def addCourse(self, courseId):
        # If course doesn't exist, create empty prerequisite set
        if courseId not in self.prereq_map:
            self.prereq_map[courseId] = set()

    # REMOVE COURSE operation
    def removeCourse(self, courseId):
        # If course doesn't exist, do nothing
        if courseId not in self.prereq_map:
            return
        
        # Remove this course from all other courses' prerequisite sets
        for cid in self.prereq_map:
            if courseId in self.prereq_map[cid]:
                self.prereq_map[cid].remove(courseId)
        
        # Remove the course itself
        del self.prereq_map[courseId]

    # ADD PREREQUISITE operation
    def addPrerequisite(self, courseId, prereqId):
        # Both courses must exist
        if (courseId not in self.prereq_map or 
            prereqId not in self.prereq_map):
            return
        
        # Self-dependency not allowed
        if courseId == prereqId:
            return
        
        # Add prerequisite (set prevents duplicates)
        self.prereq_map[courseId].add(prereqId)

    # REMOVE PREREQUISITE operation
    def removePrerequisite(self, courseId, prereqId):
        # Both courses must exist
        if (courseId not in self.prereq_map or 
            prereqId not in self.prereq_map):
            return
        
        # Remove prerequisite if present
        self.prereq_map[courseId].discard(prereqId)

    # GET PREREQUISITES operation
    def getPrerequisites(self, courseId):
        if courseId not in self.prereq_map:
            return []
        return list(self.prereq_map[courseId])

    # GET ALL COURSES operation
    def getAllCourses(self):
        return list(self.prereq_map.keys())


# -------------------------
# Example Usage
# -------------------------
if __name__ == "__main__":
    manager = CourseManager()

    manager.addCourse(101)
    manager.addCourse(102)
    manager.addCourse(103)

    manager.addPrerequisite(103, 101)
    manager.addPrerequisite(103, 102)

    print(manager.getPrerequisites(103))  # [101, 102]
    
    manager.removeCourse(101)

    print(manager.getPrerequisites(103))  # [102]
    print(manager.getAllCourses())        # [102, 103]
