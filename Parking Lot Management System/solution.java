import java.util.*;

public class ParkingLotSystem {

    enum VehicleType {
        BIKE, CAR, TRUCK, ELECTRIC
    }

    enum ParkingSpotType {
        COMPACT, REGULAR, LARGE, ELECTRIC_CHARGING
    }

    static class Vehicle {
        String licenseNumber;
        VehicleType type;

        Vehicle(String licenseNumber, VehicleType type) {
            this.licenseNumber = licenseNumber;
            this.type = type;
        }

        VehicleType getType() {
            return type;
        }
    }

    static class ParkingSpot {
        String spotId;
        ParkingSpotType type;
        boolean occupied;

        ParkingSpot(String spotId, ParkingSpotType type) {
            this.spotId = spotId;
            this.type = type;
            this.occupied = false;
        }

        boolean isAvailable() {
            return !occupied;
        }

        void occupy() {
            occupied = true;
        }

        void release() {
            occupied = false;
        }
    }

    static class ParkingFloor {
        int floorNumber;
        List<ParkingSpot> spots = new ArrayList<>();

        ParkingFloor(int floorNumber) {
            this.floorNumber = floorNumber;
        }

        void addSpot(ParkingSpot spot) {
            spots.add(spot);
        }

        ParkingSpot getAvailableSpot(ParkingSpotType type) {
            for (ParkingSpot spot : spots) {
                if (spot.type == type && spot.isAvailable()) {
                    return spot;
                }
            }
            return null;
        }
    }

    static class Ticket {
        String ticketId;
        ParkingSpot spot;
        long entryTime;
        long exitTime;

        Ticket(String ticketId, ParkingSpot spot) {
            this.ticketId = ticketId;
            this.spot = spot;
            this.entryTime = System.currentTimeMillis();
        }

        void closeTicket() {
            this.exitTime = System.currentTimeMillis();
        }
    }

    static class FeeCalculator {

        static double calculateFee(long entryTime, long exitTime) {
            long durationMillis = exitTime - entryTime;
            long hours = (long) Math.ceil(durationMillis / (1000.0 * 60 * 60));

            if (hours <= 1) return 50;
            return 50 + (hours - 1) * 30;
        }
    }

    static class PaymentService {

        void processPayment(double amount) {
            System.out.println("Payment of ₹" + amount + " processed successfully.");
        }
    }

    static class ParkingLot {
        List<ParkingFloor> floors = new ArrayList<>();
        Map<String, Ticket> activeTickets = new HashMap<>();
        int ticketCounter = 1000;

        void addFloor(ParkingFloor floor) {
            floors.add(floor);
        }

        Ticket parkVehicle(Vehicle vehicle) {
            ParkingSpotType requiredType = mapVehicleToSpot(vehicle.getType());

            for (ParkingFloor floor : floors) {
                ParkingSpot spot = floor.getAvailableSpot(requiredType);
                if (spot != null) {
                    spot.occupy();
                    String ticketId = String.valueOf(++ticketCounter);
                    Ticket ticket = new Ticket(ticketId, spot);
                    activeTickets.put(ticketId, ticket);
                    return ticket;
                }
            }
            return null;
        }

        ParkingSpotType mapVehicleToSpot(VehicleType type) {
            switch (type) {
                case BIKE:
                    return ParkingSpotType.COMPACT;
                case CAR:
                    return ParkingSpotType.REGULAR;
                case TRUCK:
                    return ParkingSpotType.LARGE;
                case ELECTRIC:
                    return ParkingSpotType.ELECTRIC_CHARGING;
                default:
                    return ParkingSpotType.REGULAR;
            }
        }

        Ticket getTicket(String ticketId) {
            return activeTickets.get(ticketId);
        }

        void removeTicket(String ticketId) {
            activeTickets.remove(ticketId);
        }
    }

    static class EntryPanel {
        ParkingLot parkingLot;

        EntryPanel(ParkingLot parkingLot) {
            this.parkingLot = parkingLot;
        }

        Ticket enterVehicle(Vehicle vehicle) {
            return parkingLot.parkVehicle(vehicle);
        }
    }

    static class ExitPanel {
        ParkingLot parkingLot;
        PaymentService paymentService = new PaymentService();

        ExitPanel(ParkingLot parkingLot) {
            this.parkingLot = parkingLot;
        }

        void exitVehicle(String ticketId) {
            Ticket ticket = parkingLot.getTicket(ticketId);
            if (ticket == null) {
                System.out.println("Invalid Ticket");
                return;
            }

            ticket.closeTicket();
            double fee = FeeCalculator.calculateFee(ticket.entryTime, ticket.exitTime);
            paymentService.processPayment(fee);
            ticket.spot.release();
            parkingLot.removeTicket(ticketId);
        }
    }

    public static void main(String[] args) {

        ParkingLot parkingLot = new ParkingLot();

        ParkingFloor floor1 = new ParkingFloor(1);
        ParkingFloor floor2 = new ParkingFloor(2);

        floor1.addSpot(new ParkingSpot("F1-C1", ParkingSpotType.COMPACT));
        floor1.addSpot(new ParkingSpot("F1-R1", ParkingSpotType.REGULAR));
        floor1.addSpot(new ParkingSpot("F1-E1", ParkingSpotType.ELECTRIC_CHARGING));

        floor2.addSpot(new ParkingSpot("F2-R1", ParkingSpotType.REGULAR));
        floor2.addSpot(new ParkingSpot("F2-L1", ParkingSpotType.LARGE));

        parkingLot.addFloor(floor1);
        parkingLot.addFloor(floor2);

        EntryPanel entryPanel = new EntryPanel(parkingLot);
        ExitPanel exitPanel = new ExitPanel(parkingLot);

        Vehicle vehicle = new Vehicle("DL-01-AB-1234", VehicleType.CAR);

        Ticket ticket = entryPanel.enterVehicle(vehicle);

        if (ticket == null) {
            System.out.println("Parking Lot Full");
            return;
        }

        System.out.println("Vehicle entered parking lot");
        System.out.println("Ticket ID: " + ticket.ticketId);
        System.out.println("Assigned Spot: " + ticket.spot.spotId);

        exitPanel.exitVehicle(ticket.ticketId);
        System.out.println("Vehicle exited parking lot");
    }
}
