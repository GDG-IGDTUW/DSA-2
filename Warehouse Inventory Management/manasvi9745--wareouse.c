#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100003  // Large prime number for hash table size

// Structure to store product details
typedef struct Product {
    int id;
    char name[21];
    int quantity;
    struct Product *next;  // For handling collisions
} Product;

Product *hashTable[TABLE_SIZE];

// Hash function
int hash(int id) {
    return id % TABLE_SIZE;
}

// Add or update a product
void addProduct(int id, char *name, int quantity) {
    int index = hash(id);
    Product *current = hashTable[index];
    
    while (current) {
        if (current->id == id) {
            current->quantity += quantity;
            return;
        }
        current = current->next;
    }
    
    Product *newProduct = (Product *)malloc(sizeof(Product));
    newProduct->id = id;
    strcpy(newProduct->name, name);
    newProduct->quantity = quantity;
    newProduct->next = hashTable[index];
    hashTable[index] = newProduct;
}

// Remove quantity from a product
void removeProduct(int id, int quantity) {
    int index = hash(id);
    Product *current = hashTable[index], *prev = NULL;
    
    while (current) {
        if (current->id == id) {
            current->quantity -= quantity;
            if (current->quantity <= 0) {  // Remove product
                if (prev) {
                    prev->next = current->next;
                } else {
                    hashTable[index] = current->next;
                }
                free(current);
            }
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Search for a product
void searchProduct(int id) {
    int index = hash(id);
    Product *current = hashTable[index];
    
    while (current) {
        if (current->id == id) {
            printf("%s %d\n", current->name, current->quantity);
            return;
        }
        current = current->next;
    }
    printf("Product not found\n");
}

int main() {
    int N, operation, id, quantity;
    char name[21];
    
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &operation);
        
        if (operation == 1) {
            scanf("%d %20s %d", &id, name, &quantity);
            addProduct(id, name, quantity);
        } else if (operation == 2) {
            scanf("%d %d", &id, &quantity);
            removeProduct(id, quantity);
        } else if (operation == 3) {
            scanf("%d", &id);
            searchProduct(id);
        }
    }
    
    return 0;
}
