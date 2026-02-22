from enum import Enum
from datetime import datetime
import math
import threading
import uuid


# =====================================================
# ENUMS
# =====================================================

class VehicleType(Enum):
    BIKE = 1
    CAR = 2
    TRUCK = 3
    ELECTRIC = 4


class ParkingSpotType(Enum):
    COMPACT = 1
    REGULAR = 2
    LARGE = 3
    ELECTRIC_CHARGING = 4


# =====================================================
# MODELS
# =====================================================

class Vehicle:
    def __init__(self, license_number, vehicle_type):
        self.license_number = license_number
        self.type = vehicle_type

    def get_type(self):
        return self.type


class ParkingSpot:
    def __init__(self, spot_id, spot_type):
        self.spot_id = spot_id
        self.type = spot_type
        self.occupied = False
        self.lock = threading.Lock()

    def is_available(self):
        return not self.occupied

    def occupy(self):
        with self.lock:
            self.occupied = True

    def release(self):
        with self.lock:
            self.occupied = False


class ParkingFloor:
    def __init__(self, floor_number):
        self.floor_number = floor_number
        self.spots = []

    def add_spot(self, spot):
        self.spots.append(spot)

    def get_available_spot(self, spot_type):
        for spot in self.spots:
            if spot.type == spot_type and spot.is_available():
                return spot
        return None

    def get_availability(self):
        availability = {}
        for spot in self.spots:
            if spot.type not in availability:
                availability[spot.type] = 0
            if spot.is_available():
                availability[spot.type] += 1
        return availability


class Ticket:
    def __init__(self, spot):
        self.ticket_id = str(uuid.uuid4())[:8]
        self.spot = spot
        self.entry_time = datetime.now()
        self.exit_time = None

    def close_ticket(self):
        self.exit_time = datetime.now()


# =====================================================
# SERVICES
# =====================================================

class FeeCalculator:

    @staticmethod
    def calculate_fee(entry_time, exit_time):
        duration = exit_time - entry_time
        hours = math.ceil(duration.total_seconds() / 3600)

        if hours <= 1:
            return 50
        return 50 + (hours - 1) * 30


class PaymentService:

    def process_payment(self, amount):
        print(f"Processing payment of ₹{amount}...")
        print("Payment Successful!")


# =====================================================
# PARKING LOT CONTROLLER
# =====================================================

class ParkingLot:
    def __init__(self):
        self.floors = []
        self.active_tickets = {}
        self.lock = threading.Lock()

    def add_floor(self, floor):
        self.floors.append(floor)

    def _map_vehicle_to_spot(self, vehicle_type):
        mapping = {
            VehicleType.BIKE: ParkingSpotType.COMPACT,
            VehicleType.CAR: ParkingSpotType.REGULAR,
            VehicleType.TRUCK: ParkingSpotType.LARGE,
            VehicleType.ELECTRIC: ParkingSpotType.ELECTRIC_CHARGING,
        }
        return mapping.get(vehicle_type)

    def park_vehicle(self, vehicle):
        with self.lock:
            required_spot_type = self._map_vehicle_to_spot(vehicle.get_type())

            for floor in self.floors:
                spot = floor.get_available_spot(required_spot_type)
                if spot:
                    spot.occupy()
                    ticket = Ticket(spot)
                    self.active_tickets[ticket.ticket_id] = ticket
                    return ticket

        return None

    def get_ticket(self, ticket_id):
        return self.active_tickets.get(ticket_id)

    def remove_ticket(self, ticket_id):
        if ticket_id in self.active_tickets:
            del self.active_tickets[ticket_id]

    def show_availability(self):
        total = {}
        for floor in self.floors:
            availability = floor.get_availability()
            for spot_type, count in availability.items():
                total[spot_type] = total.get(spot_type, 0) + count

        for spot_type in ParkingSpotType:
            print(f"{spot_type.name}: {total.get(spot_type, 0)} available")


# =====================================================
# ENTRY & EXIT PANELS
# =====================================================

class EntryPanel:
    def __init__(self, parking_lot):
        self.parking_lot = parking_lot

    def enter_vehicle(self, vehicle):
        ticket = self.parking_lot.park_vehicle(vehicle)
        if ticket:
            print("\nTicket Issued")
            print(f"Ticket ID: {ticket.ticket_id}")
            print(f"Assigned Spot: {ticket.spot.spot_id}")
            print(f"Entry Time: {ticket.entry_time.strftime('%H:%M:%S')}")
        else:
            print("\nParking Full")
            print("Please try again later")
        return ticket


class ExitPanel:
    def __init__(self, parking_lot):
        self.parking_lot = parking_lot
        self.payment_service = PaymentService()

    def exit_vehicle(self, ticket_id):
        ticket = self.parking_lot.get_ticket(ticket_id)

        if not ticket:
            print("Invalid Ticket")
            return

        ticket.close_ticket()

        fee = FeeCalculator.calculate_fee(ticket.entry_time, ticket.exit_time)

        duration = ticket.exit_time - ticket.entry_time
        hours = duration.seconds // 3600
        minutes = (duration.seconds % 3600) // 60

        print("\nExit Details")
        print(f"Exit Time: {ticket.exit_time.strftime('%H:%M:%S')}")
        print(f"Duration: {hours} hours {minutes} minutes")
        print(f"Total Fee: ₹{fee}")

        self.payment_service.process_payment(fee)

        ticket.spot.release()
        self.parking_lot.remove_ticket(ticket_id)

        print(f"Spot Released: {ticket.spot.spot_id}")


# =====================================================
# MAIN DRIVER
# =====================================================

if __name__ == "__main__":

    parking_lot = ParkingLot()

    # Create floors
    floor1 = ParkingFloor(1)
    floor2 = ParkingFloor(2)

    # Add spots
    floor1.add_spot(ParkingSpot("F1-C1", ParkingSpotType.COMPACT))
    floor1.add_spot(ParkingSpot("F1-R1", ParkingSpotType.REGULAR))
    floor1.add_spot(ParkingSpot("F1-E1", ParkingSpotType.ELECTRIC_CHARGING))

    floor2.add_spot(ParkingSpot("F2-R1", ParkingSpotType.REGULAR))
    floor2.add_spot(ParkingSpot("F2-L1", ParkingSpotType.LARGE))

    # Register floors
    parking_lot.add_floor(floor1)
    parking_lot.add_floor(floor2)

    entry_panel = EntryPanel(parking_lot)
    exit_panel = ExitPanel(parking_lot)

    # Show availability
    print("\nCurrent Availability:")
    parking_lot.show_availability()

    # Vehicle Entry
    vehicle = Vehicle("DL-01-AB-1234", VehicleType.CAR)
    ticket = entry_panel.enter_vehicle(vehicle)

    # Vehicle Exit
    if ticket:
        exit_panel.exit_vehicle(ticket.ticket_id)

    # Show availability again
    print("\nUpdated Availability:")
    parking_lot.show_availability()
