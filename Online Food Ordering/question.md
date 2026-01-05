Problem Statement

You are tasked with designing a Food Delivery System to manage restaurants, menus, customer orders, order processing, cancellations, and order history efficiently.
The platform hosts multiple restaurants offering different cuisines and menu items. Users can search for restaurants by name or cuisine, place orders containing multiple food items, and track their order history.
Orders are processed in the order they are placed. Each order is assigned a unique order ID, contains a timestamp, and can be cancelled only within 5 minutes of placing the order.

If a user attempts to place an order for a non-existent restaurant or invalid menu items, the order should not be placed.

Additionally, the system must be able to:

Track all past orders

Track orders by restaurant

Track order cancellation status

Enforce time-based cancellation rules

Each requirement must be implemented as a separate function.

Functional Requirements
1. Add Restaurant

Add a restaurant with:

restaurantId

name

cuisine

menu (item → price)

2. Search Restaurant

Search restaurants by name or cuisine

Partial string matching allowed

Return matching restaurant names

3. Place Order

Place an order from a selected restaurant

An order can contain multiple items

Generate a unique orderId

Calculate total price using the restaurant menu

Store order timestamp

Orders are processed in FIFO order

4. View Order History

Retrieve all past orders

Each order includes:

orderId

restaurant name

items ordered

total price

timestamp

status (PLACED / CANCELLED)

5. Cancel Order

An order can be cancelled only within 5 minutes (300 seconds) of placing it

If cancelled successfully, update order status

Return success or failure

Input Format
Initial Data
restaurants = [
  (restaurant_id, name, cuisine, [(item, price)])
]

Operations
ADD_RESTAURANT(restaurant_id, name, cuisine, menu)
SEARCH_RESTAURANT(keyword)
PLACE_ORDER(restaurant_id, [items], timestamp)
CANCEL_ORDER(order_id, current_time)
VIEW_ORDER_HISTORY()

Example Input
Restaurants
restaurants = [
  (1, "PizzaPalace", "Italian", [("Margherita", 250), ("GarlicBread", 120)]),
  (2, "SpiceHub", "Indian", [("PaneerTikka", 300), ("Naan", 40)])
]

Operations
SEARCH_RESTAURANT("Italian")
PLACE_ORDER(1, ["Margherita", "GarlicBread"], 100)
PLACE_ORDER(2, ["PaneerTikka"], 120)
CANCEL_ORDER(101, 250)
VIEW_ORDER_HISTORY()

Example Dry Run
Step	Operation	System State / Notes
1	SEARCH_RESTAURANT	Returns ["PizzaPalace"]
2	PLACE_ORDER	OrderID 101 → PizzaPalace, total = 370
3	PLACE_ORDER	OrderID 102 → SpiceHub, total = 300
4	CANCEL_ORDER	Order 101 cancelled (within 5 mins)
5	VIEW_ORDER_HISTORY	Shows both orders with statuses
Final Output
Order History
[
  {
    orderId: 101,
    restaurant: "PizzaPalace",
    items: ["Margherita", "GarlicBread"],
    totalPrice: 370,
    status: "CANCELLED"
  },
  {
    orderId: 102,
    restaurant: "SpiceHub",
    items: ["PaneerTikka"],
    totalPrice: 300,
    status: "PLACED"
  }
]

Data Tracked by the System
Restaurant Data

Restaurant details and menus

Order Data

Order ID

Items

Total price

Timestamp

Status

Order Processing

FIFO order queue

Constraints

1 ≤ Number of restaurants ≤ 100,000

1 ≤ Number of orders ≤ 1,000,000

1 ≤ Items per order ≤ 20

1 ≤ Price ≤ 10,000

Order cancellation window = 300 seconds

All operations must be time-efficient

Edge Cases

Multiple orders placed at the same timestamp

Search keyword matches both name and cuisine

Attempt to cancel order after 5 minutes → fail

Ordering item not present in restaurant menu → reject order

Viewing history when no orders exist