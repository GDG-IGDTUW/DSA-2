class CourseManager {

    // courseId -> set of prerequisite courseIds
    private Map<Long, Set<Long>> prereqMap;

    public CourseManager() {
        this.prereqMap = new HashMap<>();
    }

    // ADD COURSE operation
    public void addCourse(long courseId) {
        // Implement addCourse logic
        if(!prereqMap.containsKey(courseId))
            prereqMap.put(courseId, new HashSet<>());
    }

    // REMOVE COURSE operation
    public void removeCourse(long courseId) {
        // Implement removeCourse logic
        // have implemented lazy delete to improve efficiency, i.e, when this course is deleted from the system it will still be present as a 
        // prerequisite course for other courses (if any). This has been taken care of while fetching the prereq list of any course 
        // This improves efficiency because traversing over the entire hashmap will be more computionally expensive than over the corresponding hashset. 
        if(prereqMap.containsKey(courseId))
            prereqMap.remove(courseId);
    }

    // ADD PREREQUISITE operation
    public void addPrerequisite(long courseId, long prereqId) {
        // Implement addPrerequisite logic
        if(!prereqMap.containsKey(courseId) || !prereqMap.containsKey(prereqId))
            return; //both should exist
        if(courseId == prereqId)
            return; //a course cannot be a prereq of itself
        Set<Long> prereqs = prereqMap.get(courseId);
        prereqs.add(prereqId); //since it is a set, prereqs won't be added twice
        prereqMap.put(courseId, prereqs);
    }

    // REMOVE PREREQUISITE operation
    public void removePrerequisite(long courseId, long prereqId) {
        // Implement removePrerequisite logic
        if(!prereqMap.containsKey(courseId))
            return; //not a valid course
        if(!prereqMap.containsKey(prereqId))
            return; //this prereq does not exist
        Set<Long> prereqs = prereqMap.get(courseId);
        if(!prereqs.contains(prereqId))
            return; //this course does not have a prereq of prereqId
        prereqs.remove(prereqId);
        prereqMap.put(courseId, prereqs); //add the updated prereqs
    }

    // GET PREREQUISITES operation
    public List<Long> getPrerequisites(long courseId) {
        if (!prereqMap.containsKey(courseId))
            return new ArrayList<>(); //not a course in the system

        Set<Long> prereqs = prereqMap.get(courseId);
        prereqs.removeIf(id -> !prereqMap.containsKey(id)); //cleaning up dead entries; the prereqs which do not exist in system anymore, hence will not be included
        return new ArrayList<>(prereqs);
    }

    // GET ALL COURSES operation
    public List<Long> getAllCourses() {
        // Return all courseIds
        List<Long> allCourses = new ArrayList<>(prereqMap.keySet());
        return allCourses;
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
