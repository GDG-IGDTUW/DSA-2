import heapq
import math

class ParkingLot:
    def __init__(self, total_spots):
        self.total_spots = total_spots
        self.available_spots = list(range(1, total_spots + 1))  # Min-heap to store available spots
        heapq.heapify(self.available_spots)
        self.parked_vehicles = {}  # Stores {license_plate: (spot_number, entry_time)}

    def park_vehicle(self, vehicle_type, license_plate, entry_time):
        if not self.available_spots:
            return -1  # Parking lot full
        
        spot_number = heapq.heappop(self.available_spots)  # Allocate nearest available spot
        self.parked_vehicles[license_plate] = (spot_number, entry_time)
        return f"Spot {spot_number} allocated to {vehicle_type} {license_plate}"

    def remove_vehicle(self, license_plate, exit_time):
        if license_plate not in self.parked_vehicles:
            return -1  # Vehicle not found
        
        spot_number, entry_time = self.parked_vehicles.pop(license_plate)
        heapq.heappush(self.available_spots, spot_number)  # Free the spot
        
        hours_parked = math.ceil((exit_time - entry_time) / 60)  # Convert minutes to hours (rounded up)
        parking_fee = hours_parked * 20
        
        return f"{license_plate} removed from Spot {spot_number}. Parking fee: ₹{parking_fee}"

# Example Usage
total_spots = 3
parking_lot = ParkingLot(total_spots)

print(parking_lot.park_vehicle("car", "ABC-123", 0))
print(parking_lot.park_vehicle("bike", "XYZ-456", 2))
print(parking_lot.remove_vehicle("ABC-123", 120))
