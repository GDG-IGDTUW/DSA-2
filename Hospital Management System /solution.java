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
    Map<Integer, Integer> patientToDoctor = new HashMap<>();
    Map<Integer, Integer> patientToWard = new HashMap<>();
    Map<Integer, Integer> patientBill = new HashMap<>();
    Map<Integer, Integer> unservedPatients = new HashMap<>();

    // Internal tracking
    Map<Integer, Integer> doctorLoad = new HashMap<>();
    Map<Integer, Integer> wardOccupancy = new HashMap<>();

    Map<Integer, List<Integer>> doctorToPatients = new HashMap<>();

    public HospitalManagementSystem(
            List<List<Integer>> patients,
            List<List<Integer>> doctors,
            List<List<Integer>> wards
    ) {
        this.patients = patients;
        this.doctors = doctors;
        this.wards = wards;

        for (List<Integer> d : doctors) {
            doctorLoad.put(d.get(0), 0);
            doctorToPatients.put(d.get(0), new ArrayList<>());
        }

        for (List<Integer> w : wards) {
            wardOccupancy.put(w.get(0), 0);
        }
    }

    // 1️⃣ Admit patients based on priority
    public void admitPatients() {

        PriorityQueue<List<Integer>> pq = new PriorityQueue<>(
                (a, b) -> b.get(1) - a.get(1) // priority DESC
        );

        pq.addAll(patients);

        while (!pq.isEmpty()) {
            List<Integer> p = pq.poll();
            int patientId = p.get(0);
            int priority = p.get(1);

            boolean doctorAssigned = assignDoctor(patientId);
            if (!doctorAssigned) {
                unservedPatients.put(patientId, priority);
                continue;
            }

            boolean wardAssigned = allocateWard(patientId);
            if (!wardAssigned) {
                // rollback doctor
                int dId = patientToDoctor.get(patientId);
                doctorLoad.put(dId, doctorLoad.get(dId) - 1);
                doctorToPatients.get(dId).remove(Integer.valueOf(patientId));
                patientToDoctor.remove(patientId);

                unservedPatients.put(patientId, priority);
                continue;
            }

            calculateBill(patientId);
        }
    }

    // 2️⃣ Assign doctor with least number of patients
    public boolean assignDoctor(int patientId) {

        int diseaseId = -1;
        for (List<Integer> p : patients) {
            if (p.get(0) == patientId) {
                diseaseId = p.get(2);
                break;
            }
        }

        int chosenDoctor = -1;
        int minLoad = Integer.MAX_VALUE;

        for (List<Integer> d : doctors) {
            int doctorId = d.get(0);
            int docDisease = d.get(1);
            int maxPatients = d.get(2);

            if (docDisease == diseaseId &&
                    doctorLoad.get(doctorId) < maxPatients) {

                if (doctorLoad.get(doctorId) < minLoad) {
                    minLoad = doctorLoad.get(doctorId);
                    chosenDoctor = doctorId;
                }
            }
        }

        if (chosenDoctor == -1) return false;

        patientToDoctor.put(patientId, chosenDoctor);
        doctorLoad.put(chosenDoctor, doctorLoad.get(chosenDoctor) + 1);
        doctorToPatients.get(chosenDoctor).add(patientId);

        return true;
    }

    // 3️⃣ Allocate ward with least occupancy
    public boolean allocateWard(int patientId) {

        int chosenWard = -1;
        int minOcc = Integer.MAX_VALUE;

        for (List<Integer> w : wards) {
            int wardId = w.get(0);
            int maxCap = w.get(1);

            if (wardOccupancy.get(wardId) < maxCap) {
                if (wardOccupancy.get(wardId) < minOcc) {
                    minOcc = wardOccupancy.get(wardId);
                    chosenWard = wardId;
                }
            }
        }

        if (chosenWard == -1) return false;

        patientToWard.put(patientId, chosenWard);
        wardOccupancy.put(chosenWard, wardOccupancy.get(chosenWard) + 1);
        return true;
    }

    // 4️⃣ Calculate bill
    public void calculateBill(int patientId) {

        int days = 0;
        for (List<Integer> p : patients) {
            if (p.get(0) == patientId) {
                days = p.get(3);
                break;
            }
        }

        int wardId = patientToWard.get(patientId);
        int cost = 0;

        for (List<Integer> w : wards) {
            if (w.get(0) == wardId) {
                cost = w.get(2);
                break;
            }
        }

        patientBill.put(patientId, days * cost);
    }

    // 5️⃣ Get all patients treated by a doctor
    public List<Integer> getPatientsByDoctor(int doctorId) {
        return doctorToPatients.getOrDefault(doctorId, new ArrayList<>());
    }

    // 6️⃣ Get doctor assigned to a patient
    public Integer getDoctorByPatient(int patientId) {
        return patientToDoctor.get(patientId);
    }

    // 7️⃣ Track unserved patients
    public Map<Integer, Integer> getUnservedPatients() {
        return unservedPatients;
    }
}
