#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

typedef struct {
    char title[100];
    char author[100];
    char ISBN[20];
    int available;
} Book;

Book library[MAX_BOOKS];
int bookCount = 0;

void addBook(char *title, char *author, char *ISBN) {
    if (bookCount < MAX_BOOKS) {
        strcpy(library[bookCount].title, title);
        strcpy(library[bookCount].author, author);
        strcpy(library[bookCount].ISBN, ISBN);
        library[bookCount].available = 1;
        bookCount++;
        printf("Book '%s' added successfully!\n", title);
    } else {
        printf("Library is full. Cannot add more books.\n");
    }
}

void searchBook(char *query) {
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(library[i].title, query) || strstr(library[i].author, query)) {
            printf("Title: %s | Author: %s | ISBN: %s | Status: %s\n",
                   library[i].title, library[i].author, library[i].ISBN,
                   library[i].available ? "Available" : "Not Available");
            found = 1;
        }
    }
    if (!found) printf("No books found.\n");
}

void borrowBook(char *ISBN) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].ISBN, ISBN) == 0) {
            if (library[i].available) {
                library[i].available = 0;
                printf("You have borrowed '%s'.\n", library[i].title);
            } else {
                printf("Book is currently not available.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void returnBook(char *ISBN) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].ISBN, ISBN) == 0) {
            if (!library[i].available) {
                library[i].available = 1;
                printf("You have returned '%s'.\n", library[i].title);
            } else {
                printf("Book was not borrowed.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void viewAllBooks() {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        printf("Title: %s | Author: %s | ISBN: %s | Status: %s\n",
               library[i].title, library[i].author, library[i].ISBN,
               library[i].available ? "Available" : "Not Available");
    }
}

int main() {
    addBook("Harry Potter", "J.K. Rowling", "1234");
    addBook("The Hobbit", "J.R.R. Tolkien", "5678");
    
    viewAllBooks();
    
    borrowBook("1234");
    viewAllBooks();
    
    returnBook("1234");
    viewAllBooks();
    
    return 0;
}
