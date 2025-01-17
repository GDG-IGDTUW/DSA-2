#include <iostream>
#include <unordered_map>
#include <string>
#include <limits> // For numeric_limits
using namespace std;

// Structure to represent a Book
struct Book {
    string title;
    string author;
    bool availability;

    // Default constructor
    Book() : title(""), author(""), availability(true) {}

    // Constructor with parameters
    Book(string t, string a) : title(t), author(a), availability(true) {}
};

// Library Management System Class
class LibraryManagementSystem {
    unordered_map<string, Book> books; // Stores books with ISBN as the key

public:
    // Add a new book to the library
    void addBook(string title, string author, string isbn) {
        if (books.find(isbn) != books.end()) {
            cout << "Book with ISBN " << isbn << " already exists.\n";
        } else {
            books[isbn] = Book(title, author);
            cout << "Book '" << title << "' added successfully!\n";
        }
    }

    // Search for books by title or author (partial matching)
    void searchBook(string query) {
        bool found = false;
        // Use an iterator to loop through the unordered_map
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->second.title.find(query) != string::npos || it->second.author.find(query) != string::npos) {
                cout << "ISBN: " << it->first << ", Title: " << it->second.title
                     << ", Author: " << it->second.author
                     << ", Status: " << (it->second.availability ? "Available" : "Not Available") << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No books found matching the query '" << query << "'.\n";
        }
    }

    // Borrow a book if it is available
    void borrowBook(string isbn) {
        auto it = books.find(isbn);
        if (it != books.end()) {
            if (it->second.availability) {
                it->second.availability = false;
                cout << "Book '" << it->second.title << "' borrowed successfully.\n";
            } else {
                cout << "Book '" << it->second.title << "' is currently not available.\n";
            }
        } else {
            cout << "Book with ISBN " << isbn << " not found.\n";
        }
    }

    // Return a book and update its availability
    void returnBook(string isbn) {
        auto it = books.find(isbn);
        if (it != books.end()) {
            if (!it->second.availability) {
                it->second.availability = true;
                cout << "Book '" << it->second.title << "' returned successfully.\n";
            } else {
                cout << "Book '" << it->second.title << "' is already marked as available.\n";
            }
        } else {
            cout << "Book with ISBN " << isbn << " not found.\n";
        }
    }

    // Display all books in the library
    void viewAllBooks() {
        if (books.empty()) {
            cout << "No books available in the library.\n";
        } else {
            cout << "Library Collection:\n";
            // Use an iterator to loop through the unordered_map
            for (auto it = books.begin(); it != books.end(); ++it) {
                cout << "ISBN: " << it->first << ", Title: " << it->second.title
                     << ", Author: " << it->second.author
                     << ", Status: " << (it->second.availability ? "Available" : "Not Available") << "\n";
            }
        }
    }
};

// Main function with a menu-driven interface
int main() {
    LibraryManagementSystem library;
    int choice;
    string title, author, isbn, query;

    do {
        // Display the menu
        cout << "\nLibrary Management System:\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. View All Books\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear the input buffer to handle leftover newline characters
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: // Add Book
                cout << "Enter Title: ";
                getline(cin, title); // Read the full line for title
                cout << "Enter Author: ";
                getline(cin, author); // Read the full line for author
                cout << "Enter ISBN: ";
                cin >> isbn; // Read the ISBN
                library.addBook(title, author, isbn);
                break;

            case 2: // Search Book
                cout << "Enter Title or Author to search: ";
                getline(cin, query); // Read the search query
                library.searchBook(query);
                break;

            case 3: // Borrow Book
                cout << "Enter ISBN of the book to borrow: ";
                cin >> isbn;
                library.borrowBook(isbn);
                break;

            case 4: // Return Book
                cout << "Enter ISBN of the book to return: ";
                cin >> isbn;
                library.returnBook(isbn);
                break;

            case 5: // View All Books
                library.viewAllBooks();
                break;

            case 6: // Exit
                cout << "Exiting the Library Management System. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
