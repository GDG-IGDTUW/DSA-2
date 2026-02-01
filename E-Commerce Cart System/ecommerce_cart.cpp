#include <bits/stdc++.h>
using namespace std;

class ECommerceCart {
private:
    // productId -> {price, quantity}
    unordered_map<int, pair<int, int>> cart;
    int totalPrice;

public:
    ECommerceCart() {
        totalPrice = 0;
    }

    // Adds a product or updates quantity if already exists
    void addProduct(int productId, int price, int quantity) {
        if (quantity == 0) return;

        if (cart.count(productId)) {
            cart[productId].second += quantity;
            totalPrice += price * quantity;
        } else {
            cart[productId] = {price, quantity};
            totalPrice += price * quantity;
        }
    }

    // Removes product completely from the cart
    void removeProduct(int productId) {
        if (!cart.count(productId)) return;

        int price = cart[productId].first;
        int quantity = cart[productId].second;

        totalPrice -= price * quantity;
        cart.erase(productId);
    }

    // Updates quantity of a product
    void updateQuantity(int productId, int quantity) {
        if (!cart.count(productId)) return;

        int price = cart[productId].first;
        int oldQuantity = cart[productId].second;

        totalPrice -= price * oldQuantity;

        if (quantity == 0) {
            cart.erase(productId);
        } else {
            cart[productId].second = quantity;
            totalPrice += price * quantity;
        }
    }

    // Returns total price of cart
    int getTotalPrice() {
        return totalPrice;
    }

    // Returns all cart items
    vector<vector<int>> getCartItems() {
        vector<vector<int>> result;
        for (auto &it : cart) {
            result.push_back({
                it.first,
                it.second.first,
                it.second.second
            });
        }
        return result;
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
