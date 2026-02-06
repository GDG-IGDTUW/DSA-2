class ContactManagementSystem:

    # contacts: contact_id -> [name, phone, email]

    def __init__(self):
        self.contacts = {}

    # Add or update contact
    def addContact(self, contact_id, name, phone, email):
        self.contacts[contact_id] = [name, phone, email]

    # Remove contact
    def removeContact(self, contact_id):
        if contact_id in self.contacts:
            del self.contacts[contact_id]

    # Update contact details
    def updateContact(self, contact_id, name, phone, email):
        if contact_id in self.contacts:
            self.contacts[contact_id] = [name, phone, email]

    # Get a contact
    def getContact(self, contact_id):
        if contact_id in self.contacts:
            name, phone, email = self.contacts[contact_id]
            return [contact_id, name, phone, email]
        return []

    # Get all contacts
    def getAllContacts(self):
        result = []
        for cid, (name, phone, email) in self.contacts.items():
            result.append([cid, name, phone, email])
        return result


# testing

if __name__ == "__main__":
    cms = ContactManagementSystem()

    cms.addContact(101, "Alice", "9876543210", "alice@gmail.com")
    cms.addContact(102, "Bob", "9123456789", "bob@yahoo.com")
    cms.addContact(101, "Alice", "9999999999", "alice_new@gmail.com")

    print(cms.getContact(101))

    cms.removeContact(102)

    print(cms.getAllContacts())
    print(cms.getContact(102))
