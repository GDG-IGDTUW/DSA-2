#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_RESTAURANTS 100
#define MAX_ORDERS 100
#define MAX_MENU_ITEMS 10
#define ORDER_CANCEL_TIME 300 // 5 minutes in seconds

typedef struct {
    char itemName[50];
    float price;
} MenuItem;

typedef struct {
    char name[50];
    char cuisine[50];
    MenuItem menu[MAX_MENU_ITEMS];
    int menuSize;
} Restaurant;

typedef struct {
    int orderId;
    char restaurantName[50];
    MenuItem items[MAX_MENU_ITEMS];
    int itemCount;
    float totalPrice;
    time_t orderTime;
} Order;

Restaurant restaurants[MAX_RESTAURANTS];
Order orders[MAX_ORDERS];
int restaurantCount = 0;
int orderCount = 0;
int orderIdCounter = 100;

void addRestaurant(char *name, char *cuisine, MenuItem *menu, int menuSize) {
    if (restaurantCount < MAX_RESTAURANTS) {
        strcpy(restaurants[restaurantCount].name, name);
        strcpy(restaurants[restaurantCount].cuisine, cuisine);
        restaurants[restaurantCount].menuSize = menuSize;
        for (int i = 0; i < menuSize; i++) {
            restaurants[restaurantCount].menu[i] = menu[i];
        }
        restaurantCount++;
        printf("Restaurant added successfully.\n");
    } else {
        printf("Maximum restaurant limit reached.\n");
    }
}

void searchRestaurant(char *query) {
    int found = 0;
    for (int i = 0; i < restaurantCount; i++) {
        if (strstr(restaurants[i].name, query) || strstr(restaurants[i].cuisine, query)) {
            printf("Restaurant: %s | Cuisine: %s\n", restaurants[i].name, restaurants[i].cuisine);
            found = 1;
        }
    }
    if (!found) printf("No restaurants found.\n");
}

int placeOrder(char *restaurantName, MenuItem *items, int itemCount) {
    if (orderCount < MAX_ORDERS) {
        orders[orderCount].orderId = orderIdCounter++;
        strcpy(orders[orderCount].restaurantName, restaurantName);
        orders[orderCount].itemCount = itemCount;
        orders[orderCount].totalPrice = 0;
        orders[orderCount].orderTime = time(NULL);
        for (int i = 0; i < itemCount; i++) {
            orders[orderCount].items[i] = items[i];
            orders[orderCount].totalPrice += items[i].price;
        }
        printf("Order placed successfully! Order ID: %d\n", orders[orderCount].orderId);
        orderCount++;
        return orders[orderCount - 1].orderId;
    }
    printf("Order limit reached.\n");
    return -1;
}

void viewOrderHistory() {
    if (orderCount == 0) {
        printf("No orders placed yet.\n");
        return;
    }
    for (int i = 0; i < orderCount; i++) {
        printf("Order ID: %d | Restaurant: %s | Total: $%.2f\n", orders[i].orderId, orders[i].restaurantName, orders[i].totalPrice);
    }
}

void cancelOrder(int orderId) {
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            time_t currentTime = time(NULL);
            if (difftime(currentTime, orders[i].orderTime) <= ORDER_CANCEL_TIME) {
                printf("Order ID %d canceled successfully.\n", orderId);
                for (int j = i; j < orderCount - 1; j++) {
                    orders[j] = orders[j + 1];
                }
                orderCount--;
                return;
            } else {
                printf("Order cancellation period expired.\n");
                return;
            }
        }
    }
    printf("Order ID not found.\n");
}

int main() {
    MenuItem menu1[] = {{"Margherita Pizza", 10.0}, {"Garlic Bread", 5.0}};
    addRestaurant("Pizza Palace", "Italian", menu1, 2);
    
    MenuItem orderItems[] = {{"Margherita Pizza", 10.0}, {"Garlic Bread", 5.0}};
    int orderId = placeOrder("Pizza Palace", orderItems, 2);
    
    viewOrderHistory();
    cancelOrder(orderId);
    
    return 0;
}
