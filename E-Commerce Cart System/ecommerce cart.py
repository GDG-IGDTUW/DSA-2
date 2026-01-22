class ECommerceCart:
    def __init__(self):
        # Initialize cart
        self.cart = {}
        self.n = int(input("Enter number of operations: "))
        while self.n > 0:
            s=input("Enter operation: ").strip().split()
            operation = s[0]
            if operation.lower() == "addproduct":
                productId = int(s[1])
                price = int(s[2])
                quantity = int(s[3])
                self.addProduct(productId, price, quantity)
            elif operation.lower() == "removeproduct":
                productId = int(s[1])
                self.removeProduct(productId)
            elif operation.lower() == "updatequantity":
                productId = int(s[1])
                quantity = int(s[2])
                self.updateQuantity(productId, quantity)
            elif operation.lower() == "gettotalprice":
                print("Total Price:",self.getTotalPrice())
            elif operation.lower() == "getcartitems":
                print("Your Cart Items:",self.getCartItems())
            self.n -= 1
            

    # Adds a product or updates quantity if already exists
    def addProduct(self, productId: int, price: int, quantity: int) -> None:
        # Implement add logic
        if productId in self.cart:
            self.cart[productId]["quantity"] += quantity
        else:
            self.cart[productId] = {"price": price, "quantity": quantity}

    # Removes product completely from the cart
    def removeProduct(self, productId: int) -> None:
        # Implement remove logic
        if productId in self.cart:
            del self.cart[productId]
        else:
            print("Product not found in cart.")

    # Updates quantity of a product
    def updateQuantity(self, productId: int, quantity: int) -> None:
        # Implement update logic
        if productId in self.cart:
            self.cart[productId]["quantity"] = quantity
        else:
            print("Product not found in cart.")

    # Returns total price of cart
    def getTotalPrice(self) -> int:
        # Implement total price calculation
        total = 0
        for item in self.cart.values():
            total += item["price"] * item["quantity"]
        return total

    # Returns all cart items
    def getCartItems(self):
        # Implement cart item retrieval
        if self.cart:
            return [
                {"productId": pid, "price": details["price"], "quantity": details["quantity"]}
                for pid, details in self.cart.items()
            ]
        return []


if __name__ == "__main__":
    cart = ECommerceCart() 

    # cart.addProduct(101, 50, 2)
    # cart.addProduct(102, 30, 1)
    # cart.addProduct(101, 50, 1)
    # print(cart.getTotalPrice())

    # cart.updateQuantity(102, 3)
    # cart.removeProduct(101)

    # print(cart.getCartItems())
