class BusRoutePlanner:
    def __init__(self):
        self.routes = {}  # route_id -> list of stops

    def add_route(self, route_id, stops):
        if route_id in self.routes:
            print("Route already exists.")
            return
        self.routes[route_id] = stops
        print(f"Route {route_id} added successfully.")

    def find_route(self, start, destination):
        for route_id, stops in self.routes.items():
            if start in stops and destination in stops:
                start_index = stops.index(start)
                dest_index = stops.index(destination)
                if start_index < dest_index:
                    print(f"Take Route {route_id} from {start} to {destination}.")
                    return
        print("No direct route available.")

    def display_routes(self):
        for route_id, stops in self.routes.items():
            print(f"Route {route_id}: {', '.join(stops)}")


def main():
    planner = BusRoutePlanner()
    
    while True:
        print("\n1. Add Route\n2. Find Route\n3. Display Routes\n4. Exit")
        choice = input("Enter choice: ")
        
        if choice == "4":
            break
        
        if choice == "1":
            route_id = input("Enter route ID: ")
            stops = input("Enter stops separated by commas: ").split(",")
            planner.add_route(route_id, [stop.strip() for stop in stops])
        
        elif choice == "2":
            start = input("Enter start stop: ")
            destination = input("Enter destination stop: ")
            planner.find_route(start, destination)
        
        elif choice == "3":
            planner.display_routes()
        
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()
