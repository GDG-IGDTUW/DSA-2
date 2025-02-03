#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <regex> // For email validation
#include <algorithm> // For transforming strings to lowercase
using namespace std;

class Restaurant {
public:
    string name;
    string cuisine;
    unordered_map<string, double> menu;

    // Default Constructor
    Restaurant() : name(""), cuisine("") {}

    Restaurant(string name, string cuisine) : name(name), cuisine(cuisine) {}

    void addItem(string item, double price) {
        if (item.empty() || price <= 0) {
            cout << "Invalid menu item or price." << endl;
            return;
        }
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
};

class User {
private:
    string name, username, password, email, phone, address;
    vector<int> orderHistory; // To store order IDs of past orders

public:
    // Parameterized Constructor
    User(string name, string username, string password, string email, string phone, string address)
        : name(name), username(username), password(password), email(email), phone(phone), address(address) {}

    // Default Constructor
    User() {
        name = username = password = email = phone = address = "";
    }

    // Getters
    string getUserName() const { return username; }
    string getEmail() const { return email; }
    string getPassword() const { return password; }

    // Password Handling
    bool validatePassword(const string& inputPassword) {
        return inputPassword == password;
    }

    // Validation Functions
    static bool isValidEmail(const string& email) {
        const regex pattern(R"((\w+)(\.\w+)*@(\w+)(\.(\w+))+)");
        return regex_match(email, pattern);
    }

    static bool isValidPhone(const string& phone) {
        return phone.size() == 10 && all_of(phone.begin(), phone.end(), ::isdigit);
    }

    // User Input Validation
    bool validateUser() {
        if (name.empty() || username.empty() || password.empty() || address.empty()) {
            cout << "All fields must be filled." << endl;
            return false;
        }
        if (!isValidEmail(email)) {
            cout << "Invalid email format." << endl;
            return false;
        }
        if (!isValidPhone(phone)) {
            cout << "Invalid phone number. It must contain 10 digits." << endl;
            return false;
        }
        return true;
    }

    // Order History Handling
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

    // Update User Information
    void updateAddress(const string& newAddress) {
        address = newAddress;
        cout << "Address updated successfully!" << endl;
    }

    void changePassword(const string& newPassword) {
        password = newPassword;
        cout << "Password updated successfully!" << endl;
    }
};

class FoodDeliverySystem {
private:
    unordered_map<string, User> users;  // Stores users by their username
    unordered_map<string, Restaurant> restaurants;
    struct Order {
        int id;
        string restaurantName;
        vector<string> items;
        double totalPrice;
        string status; // Status of the order
    };
    unordered_map<int, Order> orders;
    int orderIdCounter = 100;

public:
    bool registerUser(User user) {
        if (!user.validateUser()) {
            return false;
        }
        if (users.find(user.getUserName()) == users.end()) {
            users[user.getUserName()] = user;
            cout << "\nUser '" << user.getUserName() << "' registered successfully!" << endl;
            return true;
        } else {
            cout << "\nUser already exists." << endl;
            return false;
        }
    }

    bool loginUser(string username) {
        if (users.find(username) != users.end()) {
            string password;
            cout << "Enter password: ";
            getline(cin, password);

            if (users[username].validatePassword(password)) {
                cout << "\nLogin successful!" << endl;
                return true;
            } else {
                cout << "\nIncorrect Password" << endl;
                return false;
            }
        } else {
            cout << "\nUser not found." << endl;
            return false;
        }
    }

    void addRestaurant(string name, string cuisine) {
        if (name.empty() || cuisine.empty()) {
            cout << "Restaurant name and cuisine cannot be empty." << endl;
            return;
        }
        restaurants[name] = Restaurant(name, cuisine);
        cout << "\nRestaurant '" << name << "' added successfully!" << endl;
    }

    void addMenuItem(string restaurantName, string item, double price) {
        if (restaurants.find(restaurantName) != restaurants.end()) {
            restaurants[restaurantName].addItem(item, price);
            cout << "Item '" << item << "' added to the menu of " << restaurantName << endl;
        } else {
            cout << "\nRestaurant not found." << endl;
        }
    }

    void viewRestaurantMenu(string restaurantName) {
        if (restaurants.find(restaurantName) != restaurants.end()) {
            restaurants[restaurantName].viewMenu();
        } else {
            cout << "\nRestaurant not found." << endl;
        }
    }

    void placeOrder(string username, string restaurantName, vector<string> items) {
        if (restaurants.find(restaurantName) != restaurants.end()) {
            double totalPrice = 0;
            bool invalidItem = false;

            for (const auto& item : items) {
                if (restaurants[restaurantName].menu.find(item) != restaurants[restaurantName].menu.end()) {
                    totalPrice += restaurants[restaurantName].menu[item];
                } else {
                    cout << "Item '" << item << "' not found in the menu of " << restaurantName << endl;
                    invalidItem = true;
                }
            }

            if (!invalidItem) {
                int orderId = orderIdCounter++;
                orders[orderId] = {orderId, restaurantName, items, totalPrice, "Placed"};
                cout << "Order placed successfully. Order ID: " << orderId << endl;

                // Add to user order history
                users[username].addToOrderHistory(orderId);
            } else {
                cout << "\nOrder could not be placed due to invalid items." << endl;
            }
        } else {
            cout << "Restaurant not found." << endl;
        }
    }

    void viewOrderHistory(string username) {
        if (users.find(username) != users.end()) {
            users[username].viewOrderHistory();
        } else {
            cout << "User not found." << endl;
        }
    }

    // Public method to get a reference to the User by username
    User& getUserByUsername(string username) {
        return users[username];
    }
};

int main() {
    FoodDeliverySystem system;

    User u1("Kashish", "k10", "abcd", "example@example.com", "1234567890", "Delhi");
    system.registerUser(u1);

    system.addRestaurant("Pizza Palace", "Italian");
    system.addMenuItem("Pizza Palace", "Margherita Pizza", 10);
    system.addMenuItem("Pizza Palace", "Garlic Bread", 5);

    vector<string> items = {"Margherita Pizza", "Garlic Bread"};
    system.placeOrder("k10", "Pizza Palace", items);

    system.viewOrderHistory("k10");

    // Accessing and updating user info
    User& user = system.getUserByUsername("k10");
    user.updateAddress("New Delhi, India");
    user.changePassword("newPassword");

    return 0;
}
