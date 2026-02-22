import java.util.*;

class HospitalManagementSystem {

    List<List<Integer>> patients;
    List<List<Integer>> doctors;
    List<List<Integer>> wards;

    Map<Integer, Integer> patientToDoctor = new HashMap<>();
    Map<Integer, Integer> patientToWard = new HashMap<>();
    Map<Integer, Integer> patientBill = new HashMap<>();
    Map<Integer, Integer> unservedPatients = new HashMap<>();

    Map<Integer, Integer> doctorLoad = new HashMap<>();
    Map<Integer, Integer> wardOccupancy = new HashMap<>();
    Map<Integer, Integer> wardCost = new HashMap<>();
    Map<Integer, Integer> doctorCapacity = new HashMap<>();
    Map<Integer, Integer> doctorDisease = new HashMap<>();

    Map<Integer, List<Integer>> doctorToPatients = new HashMap<>();
    Map<Integer, List<Integer>> diseaseToDoctors = new HashMap<>();

    Map<Integer, Integer> patientDisease = new HashMap<>();
    Map<Integer, Integer> patientDays = new HashMap<>();

    public HospitalManagementSystem(
            List<List<Integer>> patients,
            List<List<Integer>> doctors,
            List<List<Integer>> wards
    ) {
        this.patients = patients;
        this.doctors = doctors;
        this.wards = wards;

        for (List<Integer> doc : doctors) {
            int id = doc.get(0);
            int disease = doc.get(1);
            int max = doc.get(2);

            doctorCapacity.put(id, max);
            doctorLoad.put(id, 0);
            doctorDisease.put(id, disease);
            doctorToPatients.put(id, new ArrayList<>());

            diseaseToDoctors.computeIfAbsent(disease, k -> new ArrayList<>()).add(id);
        }

        for (List<Integer> ward : wards) {
            wardOccupancy.put(ward.get(0), 0);
            wardCost.put(ward.get(0), ward.get(2));
        }

        for (List<Integer> p : patients) {
            patientDisease.put(p.get(0), p.get(2));
            patientDays.put(p.get(0), p.get(3));
        }
    }

    public void admitPatients() {
        patients.sort((a, b) -> {
            if (!b.get(1).equals(a.get(1)))
                return b.get(1) - a.get(1);
            return 0;
        });

        for (List<Integer> p : patients) {
            int patientId = p.get(0);
            assignDoctor(patientId);
            if (!unservedPatients.containsKey(patientId))
                allocateWard(patientId);
        }
    }

    public void assignDoctor(int patientId) {
        int disease = patientDisease.get(patientId);
        List<Integer> possibleDoctors = diseaseToDoctors.get(disease);

        if (possibleDoctors == null) {
            unservedPatients.put(patientId, getPriority(patientId));
            return;
        }

        int selectedDoctor = -1;
        int minLoad = Integer.MAX_VALUE;

        for (int docId : possibleDoctors) {
            if (doctorLoad.get(docId) < doctorCapacity.get(docId)
                    && doctorLoad.get(docId) < minLoad) {
                minLoad = doctorLoad.get(docId);
                selectedDoctor = docId;
            }
        }

        if (selectedDoctor == -1) {
            unservedPatients.put(patientId, getPriority(patientId));
            return;
        }

        patientToDoctor.put(patientId, selectedDoctor);
        doctorLoad.put(selectedDoctor, doctorLoad.get(selectedDoctor) + 1);
        doctorToPatients.get(selectedDoctor).add(patientId);
    }

    public void allocateWard(int patientId) {

        int selectedWard = -1;
        int minOcc = Integer.MAX_VALUE;

        for (List<Integer> ward : wards) {
            int id = ward.get(0);
            int cap = ward.get(1);
            int occ = wardOccupancy.get(id);

            if (occ < cap && occ < minOcc) {
                minOcc = occ;
                selectedWard = id;
            }
        }

        if (selectedWard == -1) {
            unservedPatients.put(patientId, getPriority(patientId));
            int docId = patientToDoctor.get(patientId);
            doctorLoad.put(docId, doctorLoad.get(docId) - 1);
            doctorToPatients.get(docId).remove((Integer) patientId);
            patientToDoctor.remove(patientId);
            return;
        }

        patientToWard.put(patientId, selectedWard);
        wardOccupancy.put(selectedWard, wardOccupancy.get(selectedWard) + 1);
        calculateBill(patientId);
    }

    public void calculateBill(int patientId) {
        int wardId = patientToWard.get(patientId);
        int days = patientDays.get(patientId);
        int cost = wardCost.get(wardId);
        patientBill.put(patientId, days * cost);
    }

    public List<Integer> getPatientsByDoctor(int doctorId) {
        return doctorToPatients.getOrDefault(doctorId, new ArrayList<>());
    }

    public Integer getDoctorByPatient(int patientId) {
        return patientToDoctor.get(patientId);
    }

    public Map<Integer, Integer> getUnservedPatients() {
        return unservedPatients;
    }

    private int getPriority(int patientId) {
        for (List<Integer> p : patients)
            if (p.get(0) == patientId)
                return p.get(1);
        return 0;
    }
}
