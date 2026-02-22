import java.util.*;

class FoodDeliverySystem {

    // Restaurant Data
    private Map<Integer, Map<String, Integer>> restaurantMenus;
    private Map<Integer, String> restaurantNames;
    private Map<Integer, String> restaurantCuisines;

    // Order Data
    private Map<Integer, Integer> orderToRestaurant;
    private Map<Integer, List<String>> orderItems;
    private Map<Integer, Integer> orderTimestamp;
    private Map<Integer, Integer> orderTotalPrice;
    private Map<Integer, String> orderStatus;

    // FIFO processing queue
    private Queue<Integer> orderQueue;

    private int nextOrderId;

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

    // ✅ Add Restaurant
    public void addRestaurant(int restaurantId, String name,
                              String cuisine, Map<String, Integer> menu) {

        restaurantNames.put(restaurantId, name);
        restaurantCuisines.put(restaurantId, cuisine);
        restaurantMenus.put(restaurantId, new HashMap<>(menu));
    }

    // ✅ Search Restaurant (Partial match)
    public List<String> searchRestaurant(String keyword) {

        List<String> result = new ArrayList<>();
        keyword = keyword.toLowerCase();

        for (int restaurantId : restaurantNames.keySet()) {

            String name = restaurantNames.get(restaurantId).toLowerCase();
            String cuisine = restaurantCuisines.get(restaurantId).toLowerCase();

            if (name.contains(keyword) || cuisine.contains(keyword)) {
                result.add(restaurantNames.get(restaurantId));
            }
        }

        return result;
    }

    // ✅ Place Order
    public int placeOrder(int restaurantId, List<String> items, int timestamp) {

        // Restaurant must exist
        if (!restaurantMenus.containsKey(restaurantId)) {
            return -1;
        }

        Map<String, Integer> menu = restaurantMenus.get(restaurantId);
        int totalPrice = 0;

        // Validate items
        for (String item : items) {
            if (!menu.containsKey(item)) {
                return -1;  // Invalid item → reject order
            }
            totalPrice += menu.get(item);
        }

        int orderId = nextOrderId++;

        orderToRestaurant.put(orderId, restaurantId);
        orderItems.put(orderId, new ArrayList<>(items));
        orderTimestamp.put(orderId, timestamp);
        orderTotalPrice.put(orderId, totalPrice);
        orderStatus.put(orderId, "PLACED");

        orderQueue.offer(orderId);

        return orderId;
    }

    // ✅ Cancel Order (within 5 minutes)
    public boolean cancelOrder(int orderId, int currentTime) {

        if (!orderStatus.containsKey(orderId))
            return false;

        if (orderStatus.get(orderId).equals("CANCELLED"))
            return false;

        int orderTime = orderTimestamp.get(orderId);

        if (currentTime - orderTime <= 300) {
            orderStatus.put(orderId, "CANCELLED");
            return true;
        }

        return false;
    }

    // ✅ View Order History
    public List<Map<String, Object>> viewOrderHistory() {

        List<Map<String, Object>> history = new ArrayList<>();

        for (int orderId : orderQueue) {

            Map<String, Object> orderDetails = new HashMap<>();

            orderDetails.put("orderId", orderId);
            orderDetails.put("restaurant",
                    restaurantNames.get(orderToRestaurant.get(orderId)));
            orderDetails.put("items", orderItems.get(orderId));
            orderDetails.put("totalPrice", orderTotalPrice.get(orderId));
            orderDetails.put("timestamp", orderTimestamp.get(orderId));
            orderDetails.put("status", orderStatus.get(orderId));

            history.add(orderDetails);
        }

        return history;
    }
}
