class FoodDeliverySystem:

    def __init__(self):
        # Restaurant Data
        self.restaurant_menus = {}
        self.restaurant_names = {}
        self.restaurant_cuisines = {}

        # Order Data
        self.order_to_restaurant = {}
        self.order_items = {}
        self.order_timestamp = {}
        self.order_total_price = {}
        self.order_status = {}

        # FIFO Order Tracking
        self.order_queue = []
        self.next_order_id = 101

    # -----------------------------
    # Add Restaurant
    # -----------------------------
    def add_restaurant(self, restaurant_id, name, cuisine, menu):
        if restaurant_id in self.restaurant_menus:
            return  # already exists

        self.restaurant_names[restaurant_id] = name
        self.restaurant_cuisines[restaurant_id] = cuisine

        # Convert menu list to dictionary
        menu_dict = {}
        for item, price in menu:
            menu_dict[item] = price

        self.restaurant_menus[restaurant_id] = menu_dict

    # -----------------------------
    # Search Restaurant
    # -----------------------------
    def search_restaurant(self, keyword):
        keyword = keyword.lower()
        result = []

        for rid in self.restaurant_names:
            name = self.restaurant_names[rid].lower()
            cuisine = self.restaurant_cuisines[rid].lower()

            if keyword in name or keyword in cuisine:
                result.append(self.restaurant_names[rid])

        return result

    # -----------------------------
    # Place Order
    # -----------------------------
    def place_order(self, restaurant_id, items, timestamp):

        # Validate restaurant exists
        if restaurant_id not in self.restaurant_menus:
            return -1

        menu = self.restaurant_menus[restaurant_id]
        total_price = 0

        # Validate items
        for item in items:
            if item not in menu:
                return -1
            total_price += menu[item]

        # Generate order ID
        order_id = self.next_order_id
        self.next_order_id += 1

        # Store order details
        self.order_to_restaurant[order_id] = restaurant_id
        self.order_items[order_id] = items
        self.order_timestamp[order_id] = timestamp
        self.order_total_price[order_id] = total_price
        self.order_status[order_id] = "PLACED"

        # Add to FIFO queue
        self.order_queue.append(order_id)

        return order_id

    # -----------------------------
    # Cancel Order (within 5 minutes)
    # -----------------------------
    def cancel_order(self, order_id, current_time):

        # Check order exists
        if order_id not in self.order_status:
            return False

        # Already cancelled
        if self.order_status[order_id] == "CANCELLED":
            return False

        order_time = self.order_timestamp[order_id]

        # Check 5-minute rule (300 seconds)
        if current_time - order_time > 300:
            return False

        # Cancel order
        self.order_status[order_id] = "CANCELLED"
        return True

    # -----------------------------
    # View Order History
    # -----------------------------
    def view_order_history(self):

        history = []

        for order_id in self.order_queue:
            rid = self.order_to_restaurant[order_id]

            history.append({
                "orderId": order_id,
                "restaurant": self.restaurant_names[rid],
                "items": self.order_items[order_id],
                "totalPrice": self.order_total_price[order_id],
                "timestamp": self.order_timestamp[order_id],
                "status": self.order_status[order_id]
            })

        return history
