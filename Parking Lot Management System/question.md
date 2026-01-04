# Parking Lot System Design

## 🧩 Problem Statement
Design a parking lot system that manages parking spaces, vehicle entry and exit,
ticketing, and fee calculation. The system should simulate real-world parking lot
operations while remaining modular, extensible, and easy to maintain.

The goal is to clearly define system requirements, core components, and interactions
before implementing the solution.

---

## 🎯 Objectives
- Efficiently allocate parking spaces to vehicles
- Track entry and exit times
- Calculate parking fees
- Maintain real-time availability of parking spaces
- Support different vehicle and spot types
- Allow multiple entry and exit points

---

## 🧠 Requirements

### Functional Requirements
1. Assign an available parking space when a vehicle enters.
2. Generate a parking ticket with entry time and assigned spot.
3. Release the parking spot when the vehicle exits.
4. Calculate parking fees based on duration.
5. Display current availability of parking spaces.
6. Support different vehicle types and parking spot types.
7. Handle cases when the parking lot is full.

### Non-Functional Requirements
- Scalable to multiple floors
- Modular and extensible design
- Thread-safe for concurrent entry/exit
- Clear separation of responsibilities

---

## 🚗 Supported Entities

### Vehicle Types
- Car
- Bike
- Truck
- Electric Vehicle

### Parking Spot Types
- Compact
- Regular
- Large
- Electric Charging

---

## 🏗️ System Components

### Core Components

| Component        | Responsibility |
|------------------|----------------|
| ParkingLot       | Manages the overall parking system |
| ParkingFloor     | Represents a single floor |
| ParkingSpot      | Represents an individual parking space |
| Vehicle          | Stores vehicle details |
| Ticket           | Tracks entry time, exit time, and spot |
| EntryPanel       | Handles vehicle entry |
| ExitPanel        | Handles vehicle exit |
| PaymentService   | Calculates and processes fees |

---

## 🔄 System Flow

### Vehicle Entry Flow
1. Vehicle arrives at an entry panel.
2. System checks for an available spot suitable for the vehicle.
3. Nearest available spot is assigned.
4. Ticket is generated with entry time.
5. Spot is marked as occupied.

```bash
Input:
Enter Vehicle: CAR

Output:
Ticket Issued
Ticket ID: 1021
Assigned Spot: Floor 1 - R12
Entry Time: 10:05
```

### Vehicle Exit Flow
1. Vehicle presents the ticket at exit panel.
2. System calculates parking duration.
3. Parking fee is calculated.
4. Payment is processed.
5. Spot is released and marked available.

```bash
Input:
Exit Ticket: 1021

Output:
Exit Time: 12:30
Duration: 2 hours 25 minutes
Total Fee: ₹120
Spot Released: Floor 1 - R12

```

🧪 Example Scenarios
```bash
Example 1: Parking Lot Full
Input:
Enter Vehicle: TRUCK

Output:
Parking Full
Please try again later
```
```bash
Example 2: Check Availability
Input:
Show Parking Status

Output:
Compact: 5 available
Regular: 12 available
Large: 3 available
Electric Charging: 2 available
```

## 🧱 Design Principles Used
1. Encapsulation
2. Each component handles its own logic and state.
3. Modularity
4. Independent components make the system easy to extend.
5. Single Responsibility
6. Each class performs one well-defined task.
7. Extensibility
8. New vehicle types, spot types, or pricing models can be added easily.

## 💰 Fee Calculation (Example)
```bash
First hour: ₹50

Every additional hour: ₹30

Partial hour rounded up

Parking Time: 2 hours 10 minutes
Fee:
50 + 30 + 30 = ₹110
```

## 📌 Edge Cases Considered

Parking lot completely full

Invalid or lost ticket

Multiple entry and exit points

Vehicle exits without payment

Spot reassignment after exit

## 📈 Possible Enhancements

Online slot reservation

Dynamic pricing

Mobile app integration

License plate recognition

Analytics dashboard
