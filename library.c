#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_USERS 100

struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} users[MAX_USERS] = {0};
int numUsers = 0;
int choice, searchId, searchId1, n, m;
struct reader {
    int id;                 // id stores reader id
    char name[20];          // name stores reader's name
    int borrowedBooks[3];   // array to store the IDs of borrowed books
    int numBooksBorrowed;   // number of books currently borrowed
} rdr[10] = {0};              //rdr array is initialised with structure of reader

struct book                  //structure book defined
{
    int id;                 //id here stores book id
    char name[30];          //name stores name of the book
    char author[20];        //author stores name of the author
    char avbl;              //avbl stores availability of the book as y/n
    int rid;                //rid stores reader id having the book
} bk[20] = {0};

void registerUser(const char *username, const char *password) {
    if (numUsers >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    strncpy(users[numUsers].username, username, MAX_USERNAME_LENGTH);
    strncpy(users[numUsers].password, password, MAX_PASSWORD_LENGTH);
    numUsers++;
    printf("User registered successfully.\n");
}

int findUser(const char *username, const char *password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }

    return -1;
}

void saveUsersToFile() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "Username: %s\n", users[i].username);
        fprintf(file, "Password: %s\n\n", users[i].password);
    }

    fclose(file);
    printf("users data saved to file.\n");
}

int loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        return 0;
    }

    numUsers = 0;
    while (!feof(file) && numUsers < MAX_USERS) {
        fscanf(file, "Username: %s\n", users[numUsers].username);
        fscanf(file, "Password: %s\n", users[numUsers].password);
        numUsers++;
    }
    fclose(file);
    return numUsers;
}


int generateBookID() {
    int maxID = 0;

    for (int i = 0; i < 20; i++) {
        if (bk[i].id != 0 && bk[i].id > maxID) {
            maxID = bk[i].id;
        }
    }

    return maxID + 1;
}


int generateReaderID() {
    int maxID = 0;

    for (int i = 0; i < 10; i++) {
        if (rdr[i].id != 0 && rdr[i].id > maxID) {
            maxID = rdr[i].id;
        }
    }

    return maxID + 1;
}

void saveBooksToFile() {
    FILE *file = fopen("booklist.txt", "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < 20; i++) {
        if (bk[i].id != 0)    // Check if the book entry is valid
        {
            fprintf(file, "Book ID: %d\n", bk[i].id);
            fprintf(file, "Name: %s\n", bk[i].name);
            fprintf(file, "Author: %s\n", bk[i].author);
            fprintf(file, "Availability: %c\n", bk[i].avbl);
            fprintf(file, "Reader ID: %d\n\n", bk[i].rid);
        }
    }

    fclose(file);
    printf("Book list saved successfully.\n\n");
}

