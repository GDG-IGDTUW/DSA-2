Design a Contact Management System
1. Problem Statement

Design and implement a data structure for a Contact Management System that supports adding contacts, removing contacts, updating contact details, and retrieving stored contacts efficiently.

Each contact has:

a unique contactId

a name

a phone number

an email address

The system should efficiently handle multiple operations and always maintain accurate contact information.

You are required to design the contact management system and implement the required operations.

2. Operations

Implement the following functions:

addContact(contactId, name, phone, email)

Adds a new contact to the system.

If the contact already exists, update its details.

removeContact(contactId)

Removes the contact completely from the system.

If the contact does not exist, do nothing.

updateContact(contactId, name, phone, email)

Updates the details of an existing contact.

If the contact does not exist, do nothing.

getContact(contactId)

Returns the details of a contact in the format:

[contactId, name, phone, email]


If the contact does not exist, return [].

getAllContacts()

Returns a list of all contacts in the format:

[[contactId, name, phone, email], ...]


The order of contacts does not matter.

3. Input Format

The first line contains an integer Q, the number of operations.

The next Q lines each contain an operation in one of the following formats:

addContact contactId name phone email
removeContact contactId
updateContact contactId name phone email
getContact contactId
getAllContacts

4. Output Format

For every getContact operation, output the contact details or [].

For every getAllContacts operation, output the list of all contacts.

5. Examples
Example 1

INPUT

7
addContact 101 Alice 9876543210 alice@gmail.com
addContact 102 Bob 9123456789 bob@yahoo.com
addContact 101 Alice 9999999999 alice_new@gmail.com
getContact 101
removeContact 102
getAllContacts
getContact 102


OUTPUT

[101, Alice, 9999999999, alice_new@gmail.com]
[[101, Alice, 9999999999, alice_new@gmail.com]]
[]


Explanation

Contact 101 added and later updated.

Contact 102 added and then removed.

Only contact 101 remains in the system.

Fetching removed contact returns empty list.

Example 2

INPUT

5
addContact 201 John 8888888888 john@gmail.com
removeContact 201
getContact 201
addContact 202 Emma 7777777777 emma@gmail.com
getAllContacts


OUTPUT

[]
[[202, Emma, 7777777777, emma@gmail.com]]

6. Constraints

1 ≤ Q ≤ 10⁵

1 ≤ contactId ≤ 10⁹

Phone number and email are valid strings

All operations should be handled efficiently


Notes

The solution should support fast lookup and updates.

Use hash-based data structures for optimal performance.

Aim for O(1) time complexity per operation.

This problem tests data modeling, state management, and edge-case handling.
