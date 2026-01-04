## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class ECommerceCart {
private:
    // Data structures to store cart information

public:
    ECommerceCart() {
        // Initialize cart
    }

    // Adds a product or updates quantity if already exists
    void addProduct(int productId, int price, int quantity) {
        // Implement add logic
    }

    // Removes product completely from the cart
    void removeProduct(int productId) {
        // Implement remove logic
    }

    // Updates quantity of a product
    void updateQuantity(int productId, int quantity) {
        // Implement update logic
    }

    // Returns total price of cart
    int getTotalPrice() {
        // Implement total price calculation
        return 0;
    }

    // Returns all cart items
    vector<vector<int>> getCartItems() {
        // Implement cart item retrieval
        return {};
    }
};

int main() {
    ECommerceCart cart;

    cart.addProduct(101, 50, 2);
    cart.addProduct(102, 30, 1);
    cart.addProduct(101, 50, 1);
    cout << cart.getTotalPrice() << endl;

    cart.updateQuantity(102, 3);
    cart.removeProduct(101);

    auto items = cart.getCartItems();
    for (auto &item : items) {
        cout << "[" << item[0] << ", " << item[1] << ", " << item[2] << "] ";
    }

    return 0;
}
```

## Java
```java
import java.util.*;

class ECommerceCart {

    // Data structures to store cart information

    public ECommerceCart() {
        // Initialize cart
    }

    // Adds a product or updates quantity if already exists
    public void addProduct(int productId, int price, int quantity) {
        // Implement add logic
    }

    // Removes product completely from the cart
    public void removeProduct(int productId) {
        // Implement remove logic
    }

    // Updates quantity of a product
    public void updateQuantity(int productId, int quantity) {
        // Implement update logic
    }

    // Returns total price of cart
    public int getTotalPrice() {
        // Implement total price calculation
        return 0;
    }

    // Returns all cart items
    public List<List<Integer>> getCartItems() {
        // Implement cart item retrieval
        return new ArrayList<>();
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
````

## Python

```py
class ECommerceCart:
    def __init__(self):
        # Initialize cart
        pass

    # Adds a product or updates quantity if already exists
    def addProduct(self, productId: int, price: int, quantity: int) -> None:
        # Implement add logic
        pass

    # Removes product completely from the cart
    def removeProduct(self, productId: int) -> None:
        # Implement remove logic
        pass

    # Updates quantity of a product
    def updateQuantity(self, productId: int, quantity: int) -> None:
        # Implement update logic
        pass

    # Returns total price of cart
    def getTotalPrice(self) -> int:
        # Implement total price calculation
        return 0

    # Returns all cart items
    def getCartItems(self):
        # Implement cart item retrieval
        return []


if __name__ == "__main__":
    cart = ECommerceCart()

    cart.addProduct(101, 50, 2)
    cart.addProduct(102, 30, 1)
    cart.addProduct(101, 50, 1)
    print(cart.getTotalPrice())

    cart.updateQuantity(102, 3)
    cart.removeProduct(101)

    print(cart.getCartItems())

