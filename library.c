#include <stdio.h>

int choice, searchId, searchId1, n, m;
struct reader              //Define structure reader
{
    int id;               //id stores reader id
    char name[20];        //name stores reader's name
    char due;               //due stores y/n for if any book is due by particular leader
    int dbid;               //dbid stores due book's id
} rdr[10] = {0};              //rdr array is initialised with structure of reader

struct book                  //structure book defined
{
    int id;                 //id here stores book id
    char name[30];          //name stores name of the book
    char author[20];        //author stores name of the author
    char avbl;              //avbl stores availability of the book as y/n
    int rid;                //rid stores reader id having the book
} bk[20] = {0};

int generateBookID()
{
    int maxID = 0;

    for (int i = 0; i < 20; i++)
    {
        if (bk[i].id != 0 && bk[i].id > maxID)
        {
            maxID = bk[i].id;
        }
    }

    return maxID + 1;
}


int generateReaderID()
{
    int maxID = 0;

    for (int i = 0; i < 10; i++)
    {
        if (rdr[i].id != 0 && rdr[i].id > maxID)
        {
            maxID = rdr[i].id;
        }
    }

    return maxID + 1;
}

void saveBooksToFile()
{
    FILE *file = fopen("booklist.txt", "w");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    for (int i = 0; i < 20; i++)
    {
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

void saveReadersToFile()
{
    FILE *file = fopen("readers.txt", "w");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        if (rdr[i].id != 0)    // Check if the book entry is valid
        {
            fprintf(file, "Reader ID: %d\n", rdr[i].id);
            fprintf(file, "Name: %s\n", rdr[i].name);
            fprintf(file, "Due: %c\n", rdr[i].due);
            fprintf(file, "Due Book ID: %d\n\n", rdr[i].dbid);
        }
    }

    fclose(file);
    printf("Reader saved successfully.\n\n");
}

void loadBooksFromFile()
{
    FILE *file = fopen("booklist.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    int i = 0;
    while (!feof(file) && i < 20)
    {
        fscanf(file, "Book ID: %d\n", &bk[i].id);
        fscanf(file, "Name: %s\n", bk[i].name);
        fscanf(file, "Author: %s\n", bk[i].author);
        fscanf(file, "Availability: %c\n", &bk[i].avbl);
        fscanf(file, "Reader ID: %d\n\n", &bk[i].rid);
        i++;
    }

    fclose(file);
}

void loadReadersFromFile()
{
    FILE* file = fopen("readers.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "Reader ID: %d\n", &rdr[i].id) == 1)
    {
        fscanf(file, "Name: %s\n", rdr[i].name);
        fscanf(file, "Due: %c\n", &rdr[i].due);
        fscanf(file, "Due Book ID: %d\n\n", &rdr[i].dbid);
        i++;
    }

    fclose(file);
}


void addBook()
{
    for (int i = 0; i < 20; i++)
    {
        if (bk[i].id == 0)    // Find empty space in bk array
        {
            printf("Enter name of the book: ");
            scanf("%s", bk[i].name);
            printf("Enter name of the author: ");
            scanf("%s", bk[i].author);

            // Generate a new ID for the book
            bk[i].id = generateBookID();

            bk[i].avbl = 'y';   // Set availability to 'y'
            bk[i].rid = 0;      // Set reader's ID to 0 as default

            saveBooksToFile();  // Save the book list to a file

            printf("Book added successfully.\n\n");
            return;            // Exit the function after adding the book
        }
    }

    printf("No more space available to add a book.\n\n");
}

void searchBook()
{
    printf("Enter book ID: ");
    scanf("%d", &searchId);
    n = 0;
    for (int i = 0; i < 20; i++)
    {
        if (searchId == bk[i].id)
        {
            printf("\n\tBook Information\nBook ID: %d\tBook Name: %s\nAuthor Name: %s\nAvailable: %c\tDue by Reader ID: %d\n",
                   bk[i].id, bk[i].name, bk[i].author, bk[i].avbl, bk[i].rid);
            n++;
        }
    }
    if (n == 0)
    {
        printf("Book not found.\n\n");
    }
}

void addReader()
{
    for (int i = 0; i < 10; i++)
    {
        if (rdr[i].id == 0)    // Find empty space in rdr array
        {
            printf("Enter Reader's name: ");
            scanf("%s", rdr[i].name);

            // Generate a new ID for the reader
            rdr[i].id = generateReaderID();

            rdr[i].due = 'n';
            rdr[i].dbid = 0;
            saveReadersToFile();
            printf("Reader added successfully.\n\n");
            return;           // Exit the function after adding the reader
        }
    }

    printf("No more space available to add a reader.\n\n");
}

void searchReader()
{
    printf("Enter Reader ID: ");
    scanf("%d", &searchId);
    n = 0;
    for (int i = 0; i < 10; i++)
    {
        if (searchId == rdr[i].id)
        {
            printf("\n\tReader Information\nReader ID: %d\tReader Name: %s\nDue: %c\t\tDue book ID: %d\n", rdr[i].id,
                   rdr[i].name, rdr[i].due, rdr[i].dbid);
            n++;
        }
    }
    if (n == 0)
    {
        printf("Reader not found.\n\n");
    }
}

void issueBook()
{
    printf("Enter book ID: ");
    scanf("%d", &searchId);
    printf("Enter reader ID: ");
    scanf("%d", &searchId1);
    n = 0;
    m = 0;
    for (int i = 0; i < 20; i++)
    {
        if (searchId == bk[i].id && bk[i].avbl == 'y')
        {
            bk[i].avbl = 'n';
            bk[i].rid = searchId1;
            n++;
            i = 20;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        if (searchId1 == rdr[i].id && rdr[i].due == 'n')
        {
            rdr[i].due = 'y';
            rdr[i].dbid = searchId;
            m++;
            i = 10;
        }
    }
    if (n == 1 && m == 1)
    {
        printf("Book issued successfully.\n\n");
    }
    else if (n == 1 && m == 0)
    {
        for (int i = 0; i < 20; i++)
        {
            if (searchId == bk[i].id)
            {
                bk[i].avbl = 'y';
                bk[i].rid = 0;
                i = 20;
            }
        }
        printf("Book not issued.\nReader has a due book.\n\n");
    }
}

void submitBook()
{
    printf("Enter book ID: ");
    scanf("%d", &searchId);
    for (int i = 0; i < 20; i++)
    {
        if (searchId == bk[i].id)
        {
            bk[i].avbl = 'y';
            searchId1 = bk[i].rid;
            bk[i].rid = 0;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        if (searchId1 == rdr[i].id)
        {
            rdr[i].due = 'n';
            rdr[i].dbid = 0;
        }
    }
    printf("Book ID %d submitted successfully.\n\n", searchId);
}

void deleteBook()
{
    printf("Enter book ID to be deleted: ");
    scanf("%d", &searchId);
    n = 0;
    for (int i = 0; i < 20; i++)
    {
        if (searchId == bk[i].id)
        {
            for (i = i; i < 20; i++)
            {
                bk[i] = bk[i + 1];
            }
            n++;
        }
    }
    if (n != 0)
    {
        saveBooksToFile();
        printf("Book ID %d deleted.\n\n", searchId);
    }
    else
        printf("Book not found.\n\n");
}

void deleteReader()
{
    printf("Enter reader ID to be deleted: ");
    scanf("%d", &searchId);
    n = 0;
    for (int i = 0; i < 10; i++)
    {
        if (searchId == rdr[i].id)
        {
            for (i = i; i < 10; i++)
            {
                rdr[i] = rdr[i + 1];
            }
            n++;
        }
    }
    if (n != 0)
    {
        printf("Reader ID %d deleted.\n\n", searchId);
    }
    else
        printf("Reader not found.\n\n");
}

void listBooks()
{
    loadBooksFromFile();
    int n = 0;
    for (int i = 0; i < 20; i++)
    {
        if (bk[i].id != 0)
        {
            n++;
        }
    }

    printf("\n\t\tBook list\tTotal books: %d\n\nID\tName\t\t\tAuthor\t\t\tAvailable\tReader ID\n\n", n);

    for (int i = 0; i < 20; i++)
    {
        if (bk[i].id != 0)
        {
            printf("%d\t%s\t\t%s\t\t%c\t\t%d\n", bk[i].id, bk[i].name, bk[i].author, bk[i].avbl, bk[i].rid);
        }
    }
}

void listReaders()
{
    loadReadersFromFile();
    int n = 0;
    for (int i = 0; i < 10; i++)
    {
        if (rdr[i].id != 0)
        {
            n++;
        }
    }

    printf("\n\t\tReaders List\tTotal readers: %d\n\nID\tName\t\t\tDue\t\t\tDB ID\n\n", n);

    for (int i = 0; i < 10; i++)
    {
        if (rdr[i].id != 0)
        {
            printf("%d\t%s\t\t%c\t\t%d\n", rdr[i].id, rdr[i].name, rdr[i].due, rdr[i].dbid);
        }
    }
}


void exitMenu()
{
    printf("\n\t\tTHANK YOU!");
    exit(0);
}

void clearConsole()
{
    system("cls");
}

void init()
{
    loadBooksFromFile();
    loadReadersFromFile();
}

void about()
{
    printf("\033[1m"); // Set text to bold
    printf("\033[0;32m");
    printf("\n\t\tAbout\n\t=========================\n");
    printf("\033[0;34m");
    printf("Librarry Management project made by:\n\n");
    printf("\033[0;32m");
    printf("1. Nadim Mahmud Rabbi\n2. A S M Mahmudul Hasan\n3. Pavel Mahmud\n4. Fatema Sahab Senjuty\n5.Muktarul Islam\n");
    printf("\033[0m");
}

int main()
{
    init();
    printf("\033[0;31m");
    printf("\n\t\tWELCOME!");               //Welcome message

    do                              //do-while loop is used to return to main menu after every case is over.i.e.task is done
    {
        printf("\033[0m");
        printf("\n\tLibrary Management System\n\t=========================\n");
        printf("1. Add new book\t\t2. Search book\n3. Add new reader\t4. Search reader\n5. Issue book\t\t6. Submit book\n7. Delete book\t\t8. Delete reader\n9. List of books\t10. List of Readers\n11. About\t\t11. Exit\n\n");
        printf("\033[0;32m");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\033[0m");
        switch (choice)
        {

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
            about();
            break;
        case 12:
            exitMenu();
            break;
        default:
            printf("Invalid choice.\n\n");
            break;
        }

    }
    while (choice != 12);

    return 0;
}
