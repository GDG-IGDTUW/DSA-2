Problem Statement

You are tasked with designing a Hospital Management System to manage patient admissions, doctor assignments, ward allocations, and billing efficiently.

The hospital receives patients with different priority levels and diseases. Doctors specialize in certain diseases and can handle a limited number of patients simultaneously. Wards have maximum capacities, and patients are charged based on their length of stay.

Your system must process patients in descending order of priority and allocate them to:

1.Doctors — each patient is assigned to a doctor who treats their disease and currently has the fewest assigned patients.

2.Wards — each patient is assigned to the ward with the least current occupancy that still has capacity.

If no doctor or no ward is available, the patient leaves without admission. The system should track such patients along with their priority in an unserved patient list.

Additionally, the system must be able to:

-Track all patients currently assigned to a doctor.

-Track the doctor assigned to a patient.

-Track billing for each admitted patient.

T-rack patients who could not be admitted.

Each requirement must be implemented as a separate function.

Functional Requirements

1.Admit Patient by Priority

2.Patients are admitted in descending order of priority.

3.Admission triggers doctor assignment and ward allocation.

4.Assign Doctor to Patient

5.Assign the patient to a doctor who treats their disease.

6.If multiple doctors can treat the disease, assign to the doctor with least number of current patients.

7.If no doctor is available, the patient leaves and is recorded in the unserved list.

8.Allocate Ward to Patient

9.Assign the patient to the ward with least current occupancy among wards with available capacity.

10.If no ward is available, the patient leaves and is recorded in the unserved list.


Each patient stays for a given number of days in a ward.

Each ward has a cost per night.

Patient bill = totalDays × costPerNight.


Input Format

Initial Data:

patients = [(patient_id, name, priority, disease, totalDays)]

doctors = [(doctor_id, name, [specializations], maxPatients)]

wards = [(ward_id, maxCapacity, costPerNight)]

Operations:

ADMIT_PATIENT(patient_id)
ASSIGN_DOCTOR(patient_id)
ALLOCATE_WARD(patient_id)
CALCULATE_ACCOUNT(patient_id) Calculate Patient Billing
TRACK_PATIENTS_BY_DOCTOR(doctor_id) For any doctor, list all patients currently being treated.
TRACK_DOCTOR_BY_PATIENT(patient_id) For any patient, return their assigned doctor.
TRACK_UNSERVED_PATIENTS() Maintain a list of all patients who could not be admitted due to lack of doctor or ward availability. For each, store their priority.

Example Input

Patients:

patients = [
    (101, "Alice", 5, "Cardiology", 3),
    (102, "Bob", 10, "Neurology", 2),
    (103, "Charlie", 7, "Cardiology", 4),
    (104, "David", 8, "Orthopedics", 5)
]


Doctors:

doctors = [
    (201, "Dr. Smith", ["Cardiology"], 1),
    (202, "Dr. Lee", ["Neurology"], 1),
    (203, "Dr. Patel", ["Orthopedics"], 1)
]


Wards:

wards = [
    (301, 2, 1000),
    (302, 1, 1500)
]

Example Dry Run
Step	Operation	Patient State / Doctor / Ward / Notes
1	ADMIT_PATIENT	Patients sorted by priority: Bob(10), David(8), Charlie(7), Alice(5)
2	ASSIGN_DOCTOR	Bob → Dr. Lee, David → Dr. Patel, Charlie → Dr. Smith, Alice → cannot assign doctor → leaves; unserved list: [Alice(5)]
3	ALLOCATE_WARD	Bob → 301 (1/2), David → 301 (2/2), Charlie → 302 (1/1), Alice already left
4	CALCULATE_ACCOUNT	Bob → 2×1000=2000, David → 5×1000=5000, Charlie → 4×1500=6000
5	TRACK_PATIENTS_BY_DOCTOR	Dr. Smith → [Charlie], Dr. Lee → [Bob], Dr. Patel → [David]
6	TRACK_DOCTOR_BY_PATIENT	Bob → Dr. Lee
7	TRACK_UNSERVED_PATIENTS	[Alice → 5]
Final Output
Ward Assignments:
301 → [Bob, David]
302 → [Charlie]

Doctor Assignments:
Dr. Smith → [Charlie]
Dr. Lee → [Bob]
Dr. Patel → [David]

Patient Accounts:
101 → N/A (not admitted)
102 → 2000
103 → 6000
104 → 5000

Unserved Patients:
Alice → 5

Constraints

1 ≤ Number of patients ≤ 100,000

1 ≤ Number of doctors ≤ 1,000

1 ≤ Number of wards ≤ 1,000

1 ≤ Patient priority ≤ 100

1 ≤ totalDays ≤ 100

Each doctor can treat up to maxPatients simultaneously.

Each ward has a maxCapacity.

All operations must be processed efficiently even for large inputs.

Edge Cases

Multiple patients with the same priority → admit in order of arrival

Patients with disease not treated by any doctor → automatically unserved

Load balancing: assign patient to doctor with fewest patients and ward with least occupancy

