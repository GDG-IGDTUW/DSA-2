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
        contacts[contactId] = {name, phone, email};
    }

    // Remove contact
    void removeContact(int contactId) {
        // TODO
        contacts.erase(contactId);
    }

    // Update contact details
    void updateContact(int contactId, string name,
                       string phone, string email) {
        // TODO
        if (contacts.find(contactId) != contacts.end()) {
            contacts[contactId] = {name, phone, email};
        }
    }

    // Get contact
    vector<string> getContact(int contactId) {
    if (contacts.find(contactId) != contacts.end()) {
        return {
            to_string(contactId),
            contacts[contactId][0],
            contacts[contactId][1],
            contacts[contactId][2]
        };
    }
    return {};
}


    // Get all contacts
    vector<vector<string>> getAllContacts() {
    vector<vector<string>> allContacts;

    for (auto &p : contacts) {
        allContacts.push_back({
            to_string(p.first),
            p.second[0],
            p.second[1],
            p.second[2]
        });
    }

    return allContacts;
}
};


int main() {
    int n;
    cin>>n;
    ContactManagementSystem contact;
    while(n--){
        string s;
        cin>>s;
        if(s=="addContact"){
            int contactId;
            cin>>contactId;
            string name,phone,email;
            cin>>name>>phone>>email;
            contact.addContact(contactId, name, phone, email);
        }
        else if(s=="removeContact"){
            int contactId;
            cin>>contactId;
            contact.removeContact(contactId);
        }
        else if(s=="updateContact"){
            int contactId;
            cin>>contactId;
            string name,phone,email;
            cin>>name>>phone>>email;
            contact.updateContact(contactId, name, phone, email);
        }
        else if(s=="getContact"){
            int contactId;
            cin>>contactId;
            vector<string> result = contact.getContact(contactId);
            if(!result.empty()){
                cout << "[";
                for (int i = 0; i < result.size(); i++) {
                    cout << result[i];
                    if (i != result.size() - 1) cout << ", ";
                }
                cout << "]\n";
            } 
            else {
                cout<<"[]"<<endl;
            }
        }
        else if (s == "getAllContacts") {
    auto allContacts = contact.getAllContacts();

    cout << "[";
    for (int i = 0; i < allContacts.size(); i++) {
        cout << "[";
        for (int j = 0; j < allContacts[i].size(); j++) {
            cout << allContacts[i][j];
            if (j != allContacts[i].size() - 1)
                cout << ", ";
        }
        cout << "]";
        if (i != allContacts.size() - 1)
            cout << ", ";
    }
    cout << "]\n";
}
    }
    return 0;
}