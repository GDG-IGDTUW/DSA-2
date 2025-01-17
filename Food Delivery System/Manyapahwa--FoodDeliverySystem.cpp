#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Class to represent a Restaurant
class Restaurant {
public:
    string name;
    string cuisine;
    unordered_map<string, double> menu;

    // Default constructor
    Restaurant() : name("Unknown"), cuisine("Unknown") {}

    // Parameterized constructor to initialize Restaurant object with name and cuisine
    Restaurant(string name, string cuisine) : name(name), cuisine(cuisine) {}

    // Method to add an item to the restaurant's menu
    void addItem(string item, double price) {
        menu[item] = price;
    }
};

// Class to manage the Food Delivery System
class FoodDeliverySystem {
private:
    unordered_map<string, Restaurant> restaurants;  // Stores restaurant data
    unordered_map<int, string> orders;              // Stores orders with order ID
    int orderIdCounter = 100;                        // Counter to generate unique order IDs

public:
    // Default constructor
    FoodDeliverySystem() {}

    // Method to add a new restaurant
    void addRestaurant(string name, string cuisine) {
        restaurants[name] = Restaurant(name, cuisine);
        cout << "Restaurant '" << name << "' added successfully!" << endl;
    }

    // Method to add a menu item to a restaurant's menu
    void addMenuItem(string restaurantName, string item, double price) {
        if (restaurants.find(restaurantName) != restaurants.end()) {
            restaurants[restaurantName].addItem(item, price);
            cout << "Item '" << item << "' added to the menu of " << restaurantName << endl;
        } else {
            cout << "Restaurant not found." << endl;
        }
    }

    // Method to place an order
    int placeOrder(string restaurantName, vector<string> items) {
        if (restaurants.find(restaurantName) != restaurants.end()) {
            double totalPrice = 0;
            for (const auto& item : items) {
                if (restaurants[restaurantName].menu.find(item) != restaurants[restaurantName].menu.end()) {
                    totalPrice += restaurants[restaurantName].menu[item];
                } else {
                    cout << "Item '" << item << "' not found on the menu." << endl;
                    return -1;  // Return -1 if any item is not found
                }
            }
            int orderId = orderIdCounter++;  // Generate new order ID
            orders[orderId] = restaurantName + " | " + "Items: ";
            for (const auto& item : items) orders[orderId] += item + " ";
            orders[orderId] += "| Total: $" + to_string(totalPrice);
            cout << "Order placed successfully. Order ID: " << orderId << endl;
            return orderId;  // Return the order ID
        } else {
            cout << "Restaurant not found." << endl;
            return -1;  // Return -1 if the restaurant is not found
        }
    }

    // Method to view the history of all placed orders
    void viewOrderHistory() {
        if (orders.empty()) {
            cout << "No orders placed yet." << endl;
        } else {
            cout << "Order History:" << endl;
            for (const auto& entry : orders) {
                cout << "Order ID: " << entry.first << " | Details: " << entry.second << endl;
            }
        }
    }

    // Method to cancel an order by order ID
    void cancelOrder(int orderId) {
        if (orders.find(orderId) != orders.end()) {
            orders.erase(orderId);  // Remove order from the order list
            cout << "Order ID " << orderId << " has been cancelled." << endl;
        } else {
            cout << "Order not found." << endl;
        }
    }
};

// Main function to test the Food Delivery System
int main() {
    FoodDeliverySystem system;

    // Adding restaurants and menu items
    system.addRestaurant("Pizza Palace", "Italian");
    system.addMenuItem("Pizza Palace", "Margherita Pizza", 10);
    system.addMenuItem("Pizza Palace", "Garlic Bread", 5);

    // Placing an order and storing the returned order ID
    int orderId = system.placeOrder("Pizza Palace", {"Margherita Pizza", "Garlic Bread"});

    // Viewing order history
    system.viewOrderHistory();

    // Canceling the order by using the returned order ID
    if (orderId != -1) {
        system.cancelOrder(orderId);  // Cancel the placed order
    }

    // Viewing order history again after cancellation
    system.viewOrderHistory();
    
    return 0;
}
