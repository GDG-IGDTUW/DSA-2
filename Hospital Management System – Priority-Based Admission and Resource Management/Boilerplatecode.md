## JAVA

java
import java.util.*;


class HospitalManagementSystem {

    // Input data
    // patients: [patientId, priority, diseaseId, totalDays]
    // doctors : [doctorId, diseaseId, maxPatients]
    // wards   : [wardId, maxCapacity, costPerNight]

    List<List<Integer>> patients;
    List<List<Integer>> doctors;
    List<List<Integer>> wards;

    // System tracking
    Map<Integer, Integer> patientToDoctor;
    Map<Integer, Integer> patientToWard;
    Map<Integer, Integer> patientBill;
    Map<Integer, Integer> unservedPatients; // patientId -> priority

    public HospitalManagementSystem(
            List<List<Integer>> patients,
            List<List<Integer>> doctors,
            List<List<Integer>> wards
    ) {
        this.patients = patients;
        this.doctors = doctors;
        this.wards = wards;

        patientToDoctor = new HashMap<>();
        patientToWard = new HashMap<>();
        patientBill = new HashMap<>();
        unservedPatients = new HashMap<>();
    }

    // Admit patients based on priority
    public void admitPatients() {
        // TODO
    }

    // Assign doctor with least number of patients
    public void assignDoctor(int patientId) {
        // TODO
    }

    // Allocate ward with least occupancy
    public void allocateWard(int patientId) {
        // TODO
    }

    // Calculate bill for a patient
    public void calculateBill(int patientId) {
        // TODO
    }

    // Get all patients treated by a doctor
    public List<Integer> getPatientsByDoctor(int doctorId) {
        return new ArrayList<>();
    }

    // Get doctor assigned to a patient
    public Integer getDoctorByPatient(int patientId) {
        return null;
    }

    // Track patients who could not be admitted
    public Map<Integer, Integer> getUnservedPatients() {
        return unservedPatients;
    }
}

## Python
class HospitalManagementSystem:
    
    patients: [patient_id, priority, disease_id, total_days]
    doctors : [doctor_id, disease_id, max_patients]
    wards   : [ward_id, max_capacity, cost_per_night]
    

    def __init__(self, patients, doctors, wards):
        self.patients = patients
        self.doctors = doctors
        self.wards = wards

        self.patient_to_doctor = {}
        self.patient_to_ward = {}
        self.patient_bill = {}
        self.unserved_patients = {}

    # Admit patients based on priority
    def admit_patients(self):
        # TODO
        pass

    # Assign doctor with least number of patients
    def assign_doctor(self, patient_id):
        # TODO
        pass

    # Allocate ward with least occupancy
    def allocate_ward(self, patient_id):
        # TODO
        pass

    # Calculate bill for patient
    def calculate_bill(self, patient_id):
        # TODO
        pass

    # Get all patients treated by a doctor
    def get_patients_by_doctor(self, doctor_id):
        return []

    # Get doctor assigned to a patient
    def get_doctor_by_patient(self, patient_id):
        return None

    # Track patients who could not be admitted
    def get_unserved_patients(self):
        return self.unserved_patients

## C++

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class HospitalManagementSystem {
private:
    // patients: [patientId, priority, diseaseId, totalDays]
    // doctors : [doctorId, diseaseId, maxPatients]
    // wards   : [wardId, maxCapacity, costPerNight]

    vector<vector<int>> patients;
    vector<vector<int>> doctors;
    vector<vector<int>> wards;

    unordered_map<int, int> patientToDoctor;
    unordered_map<int, int> patientToWard;
    unordered_map<int, int> patientBill;
    unordered_map<int, int> unservedPatients;

public:
    HospitalManagementSystem(
        vector<vector<int>> patients,
        vector<vector<int>> doctors,
        vector<vector<int>> wards
    ) {
        this->patients = patients;
        this->doctors = doctors;
        this->wards = wards;
    }

    // Admit patients based on priority
    void admitPatients() {
        // TODO
    }

    // Assign doctor with least number of patients
    void assignDoctor(int patientId) {
        // TODO
    }

    // Allocate ward with least occupancy
    void allocateWard(int patientId) {
        // TODO
    }

    // Calculate bill for patient
    void calculateBill(int patientId) {
        // TODO
    }

    // Get patients treated by a doctor
    vector<int> getPatientsByDoctor(int doctorId) {
        return {};
    }

    // Get doctor assigned to a patient
    int getDoctorByPatient(int patientId) {
        return -1;
    }

    // Track unserved patients
    unordered_map<int, int> getUnservedPatients() {
        return unservedPatients;
    }
};

int main() {
    return 0;
}





