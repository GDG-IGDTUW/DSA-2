
## C++
```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class ContactManagementSystem {
private:
    // contactId -> {name, phone, email}
    unordered_map<int, vector<string>> contacts;

public:
    ContactManagementSystem() {}

    // Add or update contact
    void addContact(int contactId, string name,
                    string phone, string email) {
        // TODO
    }

    // Remove contact
    void removeContact(int contactId) {
        // TODO
    }

    // Update contact details
    void updateContact(int contactId, string name,
                       string phone, string email) {
        // TODO
    }

    // Get contact
    vector<string> getContact(int contactId) {
        // TODO
        return {};
    }

    // Get all contacts
    vector<vector<string>> getAllContacts() {
        // TODO
        return {};
    }
};

int main() {
    return 0;
}

```

## Java
```java
import java.util.*;

class ContactManagementSystem {

    // contactId -> [name, phone, email]
    Map<Integer, List<String>> contacts;

    public ContactManagementSystem() {
        contacts = new HashMap<>();
    }

    // Add a new contact or update if exists
    public void addContact(int contactId, String name,
                           String phone, String email) {
        // TODO
    }

    // Remove contact completely
    public void removeContact(int contactId) {
        // TODO
    }

    // Update contact details
    public void updateContact(int contactId, String name,
                              String phone, String email) {
        // TODO
    }

    // Get single contact
    public List<Object> getContact(int contactId) {
        // TODO
        return new ArrayList<>();
    }

    // Get all contacts
    public List<List<Object>> getAllContacts() {
        // TODO
        return new ArrayList<>();
    }
}

```

## Python

```py
class ContactManagementSystem:

    # contacts: contact_id -> [name, phone, email]

    def __init__(self):
        self.contacts = {}

    # Add or update contact
    def addContact(self, contact_id, name, phone, email):
        # TODO
        pass

    # Remove contact
    def removeContact(self, contact_id):
        # TODO
        pass

    # Update contact details
    def updateContact(self, contact_id, name, phone, email):
        # TODO
        pass

    # Get a contact
    def getContact(self, contact_id):
        # TODO
        return []

    # Get all contacts
    def getAllContacts(self):
        # TODO
        return []

````
