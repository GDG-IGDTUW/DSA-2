#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <regex> // For email validation
#include <algorithm> // For case-insensitive matching
using namespace std;

const int INITIAL_ORDER_ID = 100; // Constant for starting order ID

class Restaurant {
private:
    string name;
    string cuisine;
    unordered_map<string, double> menu;

public:
    Restaurant() {}
    Restaurant(string name, string cuisine) : name(name), cuisine(cuisine) {}

    void addItem(string item, double price) {
        if (item.empty() || price <= 0) {
            cout << "Invalid menu item or price." << endl;
            return;
        }
        transform(item.begin(), item.end(), item.begin(), ::tolower); // Normalize case
        menu[item] = price;
    }

    void viewMenu() const {
        if (menu.empty()) {
            cout << "The menu is currently empty." << endl;
        } else {
            cout << "Menu for " << name << ":" << endl;
            for (const auto& item : menu) {
                cout << "- " << item.first << ": $" << item.second << endl;
            }
        }
    }

    double getItemPrice(const string& item) const {
        string lowerItem = item;
        transform(lowerItem.begin(), lowerItem.end(), lowerItem.begin(), ::tolower);
        auto it = menu.find(lowerItem);
        return (it != menu.end()) ? it->second : -1;
    }
};

class User {
private:
    string name, username, password, email, phone, address;
    vector<int> orderHistory;

public:
    User() {}
    User(string name, string username, string password, string email, string phone, string address)
        : name(name), username(username), password(password), email(email), phone(phone), address(address) {}

    bool validatePassword(const string& inputPassword) const {
        return inputPassword == password;
    }

    static bool isValidEmail(const string& email) {
        const regex pattern(R"((\w+)(\.\w+)*@(\w+)(\.(\w+))+)");
        return regex_match(email, pattern);
    }

    static bool isValidPhone(const string& phone) {
        return phone.size() == 10 && all_of(phone.begin(), phone.end(), ::isdigit);
    }

    void addToOrderHistory(int orderId) {
        orderHistory.push_back(orderId);
    }

    void viewOrderHistory() const {
        if (orderHistory.empty()) {
            cout << "No orders placed yet." << endl;
        } else {
            cout << "Order History for " << name << ":" << endl;
            for (int orderId : orderHistory) {
                cout << "Order ID: " << orderId << endl;
            }
        }
    }

    void updateAddress(const string& newAddress) {
        address = newAddress;
        cout << "Address updated successfully!" << endl;
    }

    void changePassword(const string& newPassword) {
        password = newPassword;
        cout << "Password updated successfully!" << endl;
    }

    string getUsername() const { return username; }
};

class FoodDeliverySystem {
private:
    unordered_map<string, User> users;
    unordered_map<string, Restaurant> restaurants;
    struct Order {
        int id;
        string restaurantName;
        vector<string> items;
        double totalPrice;
        string status;
    };
    unordered_map<int, Order> orders;
    int orderIdCounter = INITIAL_ORDER_ID;

public:
    bool registerUser(const User& user) {
        if (users.find(user.getUsername()) == users.end()) {
            users[user.getUsername()] = user;
            cout << "User registered successfully!" << endl;
            return true;
        }
        cout << "User already exists." << endl;
        return false;
    }

    bool loginUser(const string& username) {
        if (users.find(username) != users.end()) {
            string password;
            cout << "Enter password: ";
            cin >> password;
            if (users[username].validatePassword(password)) {
                cout << "Login successful!" << endl;
                return true;
            } else {
                cout << "Incorrect password. Try again." << endl;
                return false;
            }
        }
        cout << "User not found." << endl;
        return false;
    }

    void addRestaurant(const string& name, const string& cuisine) {
        restaurants[name] = Restaurant(name, cuisine);
        cout << "Restaurant added successfully!" << endl;
    }

    void addMenuItem(const string& restaurantName, const string& item, double price) {
        if (restaurants.find(restaurantName) != restaurants.end()) {
            restaurants[restaurantName].addItem(item, price);
            cout << "Item added to the menu!" << endl;
        } else {
            cout << "Restaurant not found." << endl;
        }
    }

    void placeOrder(const string& username, const string& restaurantName, const vector<string>& items) {
        if (restaurants.find(restaurantName) == restaurants.end()) {
            cout << "Restaurant not found." << endl;
            return;
        }

        double totalPrice = 0;
        for (const auto& item : items) {
            double price = restaurants[restaurantName].getItemPrice(item);
            if (price == -1) {
                cout << "Item '" << item << "' not found in the menu." << endl;
                return;
            }
            totalPrice += price;
        }

        int orderId = orderIdCounter++;
        orders[orderId] = {orderId, restaurantName, items, totalPrice, "Placed"};
        users[username].addToOrderHistory(orderId);
        cout << "Order placed successfully. Order ID: " << orderId << endl;
    }
};

int main() {
    FoodDeliverySystem system;
    system.registerUser(User("Kashish", "k10", "abcd", "example@example.com", "1234567890", "Delhi"));
    system.addRestaurant("Pizza Palace", "Italian");
    system.addMenuItem("Pizza Palace", "Margherita Pizza", 10);
    system.addMenuItem("Pizza Palace", "Garlic Bread", 5);
    system.placeOrder("k10", "Pizza Palace", {"Margherita Pizza", "Garlic Bread"});

    system.registerUser(User("Kashish", "k10", "abcd", "example@example.com", "1234567890", "Delhi"));

    return 0;
}
