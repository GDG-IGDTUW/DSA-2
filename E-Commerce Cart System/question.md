# Design an E-commerce Cart System

## 1. Problem Statement

Design and implement a data structure for an **E-commerce Cart System** that supports adding products, removing products, updating quantities, and retrieving the total price of items in the cart.

Each product has:
- a unique `productId`
- a `price` per unit

The cart should efficiently handle multiple operations and always maintain correct quantities and total cost.

You are required to design the cart system and implement the required operations.

---

## 2. Operations

Implement the following functions:

1. **addProduct(productId, price, quantity)**  
   - Adds a product to the cart.
   - If the product already exists, increase its quantity.

2. **removeProduct(productId)**  
   - Removes the product completely from the cart.
   - If the product does not exist, do nothing.

3. **updateQuantity(productId, quantity)**  
   - Updates the quantity of an existing product.
   - If the quantity becomes `0`, remove the product from the cart.
   - If the product does not exist, do nothing.

4. **getTotalPrice()**  
   - Returns the total price of all products currently in the cart.

5. **getCartItems()**  
   - Returns a list of all items in the cart in the format:  
     `[productId, price, quantity]`
   - The order of items does not matter.

---

## 3. Input Format

- The first line contains an integer `Q`, the number of operations.
- The next `Q` lines each contain an operation in one of the following formats:

addProduct productId price quantity

removeProduct productId

updateQuantity productId quantity

getTotalPrice

getCartItems

---


## 4. Output Format

- For every `getTotalPrice` operation, output a single integer representing the total price.
- For every `getCartItems` operation, output the cart items as a list of lists.

---

## 5. Examples

### Example 1

**INPUT**

7

addProduct 101 50 2

addProduct 102 30 1

addProduct 101 50 1

getTotalPrice

updateQuantity 102 3

removeProduct 101

getCartItems




**OUTPUT**

180

[[102, 30, 3]]



**Explanation**
- Product 101 total quantity = 3 → cost = 150
- Product 102 quantity updated to 3 → cost = 90
- Total price before removal = 150 + 30 = 180
- Product 101 removed
- Cart contains only product 102

---

### Example 2

#### INPUT

5

addProduct 201 100 1

updateQuantity 201 0

getTotalPrice

addProduct 202 40 2

getCartItems



**OUTPUT**

0

[[202, 40, 2]]


---

## 6. Constraints

- `1 ≤ Q ≤ 10^5`
- `1 ≤ productId ≤ 10^9`
- `1 ≤ price ≤ 10^4`
- `0 ≤ quantity ≤ 10^4`
- All operations should be handled efficiently.

---

## Notes

- The solution should support **fast lookup and updates**.
- Aim for optimal time complexity for each operation.
- This problem tests understanding of **hash-based data structures**, state maintenance, and edge-case handling.
