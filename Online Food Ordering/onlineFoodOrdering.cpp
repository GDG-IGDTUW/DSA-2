#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class FoodDeliverySystem {
private:
    // restaurant data
    unordered_map<int, string> restaurantNames;
    unordered_map<int, string> restaurantCuisines;
    unordered_map<int, unordered_map<string, int>> restaurantMenus;

    // order tracking
    unordered_map<int, int> orderToRestaurant;
    unordered_map<int, vector<string>> orderItems;
    unordered_map<int, int> orderTimestamp;
    unordered_map<int, int> orderTotalPrice;
    unordered_map<int, string> orderStatus;

    queue<int> orderQueue;   // fifo order processing
    int nextOrderId;

public:
    FoodDeliverySystem() {
        nextOrderId = 101;
    }

    // add a new restaurant
    void addRestaurant(int restaurantId,string name,
                       string cuisine,
                       unordered_map<string,int> menu) {
        restaurantNames[restaurantId]=name;
        restaurantCuisines[restaurantId]=cuisine;
        restaurantMenus[restaurantId]=menu;
    }

    // search restaurant by name or cuisine
    vector<string> searchRestaurant(string keyword) {
        vector<string>res;
        for(auto &r:restaurantNames){
            int id=r.first;
            if(restaurantNames[id].find(keyword)!=string::npos||
               restaurantCuisines[id].find(keyword)!=string::npos){
                res.push_back(restaurantNames[id]);
            }
        }
        return res;
    }

    // place an order
    int placeOrder(int restaurantId,vector<string> items,int timestamp) {
        if(restaurantNames.find(restaurantId)==restaurantNames.end())
            return -1;

        int total=0;
        auto &menu=restaurantMenus[restaurantId];
        for(auto &item:items){
            if(menu.find(item)==menu.end())
                return -1;
            total+=menu[item];
        }

        int orderId=nextOrderId++;
        orderToRestaurant[orderId]=restaurantId;
        orderItems[orderId]=items;
        orderTimestamp[orderId]=timestamp;
        orderTotalPrice[orderId]=total;
        orderStatus[orderId]="PLACED";
        orderQueue.push(orderId);

        return orderId;
    }

    // cancel order within 5 minutes
    bool cancelOrder(int orderId,int currentTime) {
        if(orderStatus.find(orderId)==orderStatus.end())
            return false;

        if(orderStatus[orderId]=="PLACED"&&
           (currentTime-orderTimestamp[orderId])<=300){
            orderStatus[orderId]="CANCELLED";
            return true;
        }
        return false;
    }

    // view order history
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
