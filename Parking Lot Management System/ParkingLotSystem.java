import java.time.Duration;
import java.time.Instant;
import java.util.*;

public class ParkingLotSystem {

    // ================= ENUMS =================
    enum VehicleType { BIKE, CAR, TRUCK, ELECTRIC }
    enum ParkingSpotType { COMPACT, REGULAR, LARGE, ELECTRIC_CHARGING }

    // ================= VEHICLE =================
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

    // ================= PARKING SPOT =================
    static class ParkingSpot {
        String spotId;
        ParkingSpotType type;
        boolean occupied = false;

        ParkingSpot(String spotId, ParkingSpotType type) {
            this.spotId = spotId;
            this.type = type;
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

    // ================= PARKING FLOOR =================
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

    // ================= TICKET =================
    static class Ticket {
        String ticketId;
        ParkingSpot spot;
        Instant entryTime;
        Instant exitTime;

        Ticket(String ticketId, ParkingSpot spot) {
            this.ticketId = ticketId;
            this.spot = spot;
            this.entryTime = Instant.now();
        }

        void closeTicket() {
            this.exitTime = Instant.now();
        }
    }

    // ================= FEE CALCULATOR =================
    static class FeeCalculator {
        static double calculateFee(Instant entry, Instant exit) {
            long minutes = Duration.between(entry, exit).toMinutes();
            long hours = (long) Math.ceil(minutes / 60.0);

            if (hours <= 1) return 50;
            return 50 + (hours - 1) * 30;
        }
    }

    // ================= PAYMENT SERVICE =================
    static class PaymentService {
        void processPayment(double amount) {
            System.out.println("Payment of Rs " + amount + " processed successfully");
        }
    }

    // ================= PARKING LOT =================
    static class ParkingLot {
        List<ParkingFloor> floors = new ArrayList<>();
        Map<String, Ticket> activeTickets = new HashMap<>();
        int ticketCounter = 1000;

        void addFloor(ParkingFloor floor) {
            floors.add(floor);
        }

        ParkingSpotType mapVehicleToSpot(VehicleType type) {
            switch (type) {
                case BIKE: return ParkingSpotType.COMPACT;
                case CAR: return ParkingSpotType.REGULAR;
                case TRUCK: return ParkingSpotType.LARGE;
                default: return ParkingSpotType.ELECTRIC_CHARGING;
            }
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

        Ticket getTicket(String ticketId) {
            return activeTickets.get(ticketId);
        }

        void removeTicket(String ticketId) {
            activeTickets.remove(ticketId);
        }
    }

    // ================= ENTRY PANEL =================
    static class EntryPanel {
        ParkingLot parkingLot;

        EntryPanel(ParkingLot parkingLot) {
            this.parkingLot = parkingLot;
        }

        Ticket enterVehicle(Vehicle vehicle) {
            return parkingLot.parkVehicle(vehicle);
        }
    }

    // ================= EXIT PANEL =================
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

            System.out.println("Spot " + ticket.spot.spotId + " released");
        }
    }

    // ================= MAIN =================
    public static void main(String[] args) throws InterruptedException {

        ParkingLot parkingLot = new ParkingLot();

        ParkingFloor floor1 = new ParkingFloor(1);
        floor1.addSpot(new ParkingSpot("F1-R1", ParkingSpotType.REGULAR));
        floor1.addSpot(new ParkingSpot("F1-C1", ParkingSpotType.COMPACT));

        parkingLot.addFloor(floor1);

        EntryPanel entryPanel = new EntryPanel(parkingLot);
        ExitPanel exitPanel = new ExitPanel(parkingLot);

        Vehicle vehicle = new Vehicle("DL-01-AB-1234", VehicleType.CAR);

        Ticket ticket = entryPanel.enterVehicle(vehicle);

        if (ticket == null) {
            System.out.println("Parking Lot Full");
            return;
        }

        System.out.println("Ticket Issued");
        System.out.println("Ticket ID: " + ticket.ticketId);
        System.out.println("Spot: " + ticket.spot.spotId);

        Thread.sleep(2000); // simulate parking time

        exitPanel.exitVehicle(ticket.ticketId);
    }
}
