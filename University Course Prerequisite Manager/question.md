Design a University Course Prerequisite Manager

Problem Statement

Design and implement a data structure for a University Course Prerequisite Manager that supports adding courses, removing courses, adding prerequisites, removing prerequisites, and retrieving prerequisite information efficiently.

Each course has a unique courseId and a set of prerequisite course IDs.

The system should efficiently manage courses and their prerequisites while maintaining correct prerequisite relationships at all times.

You are required to design the prerequisite manager and implement the required operations.

Operations

Implement the following functions:

addCourse(courseId)

Adds a new course to the system.
If the course already exists, do nothing.

removeCourse(courseId)

Removes the course completely from the system.
Also removes this course from the prerequisite lists of all other courses.
If the course does not exist, do nothing.

addPrerequisite(courseId, prereqId)

Adds prereqId as a prerequisite for courseId.
Both courses must exist.
If the prerequisite already exists, do nothing.
A course cannot be a prerequisite of itself.

removePrerequisite(courseId, prereqId)

Removes prereqId from the prerequisite list of courseId.
If either course does not exist, or the prerequisite does not exist, do nothing.

getPrerequisites(courseId)

Returns a list of all prerequisite course IDs for the given course.
If the course does not exist, return an empty list.
The order of prerequisites does not matter.

getAllCourses()

Returns a list of all course IDs currently in the system.
The order does not matter.

Input Format

The first line contains an integer Q, the number of operations.

The next Q lines each contain an operation in one of the following formats:

addCourse courseId
removeCourse courseId
addPrerequisite courseId prereqId
removePrerequisite courseId prereqId
getPrerequisites courseId
getAllCourses

Output Format

For every getPrerequisites operation, output a list of course IDs.
For every getAllCourses operation, output a list of all courses.

Output format:
[courseId1, courseId2, ...]

Examples

Example 1

INPUT
8
addCourse 101
addCourse 102
addCourse 103
addPrerequisite 103 101
addPrerequisite 103 102
getPrerequisites 103
removeCourse 101
getPrerequisites 103

OUTPUT
[101, 102]
[102]

Explanation

Courses 101, 102, and 103 are added.
Course 103 requires 101 and 102 as prerequisites.
Course 101 is removed.
Course 101 is also removed from the prerequisite list of course 103.

Example 2

INPUT
6
addCourse 201
addCourse 202
addPrerequisite 202 201
removePrerequisite 202 201
getPrerequisites 202
getAllCourses

OUTPUT
[]
[201, 202]

Constraints

1 ≤ Q ≤ 100000
1 ≤ courseId ≤ 1000000000
A course can have at most 100000 prerequisites.
All operations should be handled efficiently.

Notes

The solution should support fast lookup, insertion, and deletion.
Duplicate prerequisites should not be stored.
Self-dependencies are not allowed.
This problem tests understanding of hash-based data structures, graph-like relationships, and edge-case handling.
