import java.util.*;

class MenuItem {
    String name;
    double price;

    public MenuItem(String name, double price) {
        this.name = name;
        this.price = price;
    }
}

class Restaurant {
    String name, cuisine;
    List<MenuItem> menu;

    public Restaurant(String name, String cuisine) {
        this.name = name;
        this.cuisine = cuisine;
        this.menu = new ArrayList<>();
    }

    public void addMenuItem(String itemName, double price) {
        menu.add(new MenuItem(itemName, price));
    }
}

class Order {
    static int orderCounter = 100;
    int orderId;
    String restaurantName;
    List<MenuItem> items;
    double totalPrice;
    long timestamp;

    public Order(String restaurantName, List<MenuItem> items) {
        this.orderId = orderCounter++;
        this.restaurantName = restaurantName;
        this.items = new ArrayList<>(items);
        this.totalPrice = items.stream().mapToDouble(i -> i.price).sum();
        this.timestamp = System.currentTimeMillis();
    }
}

public class SonamKumari29_FoodDeliverySys {
    private static Map<String, Restaurant> restaurants = new HashMap<>();
    private static Queue<Order> orderQueue = new LinkedList<>();
    private static List<Order> orderHistory = new ArrayList<>();

    public static void addRestaurant(String name, String cuisine) {
        restaurants.put(name.toLowerCase(), new Restaurant(name, cuisine));
    }

    public static void addMenuItem(String restaurantName, String itemName, double price) {
        Restaurant res = restaurants.get(restaurantName.toLowerCase());
        if (res != null) res.addMenuItem(itemName, price);
    }

    public static void searchRestaurant(String query) {
        for (Restaurant res : restaurants.values()) {
            if (res.name.toLowerCase().contains(query.toLowerCase()) || 
                res.cuisine.toLowerCase().contains(query.toLowerCase())) {
                System.out.println("Found: " + res.name + " (" + res.cuisine + ")");
            }
        }
    }

    public static int placeOrder(String restaurantName, List<String> itemNames) {
        Restaurant res = restaurants.get(restaurantName.toLowerCase());
        if (res == null) {
            System.out.println("Restaurant not found!");
            return -1;
        }
        
        List<MenuItem> orderedItems = new ArrayList<>();
        for (String itemName : itemNames) {
            for (MenuItem item : res.menu) {
                if (item.name.equalsIgnoreCase(itemName)) {
                    orderedItems.add(item);
                }
            }
        }
        
        if (orderedItems.isEmpty()) {
            System.out.println("No valid items selected!");
            return -1;
        }
        
        Order newOrder = new Order(res.name, orderedItems);
        orderQueue.add(newOrder);
        orderHistory.add(newOrder);
        
        System.out.println("Order placed successfully! Order ID: " + newOrder.orderId);
        return newOrder.orderId;
    }

    public static void viewOrderHistory() {
        for (Order order : orderHistory) {
            System.out.println("Order ID: " + order.orderId + ", Restaurant: " + order.restaurantName + ", Total: $" + order.totalPrice);
        }
    }

    public static void cancelOrder(int orderId) {
        Iterator<Order> iterator = orderQueue.iterator();
        while (iterator.hasNext()) {
            Order order = iterator.next();
            long currentTime = System.currentTimeMillis();
            if (order.orderId == orderId && (currentTime - order.timestamp) <= 300000) {
                iterator.remove();
                System.out.println("Order " + orderId + " cancelled successfully!");
                return;
            }
        }
        System.out.println("Order cannot be cancelled (not found or time exceeded).");
    }

    public static void main(String[] args) {
        // Adding a restaurant
        addRestaurant("Pizza Palace", "Italian");
        addMenuItem("Pizza Palace", "Margherita Pizza", 10);
        addMenuItem("Pizza Palace", "Garlic Bread", 5);
        
        // Searching for restaurants
        searchRestaurant("Italian");
        
        // Placing an order
        List<String> items = Arrays.asList("Margherita Pizza", "Garlic Bread");
        int orderId = placeOrder("Pizza Palace", items);
        
        // Viewing order history
        viewOrderHistory();
        
        // Cancelling the order (if within 5 minutes)
        cancelOrder(orderId);
    }
}