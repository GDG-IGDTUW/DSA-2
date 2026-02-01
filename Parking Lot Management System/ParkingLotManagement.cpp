#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <ctime>
#include <unistd.h>

using namespace std;

class ParkingLotSystem {

public:

    enum class VehicleType { BIKE, CAR, TRUCK, ELECTRIC };
    enum class ParkingSpotType { COMPACT, REGULAR, LARGE, ELECTRIC_CHARGING };

    class Vehicle {
    public:
        string licenseNumber;
        VehicleType type;

        Vehicle(string licenseNumber, VehicleType type)
            : licenseNumber(licenseNumber), type(type) {}

        VehicleType getType() {
            return type;
        }
    };

    class ParkingSpot {
    public:
        string spotId;
        ParkingSpotType type;
        bool occupied;

        ParkingSpot(string spotId, ParkingSpotType type)
            : spotId(spotId), type(type), occupied(false) {}

        bool isAvailable() {
            return !occupied;
        }

        void occupy() {
            occupied = true;
        }

        void release() {
            occupied = false;
        }
    };

    class ParkingFloor {
    public:
        int floorNumber;
        vector<ParkingSpot*> spots;

        ParkingFloor(int floorNumber) : floorNumber(floorNumber) {}

        void addSpot(ParkingSpot* spot) {
            spots.push_back(spot);
        }

        ParkingSpot* getAvailableSpot(ParkingSpotType type) {
            for (auto spot : spots) {
                if (spot->type == type && spot->isAvailable()) {
                    return spot;
                }
            }
            return nullptr;
        }
    };

    class Ticket {
    public:
        string ticketId;
        ParkingSpot* spot;
        time_t entryTime;
        time_t exitTime;

        Ticket(string ticketId, ParkingSpot* spot)
            : ticketId(ticketId), spot(spot) {
            entryTime = time(nullptr);
        }

        void closeTicket() {
            exitTime = time(nullptr);
        }
    };

    class FeeCalculator {
    public:
        static double calculateFee(time_t entry, time_t exit) {
            double minutes = difftime(exit, entry) / 60.0;
            int hours = ceil(minutes / 60.0);

            if (hours <= 1) return 50;
            return 50 + (hours - 1) * 30;
        }
    };

    class PaymentService {
    public:
        void processPayment(double amount) {
            cout << "Payment of ₹" << amount << " processed successfully\n";
        }
    };

    class ParkingLot {
    private:
        vector<ParkingFloor*> floors;
        unordered_map<string, Ticket*> activeTickets;
        int ticketCounter = 1000;

    public:
        void addFloor(ParkingFloor* floor) {
            floors.push_back(floor);
        }

        ParkingSpotType mapVehicleToSpot(VehicleType type) {
            if (type == VehicleType::BIKE) return ParkingSpotType::COMPACT;
            if (type == VehicleType::CAR) return ParkingSpotType::REGULAR;
            if (type == VehicleType::TRUCK) return ParkingSpotType::LARGE;
            return ParkingSpotType::ELECTRIC_CHARGING;
        }

        Ticket* parkVehicle(Vehicle* vehicle) {
            ParkingSpotType requiredType = mapVehicleToSpot(vehicle->getType());

            for (auto floor : floors) {
                ParkingSpot* spot = floor->getAvailableSpot(requiredType);
                if (spot != nullptr) {
                    spot->occupy();
                    string ticketId = to_string(++ticketCounter);
                    Ticket* ticket = new Ticket(ticketId, spot);
                    activeTickets[ticketId] = ticket;
                    return ticket;
                }
            }
            return nullptr;
        }

        Ticket* getTicket(string ticketId) {
            if (activeTickets.count(ticketId))
                return activeTickets[ticketId];
            return nullptr;
        }

        void removeTicket(string ticketId) {
            activeTickets.erase(ticketId);
        }
    };

    class EntryPanel {
    private:
        ParkingLot* parkingLot;

    public:
        EntryPanel(ParkingLot* parkingLot) : parkingLot(parkingLot) {}

        Ticket* enterVehicle(Vehicle* vehicle) {
            return parkingLot->parkVehicle(vehicle);
        }
    };

    class ExitPanel {
    private:
        ParkingLot* parkingLot;
        PaymentService paymentService;

    public:
        ExitPanel(ParkingLot* parkingLot) : parkingLot(parkingLot) {}

        void exitVehicle(string ticketId) {
            Ticket* ticket = parkingLot->getTicket(ticketId);
            if (!ticket) {
                cout << "Invalid ticket\n";
                return;
            }

            ticket->closeTicket();
            double fee = FeeCalculator::calculateFee(ticket->entryTime, ticket->exitTime);
            paymentService.processPayment(fee);

            ticket->spot->release();
            parkingLot->removeTicket(ticketId);

            cout << "Spot " << ticket->spot->spotId << " released\n";
        }
    };
};

int main() {
    using PLS = ParkingLotSystem;

    PLS::ParkingLot parkingLot;

    auto floor1 = new PLS::ParkingFloor(1);
    floor1->addSpot(new PLS::ParkingSpot("F1-R1", PLS::ParkingSpotType::REGULAR));
    floor1->addSpot(new PLS::ParkingSpot("F1-C1", PLS::ParkingSpotType::COMPACT));

    parkingLot.addFloor(floor1);

    PLS::EntryPanel entryPanel(&parkingLot);
    PLS::ExitPanel exitPanel(&parkingLot);

    PLS::Vehicle vehicle("DL-01-AB-1234", PLS::VehicleType::CAR);

    auto ticket = entryPanel.enterVehicle(&vehicle);
    if (!ticket) {
        cout << "Parking Lot Full\n";
        return 0;
    }

    cout << "Ticket Issued\n";
    cout << "Ticket ID: " << ticket->ticketId << "\n";
    cout << "Spot: " << ticket->spot->spotId << "\n";

    sleep(2);

    exitPanel.exitVehicle(ticket->ticketId);

    return 0;
}
