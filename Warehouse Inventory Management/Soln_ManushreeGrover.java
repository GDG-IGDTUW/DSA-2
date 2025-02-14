package Snowscript;
import java.util.*;

class Product {
    String name;
    int quantity;

    public Product(String name, int quantity) {
        this.name = name;
        this.quantity = quantity;
    }
}

class WarehouseInventory {
    private Map<Integer, Product> inventory;

    public WarehouseInventory() {
        inventory = new HashMap<>();
    }

    // Add or update a product in the inventory
    public void addProduct(int id, String name, int quantity) {
        // To be implemented
    	if(inventory.containsKey(id)) {    // if product already present
    		inventory.get(id).quantity++;
    	}
    	else {
    		Product newProd=new Product(name,quantity);  // adding new product
    		inventory.put(id,newProd);
    	}
    }

    // Remove a product or reduce its quantity
    public void removeProduct(int id, int quantity) {
        // To be implemented
    	if(!inventory.containsKey(id)) {   
    		System.out.println("No such product available");
    		return;
    	}
    	
    	inventory.get(id).quantity=inventory.get(id).quantity-quantity;
    	if(inventory.get(id).quantity<=0) {       // remove if quantity becomes 0 or -ve
    		inventory.remove(id);
    	}
    }

    // Search for a product by ID
    public String searchProduct(int id) {
        // To be implemented
    	String ans="";
    	if(inventory.containsKey(id)) {
    		ans=ans+inventory.get(id).name+" "+inventory.get(id).quantity;
    	}
    	
    	if(ans.length()==0) {
    		return "Product not found";
    	}
        return ans;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        WarehouseInventory warehouse = new WarehouseInventory();

        int n = sc.nextInt();
        sc.nextLine(); // Consume the newline character

        for (int i = 0; i < n; i++) {
            String[] operation = sc.nextLine().split(" ");
            int opType = Integer.parseInt(operation[0]);

            if (opType == 1) { // Add a product
                int id = Integer.parseInt(operation[1]);
                String name = operation[2];
                int quantity = Integer.parseInt(operation[3]);
                warehouse.addProduct(id, name, quantity);

            } else if (opType == 2) { // Remove a product
                int id = Integer.parseInt(operation[1]);
                int quantity = Integer.parseInt(operation[2]);
                warehouse.removeProduct(id, quantity);

            } else if (opType == 3) { // Search a product
                int id = Integer.parseInt(operation[1]);
                System.out.println(warehouse.searchProduct(id));
            }
        }

        sc.close();
    }
}



