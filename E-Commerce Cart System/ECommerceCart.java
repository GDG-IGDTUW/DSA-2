package CollectionsFramework;

import java.util.*;

class ECommerceCart {

    class Product{
        int productId, quantity, price;
        Product(int productId, int price, int quantity){
            this.productId = productId;
            this.quantity = quantity;
            this.price = price;
        }

        @Override
        public String toString() {
            return "ProductId=" + productId + ", price=" + price + ", quantity=" + quantity;
        }

    }

    // Data structures to store cart information
    Map<Integer, Product> products;
    int totalPrice;

    public ECommerceCart() {
        // Initialize cart
        products = new HashMap<>();
        totalPrice = 0;
    }

    // Adds a product or updates quantity if already exists
    public void addProduct(int productId, int price, int quantity) {
        // Implement add logic
        if(products.containsKey(productId)){
            updateQuantity(productId, products.get(productId).quantity+quantity);
            return;
        }
        Product p = new Product(productId, price, quantity);
        totalPrice += (price*quantity);
        products.put(productId, p);
    }

    // Removes product completely from the cart
    public void removeProduct(int productId) {
        // Implement remove logic
        if(!products.containsKey(productId))
            return;
        Product p = products.get(productId);
        totalPrice -= (p.quantity*p.price);
        products.remove(productId);
    }

    // Updates quantity of a product
    public void updateQuantity(int productId, int newQty) {
        // Implement update logic
        if(!products.containsKey(productId))
            return;
        Product p = products.get(productId);
        int oldQty = p.quantity;
        int price = p.price;
        int priceDiff = (newQty*price)-(oldQty*price); //calculate the difference
        totalPrice +=priceDiff; //update the totalPrice of the cart
        p.quantity = newQty;
        products.put(productId, p); //update the cart
    }

    // Returns total price of cart
    public int getTotalPrice() {
        // Implement total price calculation
        return totalPrice;
    }

    // Returns all cart items
    public List<Product> getCartItems() {
        // Implement cart item retrieval
        return new ArrayList<>(products.values());
    }

    public static void main(String[] args) {
        ECommerceCart cart = new ECommerceCart();

        cart.addProduct(101, 50, 2);
        cart.addProduct(102, 30, 1);
        cart.addProduct(101, 50, 1);
        System.out.println(cart.getTotalPrice());

        cart.updateQuantity(102, 3);
        cart.removeProduct(101);

        System.out.println(cart.getCartItems());
    }
}
