import java.util.*;
class SonamKumari29_warehouse {
    // Product class to represent a single product
    static class Product {
        String name;
        int quantity;
        Product(String name, int quantity) {
            this.name = name;
            this.quantity = quantity;
        }
    }
    static class WarehouseInventory {
        private Map<Integer, Product> inventory;
        WarehouseInventory() {
            inventory = new HashMap<>();
        }
        public void addProduct(int id, String name, int quantity) {
            if (inventory.containsKey(id)) {
                Product product = inventory.get(id);
                product.quantity += quantity; // Update the quantity
            } else {
                Product newProduct = new Product(name, quantity);
                inventory.put(id, newProduct); // Add new product
            }
        }
        public void removeProduct(int id, int quantity) {
            if (!inventory.containsKey(id)) {
                System.out.println("Product not found");
                return;
            }
            Product product = inventory.get(id);
            product.quantity -= quantity;
            if (product.quantity <= 0) {
                inventory.remove(id); // Remove product if quantity is zero or less
            }
        }
        public String searchProduct(int id) {
            if (!inventory.containsKey(id)) {
                return "Product not found";
            }

            Product product = inventory.get(id);
            return product.name + " " + product.quantity;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        WarehouseInventory warehouse = new WarehouseInventory();
        int n = sc.nextInt();

        for (int i = 0; i < n; i++) {
            int operation = sc.nextInt();

            if (operation == 1) { // Add a product
                int id = sc.nextInt();
                String name = sc.next();
                int quantity = sc.nextInt();
                warehouse.addProduct(id, name, quantity);

            } else if (operation == 2) { // Remove a product
                int id = sc.nextInt();
                int quantity = sc.nextInt();
                warehouse.removeProduct(id, quantity);

            } else if (operation == 3) { // Search a product
                int id = sc.nextInt();
                System.out.println(warehouse.searchProduct(id));
            }
        }
        sc.close();
    }
}
