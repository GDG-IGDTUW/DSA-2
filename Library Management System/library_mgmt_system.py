class LibraryManagementSystem:
    def __init__(self):
        self.books = {}  # book_id -> (title, author, available)

    def add_book(self, book_id, title, author):
        if book_id in self.books:
            print("Book ID already exists.")
            return
        self.books[book_id] = (title, author, True)
        print(f"Book '{title}' by {author} added successfully.")

    def borrow_book(self, book_id):
        if book_id not in self.books:
            print("-1")  # Book does not exist
            return
        title, author, available = self.books[book_id]
        if not available:
            print(f"Book '{title}' is currently unavailable.")
            return
        self.books[book_id] = (title, author, False)
        print(f"You have borrowed '{title}' by {author}.")

    def return_book(self, book_id):
        if book_id not in self.books:
            print("-1")  # Book does not exist
            return
        title, author, available = self.books[book_id]
        if available:
            print(f"Book '{title}' is already available.")
            return
        self.books[book_id] = (title, author, True)
        print(f"You have returned '{title}' by {author}.")

    def display_books(self):
        if not self.books:
            print("No books available in the library.")
            return
        for book_id, (title, author, available) in self.books.items():
            status = "Available" if available else "Borrowed"
            print(f"ID: {book_id}, Title: {title}, Author: {author}, Status: {status}")


def main():
    library = LibraryManagementSystem()
    
    while True:
        print("\n1. Add Book\n2. Borrow Book\n3. Return Book\n4. Display Books\n5. Exit")
        choice = input("Enter choice: ")
        
        if choice == "5":
            break
        
        if choice == "1":
            book_id = input("Enter book ID: ")
            title = input("Enter book title: ")
            author = input("Enter book author: ")
            library.add_book(book_id, title, author)
        
        elif choice == "2":
            book_id = input("Enter book ID: ")
            library.borrow_book(book_id)
        
        elif choice == "3":
            book_id = input("Enter book ID: ")
            library.return_book(book_id)
        
        elif choice == "4":
            library.display_books()
        
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()
