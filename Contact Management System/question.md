#  Contact Management System

## Problem Statement

Design and implement a data structure for a **Contact Management System** that supports adding contacts, removing contacts, updating contact details, and retrieving stored contacts efficiently.

Each contact has:
- a unique `contactId`
- a `name`
- a `phone number`
- an `email address`

The system should efficiently handle multiple operations and always maintain accurate contact information.

---

##  Operations

Implement the following functions:

### 1. `addContact(contactId, name, phone, email)`
- Adds a new contact to the system.
- If the contact already exists, update its details.

### 2. `removeContact(contactId)`
- Removes the contact completely from the system.
- If the contact does not exist, do nothing.

### 3. `updateContact(contactId, name, phone, email)`
- Updates the details of an existing contact.
- If the contact does not exist, do nothing.

### 4. `getContact(contactId)`
- Returns the contact details in the format:
[contactId, name, phone, email]
- If the contact does not exist, return:
 []

### 5. `getAllContacts()`
- Returns a list of all contacts in the format:
  [[contactId, name, phone, email], ...]

- The order of contacts does not matter.

---

##  Input Format

- The first line contains an integer `Q`, the number of operations.
- The next `Q` lines contain one of the following commands:
addContact contactId name phone email
removeContact contactId
updateContact contactId name phone email
getContact contactId
getAllContacts


---

##  Output Format

- For every `getContact` operation, output the contact details or `[]`.
- For every `getAllContacts` operation, output the list of all contacts.

---

##  Examples

### Example 1
#### INPUT
7
addContact 101 Alice 9876543210 alice@gmail.com

addContact 102 Bob 9123456789 bob@yahoo.com

addContact 101 Alice 9999999999 alice_new@gmail.com

getContact 101
removeContact 102
getAllContacts
getContact 102


#### OUTPUT
[101, Alice, 9999999999, alice_new@gmail.com]
[[101, Alice, 9999999999, alice_new@gmail.com]]
[]

#### Explanation
- Contact `101` is added and later updated.
- Contact `102` is added and then removed.
- Only contact `101` remains in the system.
- Fetching a removed contact returns an empty list.

---

### Example 2

#### INPUT
5
addContact 201 John 8888888888 john@gmail.com

removeContact 201
getContact 201
addContact 202 Emma 7777777777 emma@gmail.com

getAllContacts

#### OUTPUT
[]
[[202, Emma, 7777777777, emma@gmail.com]]

---

## Constraints

- `1 ≤ Q ≤ 10^5`
- `1 ≤ contactId ≤ 10^9`
- Phone number and email are valid strings
- All operations should be handled efficiently



---

##  Key Takeaways

- Demonstrates effective **data modeling**
- Tests understanding of **hash maps**
- Ensures clean **state management**
- Suitable for **coding interviews and system design rounds**




