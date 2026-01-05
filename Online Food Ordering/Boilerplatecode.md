## JAVA
```
java
import java.util.*;

class FoodDeliverySystem {

    // Input data
    // restaurants: [restaurantId, name, cuisine, menu(item -> price)]
    // orders: [orderId, restaurantId, items, timestamp]

    List<List<Object>> restaurants;

    // System tracking
    Map<Integer, Map<String, Integer>> restaurantMenus; // restaurantId -> menu
    Map<Integer, String> restaurantNames;               // restaurantId -> name
    Map<Integer, String> restaurantCuisines;            // restaurantId -> cuisine

    Map<Integer, Integer> orderToRestaurant;             // orderId -> restaurantId
    Map<Integer, List<String>> orderItems;               // orderId -> items
    Map<Integer, Integer> orderTimestamp;                // orderId -> timestamp
    Map<Integer, Integer> orderTotalPrice;               // orderId -> total price
    Map<Integer, String> orderStatus;                    // orderId -> PLACED / CANCELLED

    Queue<Integer> orderQueue;                           // FIFO order processing

    int nextOrderId;

    public FoodDeliverySystem() {
        restaurantMenus = new HashMap<>();
        restaurantNames = new HashMap<>();
        restaurantCuisines = new HashMap<>();

        orderToRestaurant = new HashMap<>();
        orderItems = new HashMap<>();
        orderTimestamp = new HashMap<>();
        orderTotalPrice = new HashMap<>();
        orderStatus = new HashMap<>();

        orderQueue = new LinkedList<>();
        nextOrderId = 101;
    }

    // Add a new restaurant
    public void addRestaurant(int restaurantId, String name,
                              String cuisine, Map<String, Integer> menu) {
        // TODO
    }

    // Search restaurant by name or cuisine
    public List<String> searchRestaurant(String keyword) {
        // TODO
        return new ArrayList<>();
    }

    // Place an order
    public int placeOrder(int restaurantId, List<String> items, int timestamp) {
        // TODO
        return -1;
    }

    // Cancel order within 5 minutes
    public boolean cancelOrder(int orderId, int currentTime) {
        // TODO
        return false;
    }

    // View all orders
    public List<Integer> viewOrderHistory() {
        return new ArrayList<>(orderQueue);
    }
}
```
## Python
```
class FoodDeliverySystem:

    # restaurants: restaurant_id -> {name, cuisine, menu}
    # orders track orderId, items, timestamp, status, total price

    def __init__(self):
        self.restaurant_menus = {}
        self.restaurant_names = {}
        self.restaurant_cuisines = {}

        self.order_to_restaurant = {}
        self.order_items = {}
        self.order_timestamp = {}
        self.order_total_price = {}
        self.order_status = {}

        self.order_queue = []
        self.next_order_id = 101

    # Add a restaurant
    def add_restaurant(self, restaurant_id, name, cuisine, menu):
        # TODO
        pass

    # Search restaurant by name or cuisine
    def search_restaurant(self, keyword):
        # TODO
        return []

    # Place an order
    def place_order(self, restaurant_id, items, timestamp):
        # TODO
        return -1

    # Cancel order within 5 minutes
    def cancel_order(self, order_id, current_time):
        # TODO
        return False

    # View order history
    def view_order_history(self):
        return self.order_queue

```
## C++
```
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class FoodDeliverySystem {
private:
    // Restaurant data
    unordered_map<int, string> restaurantNames;
    unordered_map<int, string> restaurantCuisines;
    unordered_map<int, unordered_map<string, int>> restaurantMenus;

    // Order tracking
    unordered_map<int, int> orderToRestaurant;
    unordered_map<int, vector<string>> orderItems;
    unordered_map<int, int> orderTimestamp;
    unordered_map<int, int> orderTotalPrice;
    unordered_map<int, string> orderStatus;

    queue<int> orderQueue;   // FIFO order processing
    int nextOrderId;

public:
    FoodDeliverySystem() {
        nextOrderId = 101;
    }

    // Add a new restaurant
    void addRestaurant(int restaurantId, string name,
                       string cuisine,
                       unordered_map<string, int> menu) {
        // TODO
    }

    // Search restaurant by name or cuisine
    vector<string> searchRestaurant(string keyword) {
        // TODO
        return {};
    }

    // Place an order
    int placeOrder(int restaurantId, vector<string> items, int timestamp) {
        // TODO
        return -1;
    }

    // Cancel order within 5 minutes
    bool cancelOrder(int orderId, int currentTime) {
        // TODO
        return false;
    }

    // View order history
    vector<int> viewOrderHistory() {
        vector<int> history;
        queue<int> temp = orderQueue;
        while (!temp.empty()) {
            history.push_back(temp.front());
            temp.pop();
        }
        return history;
    }
};

int main() {
    return 0;
}
```




