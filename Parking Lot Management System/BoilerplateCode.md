## Java
```java
import java.time.Duration;
import java.time.LocalDateTime;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class ParkingLotSystem {

    /* ===================== ENUMS ===================== */

    enum VehicleType {
        BIKE, CAR, TRUCK, ELECTRIC
    }

    enum ParkingSpotType {
        COMPACT, REGULAR, LARGE, ELECTRIC_CHARGING
    }

    /* ===================== MODELS ===================== */

    static class Vehicle {
        private final String licenseNumber;
        private final VehicleType type;

        Vehicle(String licenseNumber, VehicleType type) {
            this.licenseNumber = licenseNumber;
            this.type = type;
        }

        VehicleType getType() {
            return type;
        }
    }

    static class ParkingSpot {
        private final String spotId;
        private final ParkingSpotType type;
        private boolean occupied;

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

        ParkingSpotType getType() {
            return type;
        }

        String getSpotId() {
            return spotId;
        }
    }

    static class ParkingFloor {
        private final int floorNumber;
        private final List<ParkingSpot> spots = new ArrayList<>();

        ParkingFloor(int floorNumber) {
            this.floorNumber = floorNumber;
        }

        void addSpot(ParkingSpot spot) {
            spots.add(spot);
        }

        Optional<ParkingSpot> getAvailableSpot(ParkingSpotType type) {
            return spots.stream()
                    .filter(s -> s.getType() == type && s.isAvailable())
                    .findFirst();
        }

        int getFloorNumber() {
            return floorNumber;
        }
    }

    static class Ticket {
        private final String ticketId;
        private final ParkingSpot spot;
        private final LocalDateTime entryTime;
        private LocalDateTime exitTime;

        Ticket(String ticketId, ParkingSpot spot) {
            this.ticketId = ticketId;
            this.spot = spot;
            this.entryTime = LocalDateTime.now();
        }

        void close() {
            this.exitTime = LocalDateTime.now();
        }

        LocalDateTime getEntryTime() {
            return entryTime;
        }

        LocalDateTime getExitTime() {
            return exitTime;
        }

        ParkingSpot getSpot() {
            return spot;
        }

        String getTicketId() {
            return ticketId;
        }
    }

    /* ===================== SERVICES ===================== */

    static class FeeCalculator {

        static double calculate(LocalDateTime entry, LocalDateTime exit) {
            long minutes = Duration.between(entry, exit).toMinutes();
            long hours = (minutes + 59) / 60; // round up

            if (hours <= 1) return 50;
            return 50 + (hours - 1) * 30;
        }
    }

    static class PaymentService {
        void pay(double amount) {
            System.out.println("Payment successful: ₹" + amount);
        }
    }

    static class ParkingLot {
        private final List<ParkingFloor> floors = new ArrayList<>();
        private final Map<String, Ticket> activeTickets = new ConcurrentHashMap<>();

        void addFloor(ParkingFloor floor) {
            floors.add(floor);
        }

        Ticket park(Vehicle vehicle) {
            ParkingSpotType requiredSpot = mapVehicleToSpot(vehicle.getType());

            for (ParkingFloor floor : floors) {
                Optional<ParkingSpot> spotOpt = floor.getAvailableSpot(requiredSpot);
                if (spotOpt.isPresent()) {
                    ParkingSpot spot = spotOpt.get();
                    spot.occupy();

                    Ticket ticket = new Ticket(UUID.randomUUID().toString(), spot);
                    activeTickets.put(ticket.getTicketId(), ticket);

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

        private ParkingSpotType mapVehicleToSpot(VehicleType type) {
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
                    throw new IllegalArgumentException();
            }
        }
    }

    static class EntryPanel {
        private final ParkingLot parkingLot;

        EntryPanel(ParkingLot parkingLot) {
            this.parkingLot = parkingLot;
        }

        Ticket enter(Vehicle vehicle) {
            return parkingLot.park(vehicle);
        }
    }

    static class ExitPanel {
        private final ParkingLot parkingLot;
        private final PaymentService paymentService = new PaymentService();

        ExitPanel(ParkingLot parkingLot) {
            this.parkingLot = parkingLot;
        }

        void exit(String ticketId) {
            Ticket ticket = parkingLot.getTicket(ticketId);
            if (ticket == null) {
                System.out.println("Invalid or lost ticket");
                return;
            }

            ticket.close();
            double fee = FeeCalculator.calculate(
                    ticket.getEntryTime(),
                    ticket.getExitTime()
            );

            paymentService.pay(fee);
            ticket.getSpot().release();
            parkingLot.removeTicket(ticketId);

            System.out.println("Spot released: " + ticket.getSpot().getSpotId());
        }
    }

    /* ===================== MAIN ===================== */

    public static void main(String[] args) {

        ParkingLot parkingLot = new ParkingLot();

        ParkingFloor floor1 = new ParkingFloor(1);
        floor1.addSpot(new ParkingSpot("C1", ParkingSpotType.COMPACT));
        floor1.addSpot(new ParkingSpot("R1", ParkingSpotType.REGULAR));
        floor1.addSpot(new ParkingSpot("E1", ParkingSpotType.ELECTRIC_CHARGING));

        parkingLot.addFloor(floor1);

        EntryPanel entryPanel = new EntryPanel(parkingLot);
        ExitPanel exitPanel = new ExitPanel(parkingLot);

        Vehicle car = new Vehicle("DL-01-AB-1234", VehicleType.CAR);

        Ticket ticket = entryPanel.enter(car);

        if (ticket == null) {
            System.out.println("Parking Full");
            return;
        }

        System.out.println("Ticket Issued");
        System.out.println("Ticket ID: " + ticket.getTicketId());
        System.out.println("Assigned Spot: " + ticket.getSpot().getSpotId());

        // simulate exit
        exitPanel.exit(ticket.getTicketId());
    }
}
```
