
##  C++ Implementation


## C++
```cpp
#include <bits/stdc++.h>
using namespace std;

class ContactManagementSystem {
private:
    // contactId -> {name, phone, email}
    unordered_map<int, vector<string>> contacts;

public:
    ContactManagementSystem() {}

    void addContact(int contactId, string name, string phone, string email) {
        contacts[contactId] = {name, phone, email};
    }

    void removeContact(int contactId) {
        contacts.erase(contactId);
    }

    void updateContact(int contactId, string name, string phone, string email) {
        if (contacts.count(contactId)) {
            contacts[contactId] = {name, phone, email};
        }
    }

    vector<string> getContact(int contactId) {
        if (contacts.count(contactId)) {
            auto &c = contacts[contactId];
            return {to_string(contactId), c[0], c[1], c[2]};
        }
        return {};
    }

    vector<vector<string>> getAllContacts() {
        vector<vector<string>> res;
        for (auto &it : contacts) {
            res.push_back({
                to_string(it.first),
                it.second[0],
                it.second[1],
                it.second[2]
            });
        }
        return res;
    }
};

int main() {
    ContactManagementSystem cms;

    cms.addContact(101, "Alice", "9876543210", "alice@gmail.com");
    cms.addContact(102, "Bob", "9123456789", "bob@yahoo.com");
    cms.addContact(101, "Alice", "9999999999", "alice_new@gmail.com");

    auto c = cms.getContact(101);
    if (!c.empty()) {
        cout << "[" << c[0] << ", " << c[1] << ", " << c[2] << ", " << c[3] << "]\n";
    }

    cms.removeContact(102);

    auto all = cms.getAllContacts();
    cout << "[";
    for (auto &x : all) {
        cout << "[" << x[0] << ", " << x[1] << ", " << x[2] << ", " << x[3] << "] ";
    }
    cout << "]\n";

    auto c2 = cms.getContact(102);
    if (c2.empty()) cout << "[]\n";

    return 0;
}
```

## Java
```java
import java.util.*;

class ContactManagementSystem {

    // contactId -> [name, phone, email]
    private Map<Integer, List<String>> contacts;

    public ContactManagementSystem() {
        contacts = new HashMap<>();
    }

    public void addContact(int contactId, String name, String phone, String email) {
        contacts.put(contactId, Arrays.asList(name, phone, email));
    }

    public void removeContact(int contactId) {
        contacts.remove(contactId);
    }

    public void updateContact(int contactId, String name, String phone, String email) {
        if (contacts.containsKey(contactId)) {
            contacts.put(contactId, Arrays.asList(name, phone, email));
        }
    }

    public List<String> getContact(int contactId) {
        if (contacts.containsKey(contactId)) {
            List<String> c = contacts.get(contactId);
            return Arrays.asList(
                String.valueOf(contactId),
                c.get(0),
                c.get(1),
                c.get(2)
            );
        }
        return new ArrayList<>();
    }

    public List<List<String>> getAllContacts() {
        List<List<String>> res = new ArrayList<>();
        for (Map.Entry<Integer, List<String>> e : contacts.entrySet()) {
            res.add(Arrays.asList(
                String.valueOf(e.getKey()),
                e.getValue().get(0),
                e.getValue().get(1),
                e.getValue().get(2)
            ));
        }
        return res;
    }

    public static void main(String[] args) {
        ContactManagementSystem cms = new ContactManagementSystem();

        cms.addContact(101, "Alice", "9876543210", "alice@gmail.com");
        cms.addContact(102, "Bob", "9123456789", "bob@yahoo.com");
        cms.addContact(101, "Alice", "9999999999", "alice_new@gmail.com");

        System.out.println(cms.getContact(101));
        cms.removeContact(102);
        System.out.println(cms.getAllContacts());
        System.out.println(cms.getContact(102));
    }
}
```

## Python

```py
class ContactManagementSystem:
    def __init__(self):
        # contactId -> [name, phone, email]
        self.contacts = {}

    def addContact(self, contactId: int, name: str, phone: str, email: str) -> None:
        self.contacts[contactId] = [name, phone, email]

    def removeContact(self, contactId: int) -> None:
        self.contacts.pop(contactId, None)

    def updateContact(self, contactId: int, name: str, phone: str, email: str) -> None:
        if contactId in self.contacts:
            self.contacts[contactId] = [name, phone, email]

    def getContact(self, contactId: int):
        if contactId in self.contacts:
            c = self.contacts[contactId]
            return [contactId, c[0], c[1], c[2]]
        return []

    def getAllContacts(self):
        return [
            [cid, v[0], v[1], v[2]]
            for cid, v in self.contacts.items()
        ]


if __name__ == "__main__":
    cms = ContactManagementSystem()

    cms.addContact(101, "Alice", "9876543210", "alice@gmail.com")
    cms.addContact(102, "Bob", "9123456789", "bob@yahoo.com")
    cms.addContact(101, "Alice", "9999999999", "alice_new@gmail.com")

    print(cms.getContact(101))
    cms.removeContact(102)
    print(cms.getAllContacts())
    print(cms.getContact(102))
````
