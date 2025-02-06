import java.util.*;

public class SonamKumari29_ParkingLotMgmtSys {

    static class VehicleInfo {
        int spot;
        double entryTime;
        String type;

        public VehicleInfo(int spot, double entryTime, String type) {
            this.spot = spot;
            this.entryTime = entryTime;
            this.type = type;
        }
    }

    static class RemoveResult {
        int fee;
        String vehicleType;
        int spot;

        public RemoveResult(int fee, String vehicleType, int spot) {
            this.fee = fee;
            this.vehicleType = vehicleType;
            this.spot = spot;
        }
    }

    private Stack<Integer> availableSpots = new Stack<>();
    private Map<String, VehicleInfo> parkedVehicles = new HashMap<>();

    public void init(int totalSpots) {
        // Push spots in reverse order so that the highest spot is allocated first
        for (int i = 1; i <= totalSpots; i++) {
            availableSpots.push(i);
        }
    }

    public int park(String vehicleType, String licensePlate, double entryTime) {
        if (parkedVehicles.containsKey(licensePlate) || availableSpots.isEmpty()) {
            return -1;
        }
        int spot = availableSpots.pop();
        parkedVehicles.put(licensePlate, new VehicleInfo(spot, entryTime, vehicleType));
        return spot;
    }

    public RemoveResult remove(String licensePlate, double exitTime) {
        if (!parkedVehicles.containsKey(licensePlate)) {
            return null;
        }
        VehicleInfo info = parkedVehicles.get(licensePlate);
        parkedVehicles.remove(licensePlate);
        availableSpots.push(info.spot);
        double duration = exitTime - info.entryTime;
        int hours = (int) Math.ceil(duration);
        int fee = hours * 20;
        return new RemoveResult(fee, info.type, info.spot);
    }

    public static void main(String[] args) {
        SonamKumari29_ParkingLotMgmtSys sys = new SonamKumari29_ParkingLotMgmtSys();
        Scanner scanner = new Scanner(System.in);

        // Parse parking lot capacity
        String parkingLotLine = scanner.nextLine().trim();
        int totalSpots = Integer.parseInt(parkingLotLine.replaceAll("[^0-9]", ""));
        sys.init(totalSpots);

        // Process each operation
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (line.isEmpty()) {
                continue;
            }

            String[] parts = line.split("\\s+");
            String operation = parts[0];

            if (operation.equals("park")) {
                String vehicleType = parts[1];
                String licensePlate = parts[2];
                double entryTime = Double.parseDouble(parts[3]);

                int spot = sys.park(vehicleType, licensePlate, entryTime);
                if (spot == -1) {
                    System.out.println("Output: -1");
                } else {
                    System.out.println("Spot " + spot + " allocated to " + vehicleType + " " + licensePlate);
                }
            } else if (operation.equals("remove")) {
                String licensePlate = parts[1];
                double exitTime = Double.parseDouble(parts[2]);

                RemoveResult result = sys.remove(licensePlate, exitTime);
                if (result == null) {
                    System.out.println("Output: -1");
                } else {
                    System.out.println(result.vehicleType + " " + licensePlate + " removed from Spot " + result.spot + ". Parking fee: ₹" + result.fee);
                }
            }
        }
        scanner.close();
    }
}