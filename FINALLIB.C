#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_BOOKS 100

struct User {
    int id;
    char name[50];
};

struct Book {
    int bookId;
    char title[100];
    int floor;
    int isAvailable;
    int borrowerId; // ID of the user who borrowed the book (-1 if not borrowed)
};

struct User users[MAX_USERS];
struct Book books[MAX_BOOKS];
int numUsers = 0;
int numBooks = 0;

void addUser() {
    clrscr();
    if (numUsers < MAX_USERS) {
        struct User user;
        user.id = numUsers + 1;
        printf("Enter user name: ");
        scanf("%s", user.name);
        users[numUsers] = user;
        numUsers++;
        printf("User added successfully!\n");
    } else {
        printf("Maximum number of users reached!\n");
    }
}

void deleteUser() {
    int i,j ;
    int userId;
    int found = 0;
    clrscr();
    printf("Enter user ID to delete: ");
    scanf("%d", &userId);

    for ( i = 0; i < numUsers; i++) {
        if (users[i].id == userId) {
            found = 1;
            for (j = i; j < numUsers - 1; j++) {
                users[j] = users[j + 1];
            }
            numUsers--;
            printf("User deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("User not found!\n");
    }
}

void displayUsers() {
    int i ;
    clrscr();
    printf("List of Users:\n");
    for ( i = 0; i < numUsers; i++) {
        printf("ID: %d, Name: %s\n", users[i].id, users[i].name);
    }
}

void addBook() {
    clrscr();
    if (numBooks < MAX_BOOKS) {
        struct Book book;
        book.bookId = numBooks + 1;
        printf("Enter book title: ");
        scanf("%s", book.title);
        printf("Enter book floor: ");
        scanf("%d", &book.floor);
        book.isAvailable = 1;
        books[numBooks] = book;
        numBooks++;
        printf("Book added successfully!\n");
    } else {
        printf("Maximum number of books reached!\n");
    }
}

void displayBooks() {
    int i ;
    clrscr();
    printf("List of Books:\n");
    for (i= 0; i < numBooks; i++) {
        printf("ID: %d, Title: %s, Floor: %d, Available: %s\n", books[i].bookId, books[i].title, books[i].floor, books[i].isAvailable ? "Yes" : "No");
    }
}

void searchBooksOnFloor() {
    clrscr();
    int floor,i,found;
    printf("Enter floor to search for books: ");
    scanf("%d", &floor);

    printf("Books on Floor %d:\n", floor);
    found = 0;
    for (i = 0; i < numBooks; i++) {
        if (books[i].floor == floor) {
            found = 1;
            printf("ID: %d, Title: %s, Available: %s\n", books[i].bookId, books[i].title, books[i].isAvailable ? "Yes" : "No");
        }
    }

    if (!found) {
        printf("No books found on Floor %d.\n", floor);
    }
}


void borrowBook() {
    int userId,i,j,bookId;
    int foundUser = 0;
    int foundBook = 0;
    clrscr();
    printf("Enter user ID: ");
    scanf("%d", &userId);

    for (i = 0; i < numUsers; i++) {
        if (users[i].id == userId) {
            foundUser = 1;
            printf("Enter book ID to borrow: ");
            scanf("%d", &bookId);

            for (j = 0; j < numBooks; j++) {
                if (books[j].bookId == bookId) {
                    foundBook = 1;
                    if (books[j].isAvailable) {
                        books[j].isAvailable = 0;
                        books[j].borrowerId = userId;
                        printf("Book '%s' borrowed successfully!\n", books[j].title);
                    } else {
                        printf("Book '%s' is already borrowed!\n", books[j].title);
                    }
                    break;
                }
            }

            if (!foundBook) {
                printf("Book not found!\n");
            }

            break;
        }
    }

    if (!foundUser) {
        printf("User not found!\n");
    }
}

void checkBookAvailability() {
    int bookId,i;
    int found= 0;
    clrscr();
    printf("Enter book ID: ");
    scanf("%d", &bookId);

    for (i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookId) {
            found = 1;
            if (books[i].isAvailable) {
                printf("Book is available!\n");
            } else {
                printf("Book is not available. Borrowed by User ID %d.\n", books[i].borrowerId);
            }
            break;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }
}
void returnBook() {
    int userId, bookId,i,j;
    int foundUser = 0;
    int foundBook = 0;
    clrscr();
    printf("Enter user ID: ");
    scanf("%d", &userId);

    for ( i = 0; i < numUsers; i++) {
        if (users[i].id == userId) {
            foundUser = 1;
            printf("Enter book ID to return: ");
            scanf("%d", &bookId);

            for (j = 0; j < numBooks; j++) {
                if (books[j].bookId == bookId) {
                    foundBook = 1;
                    if (!books[j].isAvailable && books[j].borrowerId == userId) {
                        books[j].isAvailable = 1;
                        books[j].borrowerId = -1; // Reset borrower ID
                        printf("Book '%s' returned successfully!\n", books[j].title);
                    } else {
                        printf("You can't return this book. It's either not borrowed by you or already returned.\n");
                    }
                    break;
                }
            }

            if (!foundBook) {
                printf("Book not found!\n");
            }

            break;
        }
    }

    if (!foundUser) {
        printf("User not found!\n");
    }
}




int main() {
    int choice;
    clrscr();
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add User\n");
        printf("2. Delete User\n");
        printf("3. Display Users\n");
        printf("4. Add Book\n");
        printf("5. Display Books\n");
        printf("6. Borrow Book\n");
        printf("7. returnBook\n");
        printf("8. checkBookAvailability\n");
        printf("9. Search Books on Floor\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                deleteUser();
                break;
            case 3:
                displayUsers();
                break;
            case 4:
                addBook();
                break;
            case 5:
                displayBooks();
                break;
            case 6:
                borrowBook();
                break;
            case 7:
                returnBook(); // Add code to return a book
                break;
            case 8:
                checkBookAvailability();
                break;
            case 9:
                searchBooksOnFloor();
                break;
            case 10:
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}