void saveReadersToFile() {
    FILE *file = fopen("readers.txt", "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < 10; i++) {
        if (rdr[i].id != 0) // Check if the reader entry is valid
        {
            fprintf(file, "Reader ID: %d\n", rdr[i].id);
            fprintf(file, "Name: %s\n", rdr[i].name);
            fprintf(file, "Num Books Borrowed: %d\n", rdr[i].numBooksBorrowed);
            for (int j = 0; j < rdr[i].numBooksBorrowed; j++) {
                fprintf(file, "Borrowed Book ID %d: %d\n", j + 1, rdr[i].borrowedBooks[j]);
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Reader data saved to file.\n\n");
}


void loadBooksFromFile() {
    FILE *file = fopen("booklist.txt", "r");
    if (file == NULL) {
        return;
    }

    int i = 0;
    while (!feof(file) && i < 20) {
        fscanf(file, "Book ID: %d\n", &bk[i].id);
        fscanf(file, "Name: %s\n", bk[i].name);
        fscanf(file, "Author: %s\n", bk[i].author);
        fscanf(file, "Availability: %c\n", &bk[i].avbl);
        fscanf(file, "Reader ID: %d\n\n", &bk[i].rid);
        i++;
    }

    fclose(file);
}

void loadReadersFromFile() {
    FILE *file = fopen("readers.txt", "r");
    if (file == NULL) {
        return;
    }

    int i = 0;
    while (fscanf(file, "Reader ID: %d\n", &rdr[i].id) == 1) {
        fscanf(file, "Name: %[^\n]\n", rdr[i].name);
        fscanf(file, "Num Books Borrowed: %d\n", &rdr[i].numBooksBorrowed);
        for (int j = 0, k=1; j < rdr[i].numBooksBorrowed; j++, k++) {
            fscanf(file, "Borrowed Book ID %d: %d\n", &k, &rdr[i].borrowedBooks[j]);
        }
        fscanf(file, "\n");
        i++;
    }

    fclose(file);
}


void addBook() {
    char name[50], author[50];
    for (int i = 0; i < 20; i++) {
        if (bk[i].id == 0) // Find empty space in bk array
        {
            getchar();
            printf("Enter name of the book: ");
            gets(name);
            printf("Enter name of the author: ");
            gets(author);
            strcpy(bk[i].name, name);
            strcpy(bk[i].author, author);
            // Generate a new ID for the book
            bk[i].id = generateBookID();

            bk[i].avbl = 'y'; // Set availability to 'y'
            bk[i].rid = 0;    // Set reader's ID to 0 as default

            saveBooksToFile(); // Save the book list to a file

            printf("Book added successfully.\n\n");
            return; // Exit the function after adding the book
        }
    }

    printf("No more space available to add a book.\n\n");
}


void searchBook() {
    printf("Enter book ID: ");
    scanf("%d", &searchId);
    n = 0;
    for (int i = 0; i < 20; i++) {
        if (searchId == bk[i].id) {
            printf("\n\tBook Information\nBook ID: %d\tBook Name: %s\nAuthor Name: %s\nAvailable: %c\tDue by Reader ID: %d\n",
                   bk[i].id, bk[i].name, bk[i].author, bk[i].avbl, bk[i].rid);
            n++;
        }
    }
    if (n == 0) {
        printf("Book not found.\n\n");
    }
}

void addReader() {
    char name[50];
    for (int i = 0; i < 10; i++) {
        if (rdr[i].id == 0) // Find empty space in rdr array
        {
            getchar();
            printf("Enter Reader's name: ");
            gets(name);
            strcpy(rdr[i].name, name);
            // Generate a new ID for the reader
            rdr[i].id = generateReaderID();
            rdr[i].numBooksBorrowed = 0; // Initialize the number of borrowed books to 0

            saveReadersToFile();
            printf("Reader added successfully.\n\n");
            return; // Exit the function after adding the reader
        }
    }

    printf("No more space available to add a reader.\n\n");
}


void searchReader() {
    int searchId;
    printf("Enter Reader ID: ");
    scanf("%d", &searchId);

    int n = 0;
    for (int i = 0; i < 10; i++) {
        if (searchId == rdr[i].id) {
            printf("\n\tReader Information\nReader ID: %d\tReader Name: %s\nNum Books Borrowed: %d\n", rdr[i].id,
                   rdr[i].name, rdr[i].numBooksBorrowed);
            if (rdr[i].numBooksBorrowed > 0) {
                printf("Borrowed Book IDs: ");
                for (int j = 0; j < rdr[i].numBooksBorrowed; j++) {
                    printf("%d ", rdr[i].borrowedBooks[j]);
                }
                printf("\n");
            }
            n++;
        }
    }

    if (n == 0) {
        printf("Reader not found.\n\n");
    }
}


void issueBook() {
    int bookId, readerId;
    printf("Enter book ID: ");
    scanf("%d", &bookId);
    printf("Enter reader ID: ");
    scanf("%d", &readerId);

    int bookIndex = -1;
    int readerIndex = -1;

    // Find the book and reader indices
    for (int i = 0; i < 20; i++) {
        if (bookId == bk[i].id) {
            bookIndex = i;
            break;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (readerId == rdr[i].id) {
            readerIndex = i;
            break;
        }
    }

    // Check if the book and reader were found
    if (bookIndex != -1 && readerIndex != -1) {
        // Check if the book is available and the reader has no due book
        if (bk[bookIndex].avbl == 'y') {
            // Check if the reader has already borrowed the maximum number of books
            if (rdr[readerIndex].numBooksBorrowed >= 3) {
                printf("The maximum number of books have been borrowed by this reader. Book cannot be issued.\n\n");
                return;
            }

            // Issue the book to the reader
            bk[bookIndex].avbl = 'n';
            bk[bookIndex].rid = readerId;
            rdr[readerIndex].borrowedBooks[rdr[readerIndex].numBooksBorrowed] = bookId;
            rdr[readerIndex].numBooksBorrowed++;

            printf("Book issued successfully.\n\n");
            saveBooksToFile();
            saveReadersToFile();
        } else {
            printf("Book not issued.\n");
            if (bk[bookIndex].avbl == 'n') {
                printf("The book is not available.\n");
            }
            printf("\n");
        }
    } else {
        printf("Book or reader not found.\n\n");
    }
}


void submitBook() {
    int bookId;
    printf("Enter book ID: ");
    scanf("%d", &bookId);

    int bookIndex = -1;
    int readerId = -1;

    // Find the book index and get the reader ID
    for (int i = 0; i < 20; i++) {
        if (bookId == bk[i].id) {
            bookIndex = i;
            readerId = bk[i].rid;
            break;
        }
    }

    // Check if the book was found
    if (bookIndex != -1) {
        bk[bookIndex].avbl = 'y';
        bk[bookIndex].rid = 0;

        // Find the reader index and update due information
        for (int i = 0; i < 10; i++) {
            if (readerId == rdr[i].id) {

                // Remove the book from the reader's borrowedBooks array
                for (int j = 0; j < rdr[i].numBooksBorrowed; j++) {
                    if (rdr[i].borrowedBooks[j] == bookId) {
                        rdr[i].borrowedBooks[j] = rdr[i].borrowedBooks[rdr[i].numBooksBorrowed - 1];
                        rdr[i].numBooksBorrowed--;
                        break;
                    }
                }

                printf("Book ID %d submitted successfully.\n\n", bookId);
                saveBooksToFile();
                saveReadersToFile();
                return;
            }
        }
    }

    printf("Book ID %d not found or not borrowed.\n\n", bookId);
}


void deleteBook() {
    printf("Enter book ID to be deleted: ");
    scanf("%d", &searchId);
    n = 0;
    for (int i = 0; i < 20; i++) {
        if (searchId == bk[i].id) {
            for (i = i; i < 20; i++) {
                bk[i] = bk[i + 1];
            }
            n++;
        }
    }
    if (n != 0) {
        saveBooksToFile();
        printf("Book ID %d deleted.\n\n", searchId);
    } else
        printf("Book not found.\n\n");
}

void deleteReader() {
    printf("Enter reader ID to be deleted: ");
    scanf("%d", &searchId);
    n = 0;
    for (int i = 0; i < 10; i++) {
        if (searchId == rdr[i].id) {
            for (i = i; i < 10; i++) {
                rdr[i] = rdr[i + 1];
            }
            n++;
        }
    }
    if (n != 0) {
        printf("Reader ID %d deleted.\n\n", searchId);
    } else
        printf("Reader not found.\n\n");
}

void listBooks() {
    loadBooksFromFile();
    int n = 0;
    for (int i = 0; i < 20; i++) {
        if (bk[i].id != 0) {
            n++;
        }
    }

    printf("\n\t\tBook list\tTotal books: %d\n\nID\tName\t\t\tAuthor\t\t\tAvailable\tReader ID\n\n", n);

    for (int i = 0; i < 20; i++) {
        if (bk[i].id != 0) {
            printf("%d\t%s\t\t%s\t\t%c\t\t%d\n", bk[i].id, bk[i].name, bk[i].author, bk[i].avbl, bk[i].rid);
        }
    }
}

void listReaders() {
    loadReadersFromFile();

    int totalReaders = 0;
    for (int i = 0; i < 10; i++) {
        if (rdr[i].id != 0) {
            totalReaders++;
        }
    }


    printf("\n\t\tReaders List\tTotal readers: %d\n\nID\tName\t\t\tNum Books Borrowed\tBorrowed Book IDs\n\n",
           totalReaders);

    for (int i = 0; i < 10; i++) {
        if (rdr[i].id != 0) {
            printf("%d\t%s\t\t\t%d\t\t\t", rdr[i].id, rdr[i].name, rdr[i].numBooksBorrowed);
            if (rdr[i].numBooksBorrowed > 0) {
                for (int j = 0; j < rdr[i].numBooksBorrowed; j++) {
                    printf("%d ", rdr[i].borrowedBooks[j]);
                }
            }
            printf("\n");
        }
    }
}


void exitMenu() {
    printf("\n\t\tTHANK YOU!");
    exit(0);
}

void clearConsole() {
    system("cls");
}

void init() {
    loadBooksFromFile();
    loadReadersFromFile();
    if (loadUsersFromFile() == 0) {
        registerUser("admin", "admin");
        saveUsersToFile();
    }
}

void about() {
    printf("\033[1m"); // Set text to bold
    printf("\033[0;32m");
    printf("\n\t\tAbout\n\t=========================\n");
    printf("\033[0;34m");
    printf("Librarry Management project made by:\n\n");
    printf("\033[0;32m");
    printf("1. Nadim Mahmud Rabbi\n2. A S M Mahmudul Hasan\n3. Pavel Mahmud\n4. Fatema Sahab Senjuty\n5.Muktarul Islam\n");
    printf("\033[0m");
}

void menu() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    do {
        printf("\033[0m");
        printf("\n\tLibrary Management System\n\t=========================\n");
        printf("1. Add new book\t\t2. Search book\n3. Add new reader\t4. Search reader\n5. Issue book\t\t6. Submit book\n7. Delete book\t\t8. Delete reader\n9. List of books\t10. List of Readers\n11. Register a User\t12. About\n13. Exit\n\n");
        printf("\033[0;32m");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\033[0m");
        switch (choice) {

            case 1:
                addBook();
                break;

            case 2:
                searchBook();
                break;

            case 3:
                addReader();
                break;

            case 4:
                searchReader();
                break;

            case 5:
                issueBook();
                break;

            case 6:
                submitBook();
                break;

            case 7:
                deleteBook();
                break;

            case 8:
                deleteReader();
                break;

            case 9:
                listBooks();
                break;
            case 10:
                listReaders();
                break;
            case 11:
                printf("Enter username: ");
                fgets(username, MAX_USERNAME_LENGTH, stdin);
                username[strcspn(username, "\n")] = '\0'; // Remove newline character
                printf("Enter password: ");
                fgets(password, MAX_PASSWORD_LENGTH, stdin);
                password[strcspn(password, "\n")] = '\0'; // Remove newline character
                registerUser(username, password);
                saveUsersToFile();
            case 12:
                about();
                break;
            case 13:
                printf("\n\t\tTHANK YOU!");
                exit(0);
            default:
                printf("Invalid choice.\n\n");
                break;
        }

    } while (choice != 13);
}

int main() {
    init();
    printf("\033[0;31m");
    printf("\n\t\tWELCOME!");
    printf("\033[0m");
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("\n\nEnter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character
    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character
    int userIdx = findUser(username, password);
    if (userIdx != -1) {
        printf("Welcome %s!\n", username);
        menu();
    } else {
        printf("Invalid username or password.\n");
    }
    return 0;
}
