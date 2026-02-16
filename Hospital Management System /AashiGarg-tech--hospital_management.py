from collections import defaultdict
import heapq


class HospitalManagementSystem:

    def __init__(self, patients, doctors, wards):
        self.patients = {}
        for pid, name, priority, disease, days in patients:
            self.patients[pid] = {
                "name": name,
                "priority": priority,
                "disease": disease,
                "days": days
            }

        self.doctors = {}
        self.doctor_patients = defaultdict(list)

        for did, name, specs, maxp in doctors:
            self.doctors[did] = {
                "name": name,
                "specs": set(specs),
                "max": maxp
            }

        self.wards = {}
        self.ward_patients = defaultdict(list)

        for wid, cap, cost in wards:
            self.wards[wid] = {
                "cap": cap,
                "cost": cost
            }

        self.patient_to_doctor = {}
        self.patient_to_ward = {}
        self.patient_bill = {}
        self.unserved_patients = {}

    def admit_patients(self):
        order = sorted(self.patients.keys(),
                       key=lambda p: -self.patients[p]["priority"])

        for pid in order:

            if not self.assign_doctor(pid):
                self.unserved_patients[pid] = self.patients[pid]["priority"]
                continue

            if not self.allocate_ward(pid):
                self.unserved_patients[pid] = self.patients[pid]["priority"]
                self.doctor_patients[self.patient_to_doctor[pid]].remove(pid)
                del self.patient_to_doctor[pid]
                continue

            self.calculate_bill(pid)

    def assign_doctor(self, patient_id):
        disease = self.patients[patient_id]["disease"]

        candidates = []

        for did, info in self.doctors.items():
            if disease in info["specs"] and len(self.doctor_patients[did]) < info["max"]:
                heapq.heappush(candidates, (len(self.doctor_patients[did]), did))

        if not candidates:
            return False

        _, chosen = heapq.heappop(candidates)

        self.patient_to_doctor[patient_id] = chosen
        self.doctor_patients[chosen].append(patient_id)
        return True

    def allocate_ward(self, patient_id):
        candidates = []

        for wid, info in self.wards.items():
            if len(self.ward_patients[wid]) < info["cap"]:
                heapq.heappush(candidates, (len(self.ward_patients[wid]), wid))

        if not candidates:
            return False

        _, chosen = heapq.heappop(candidates)

        self.patient_to_ward[patient_id] = chosen
        self.ward_patients[chosen].append(patient_id)
        return True

    def calculate_bill(self, patient_id):
        ward = self.patient_to_ward[patient_id]
        days = self.patients[patient_id]["days"]
        cost = self.wards[ward]["cost"]
        self.patient_bill[patient_id] = days * cost

    def get_patients_by_doctor(self, doctor_id):
        return self.doctor_patients[doctor_id]

    def get_doctor_by_patient(self, patient_id):
        return self.patient_to_doctor.get(patient_id)

    def get_unserved_patients(self):
        return self.unserved_patients


# EXECUTION EXAMPLE

patients = [
    (101, "Alice", 5, "Cardiology", 3),
    (102, "Bob", 10, "Neurology", 2),
    (103, "Charlie", 7, "Cardiology", 4),
    (104, "David", 8, "Orthopedics", 5)
]

doctors = [
    (201, "Dr. Smith", ["Cardiology"], 1),
    (202, "Dr. Lee", ["Neurology"], 1),
    (203, "Dr. Patel", ["Orthopedics"], 1)
]

wards = [
    (301, 2, 1000),
    (302, 1, 1500)
]

system = HospitalManagementSystem(patients, doctors, wards)

system.admit_patients()

print("\nWard Assignments:")
for wid, plist in system.ward_patients.items():
    print(wid, "->", plist)

print("\nDoctor Assignments:")
for did, plist in system.doctor_patients.items():
    print(did, "->", plist)

print("\nPatient Bills:")
for pid, bill in system.patient_bill.items():
    print(pid, "->", bill)

print("\nUnserved Patients:")
print(system.get_unserved_patients())
