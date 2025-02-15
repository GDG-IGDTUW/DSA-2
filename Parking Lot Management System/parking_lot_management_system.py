import math

class ParkingLot:
    def __init__(self, total_spots):
        self.total_spots = total_spots
        self.available_spots = list(range(total_spots, 0, -1))  # LIFO stack
        self.parked_vehicles = {}  # license -> (vehicle_type, entry_time, spot)
        self.parking_rate = 20  # Fixed rate per hour

    def park_vehicle(self, vehicle_type, license_plate, entry_time):
        if not self.available_spots:
            print("-1")  # Parking lot is full
            return
        if license_plate in self.parked_vehicles:
            print(f"Vehicle with license {license_plate} is already parked.")
            return
        
        spot = self.available_spots.pop()
        self.parked_vehicles[license_plate] = (vehicle_type, entry_time, spot)
        print(f"Spot {spot} allocated to {vehicle_type} {license_plate}.")

    def remove_vehicle(self, license_plate, exit_time):
        if license_plate not in self.parked_vehicles:
            print("-1")  # Vehicle not found
            return
        
        vehicle_type, entry_time, spot = self.parked_vehicles.pop(license_plate)
        duration = max(1, exit_time - entry_time)  # Ensure at least 1-hour charge
        fee = math.ceil(duration) * self.parking_rate
        self.available_spots.append(spot)  # Free the spot
        
        print(f"{vehicle_type} {license_plate} removed from Spot {spot}. Parking fee: ₹{fee}.")


def main():
    while True:
        try:
            total_spots = int(input("Enter total parking spots (1-1000): "))
            if 1 <= total_spots <= 1000:
                break
            print("Invalid input. Please enter a number between 1 and 1000.")
        except ValueError:
            print("Please enter a valid integer.")
    
    lot = ParkingLot(total_spots)
    
    while True:
        print("\n1. Park Vehicle\n2. Remove Vehicle\n3. Exit")
        choice = input("Enter choice: ")
        
        if choice == "3":
            break
        
        if choice == "1":
            vehicle_type = input("Enter vehicle type (car/bike): ")
            license_plate = input("Enter license number: ")
            entry_time = int(input("Enter entry time (0-23): "))
            lot.park_vehicle(vehicle_type, license_plate, entry_time)
        
        elif choice == "2":
            license_plate = input("Enter license number: ")
            exit_time = int(input("Enter exit time (0-23): "))
            lot.remove_vehicle(license_plate, exit_time)
        
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()
