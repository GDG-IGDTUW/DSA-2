class Warehouse:
    def __init__(self):
        self.inventory = {}  # item_name -> (quantity, price_per_unit)
    
    def add_item(self, item_name, quantity, price_per_unit):
        if item_name in self.inventory:
            self.inventory[item_name] = (self.inventory[item_name][0] + quantity, price_per_unit)
        else:
            self.inventory[item_name] = (quantity, price_per_unit)
        print(f"Added {quantity} units of {item_name} at ₹{price_per_unit} each.")
    
    def remove_item(self, item_name, quantity):
        if item_name not in self.inventory or self.inventory[item_name][0] < quantity:
            print("-1")  # Item not available or insufficient quantity
            return
        
        new_quantity = self.inventory[item_name][0] - quantity
        price_per_unit = self.inventory[item_name][1]
        if new_quantity == 0:
            del self.inventory[item_name]
        else:
            self.inventory[item_name] = (new_quantity, price_per_unit)
        print(f"Removed {quantity} units of {item_name}.")
    
    def check_inventory(self):
        if not self.inventory:
            print("Inventory is empty.")
            return
        print("Current Inventory:")
        for item, (quantity, price) in self.inventory.items():
            print(f"{item}: {quantity} units, ₹{price} each")


def main():
    warehouse = Warehouse()
    
    while True:
        print("\n1. Add Item\n2. Remove Item\n3. Check Inventory\n4. Exit")
        choice = input("Enter choice: ")
        
        if choice == "4":
            break
        
        if choice == "1":
            item_name = input("Enter item name: ")
            quantity = int(input("Enter quantity: "))
            price_per_unit = float(input("Enter price per unit: "))
            warehouse.add_item(item_name, quantity, price_per_unit)
        
        elif choice == "2":
            item_name = input("Enter item name: ")
            quantity = int(input("Enter quantity to remove: "))
            warehouse.remove_item(item_name, quantity)
        
        elif choice == "3":
            warehouse.check_inventory()
        
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()
