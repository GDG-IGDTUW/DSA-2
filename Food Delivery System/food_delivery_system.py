class Restaurant:
    def __init__(self, name):
        self.name = name
        self.menu = {}  # Stores menu items and their prices
        self.orders = []  # Stores all customer orders

    def add_menu_item(self, item_name, price):
        """Adds an item to the restaurant's menu."""
        self.menu[item_name] = price
        print(f"{item_name} added to menu at ₹{price}")

    def display_menu(self):
        """Displays the restaurant's menu."""
        if not self.menu:
            print("No items in the menu.")
            return
        print("\nMenu:")
        for item, price in self.menu.items():
            print(f"{item}: ₹{price}")

    def place_order(self, customer_name, items):
        """Places an order for the given items."""
        total_price = 0
        order_details = {"customer": customer_name, "items": {}, "total": 0}

        for item, quantity in items.items():
            if item in self.menu:
                order_details["items"][item] = quantity
                total_price += self.menu[item] * quantity
            else:
                print(f"Item '{item}' not available.")

        if total_price > 0:
            order_details["total"] = total_price
            self.orders.append(order_details)
            print(f"Order placed for {customer_name}. Total: ₹{total_price}")
        else:
            print("No valid items in order.")

    def display_orders(self):
        """Displays all orders placed."""
        if not self.orders:
            print("No orders placed yet.")
            return
        print("\nOrders:")
        for idx, order in enumerate(self.orders, start=1):
            print(f"\nOrder {idx}:")
            print(f"Customer: {order['customer']}")
            print("Items:")
            for item, qty in order["items"].items():
                print(f"  {item} x{qty}")
            print(f"Total: ₹{order['total']}")

# Main function to demonstrate the food delivery system
def main():
    restaurant = Restaurant("Delicious Bites")

    while True:
        print("\n1. Add Menu Item\n2. Display Menu\n3. Place Order\n4. View Orders\n5. Exit")
        choice = input("Enter your choice: ")

        if choice == "1":
            item_name = input("Enter item name: ")
            price = float(input("Enter item price: "))
            restaurant.add_menu_item(item_name, price)

        elif choice == "2":
            restaurant.display_menu()

        elif choice == "3":
            customer_name = input("Enter customer name: ")
            items = {}
            while True:
                item = input("Enter item name (or 'done' to finish): ")
                if item.lower() == "done":
                    break
                quantity = int(input(f"Enter quantity for {item}: "))
                items[item] = quantity
            restaurant.place_order(customer_name, items)

        elif choice == "4":
            restaurant.display_orders()

        elif choice == "5":
            print("Exiting system.")
            break

        else:
            print("Invalid choice. Try again.")

if __name__ == "__main__":
    main()
