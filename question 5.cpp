#include <stdio.h>
#include <string.h>

void displayMenu()
{
    printf("\nUniversity Library Menu:"); 
    printf("1. Member Registration\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    printf("Enter name: ");
    scanf(" %[^\n]", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);

    printf("Membership type (1 = Student, 2 = Faculty): ");
    scanf("%d", memberType);

    while (*memberType != 1 && *memberType != 2)
    {
        printf("Invalid type. Enter 1 for Student or 2 for Faculty: ");
        scanf("%d", memberType);
    }

    printf("Registration successful.\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks)
{
    int i;

    printf("\n%-10s %-30s %-10s\n", "Book ID", "Title", "Available");
    for (i = 0; i < totalBooks; i++)
    {
        printf("%-10d %-30s %-10d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType)
{
    int id, days, i, index = -1, limit;

    if (*borrowedCount >= 3)
    {
        printf("You have already borrowed 3 books. Return one first.\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &id);

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
            index = i;
    }

    if (index == -1)
    {
        printf("Invalid book ID.\n");
        return;
    }

    if (availableCopies[index] == 0)
    {
        printf("Sorry, no copies of this book are available.\n");
        return;
    }

    printf("Enter number of days you want to keep the book: ");
    scanf("%d", &days);

    while (days <= 0)
    {
        printf("Days must be positive. Enter again: ");
        scanf("%d", &days);
    }

    if (memberType == 1)
        limit = 14;
    else
        limit = 30;

    if (days > limit)
        printf("Note: the permitted period is %d days. A fine applies after that.\n", limit);

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[index]--;

    printf("You borrowed \"%s\".\n", bookTitles[index]);
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine)
{
    int id, days, i, pos = -1, index = -1, limit, rate, extra;
    float fine = 0, payable = 0;
    char code[20];

    if (*borrowedCount == 0)
    {
        printf("You have no borrowed books to return.\n");
        return 0;
    }

    printf("Enter book ID to return: ");
    scanf("%d", &id);

    for (i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == id)
            pos = i;
    }

    if (pos == -1)
    {
        printf("You have not borrowed this book.\n");
        return 0;
    }

    printf("Enter number of days the book was kept: ");
    scanf("%d", &days);

    while (days <= 0)
    {
        printf("Days must be positive. Enter again: ");
        scanf("%d", &days);
    }

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
            index = i;
    }

    availableCopies[index]++;

    if (memberType == 1)
    {
        limit = 14;
        rate = 20;
    }
    else
    {
        limit = 30;
        rate = 10;
    }

    if (days > limit)
    {
        extra = days - limit;
        fine = extra * rate;
        printf("Book returned %d day(s) late. Fine: Rs. %.2f\n", extra, fine);

        printf("Enter membership code: ");
        scanf("%s", code);

        if (strcmp(code, "LIB2026") == 0)
        {
            payable = fine / 2;
            printf("Code accepted. 50%% waiver applied.\n");
        }
        else
        {
            payable = fine;
            printf("Wrong code. No waiver applied.\n");
        }

        printf("Fine payable for this return: Rs. %.2f\n", payable);
    }
    else
    {
        printf("Book returned on time. No fine.\n");
    }

    *totalFine = *totalFine + fine;

    for (i = pos; i < *borrowedCount - 1; i++)
    {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    (*borrowedCount)--;

    return payable;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver)
{
    int i;

    printf("\n----- Member Record -----\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);

    if (memberType == 1)
        printf("Membership type: Student\n");
    else
        printf("Membership type: Faculty\n");

    printf("Currently borrowed books: ");
    if (borrowedCount == 0)
    {
        printf("None");
    }
    else
    {
        for (i = 0; i < borrowedCount; i++)
        {
            printf("%d ", borrowedBookIDs[i]);
        }
    }
    printf("\n");

    printf("Total fine before waiver: Rs. %.2f\n", totalFine);
    printf("Final fine payable: Rs. %.2f\n", fineAfterWaiver);
}

int main()
{
    int bookIDs[5] = {101, 102, 103, 104, 105};
    char bookTitles[5][50] = {
        "C Programming",
        "Data Structures",
        "Database Systems",
        "Operating Systems",
        "Computer Networks"
    };
    int availableCopies[5] = {3, 2, 1, 2, 1};
    int totalBooks = 5;

    char name[50];
    int studentID = 0, memberType = 0;
    int borrowedBookIDs[3];
    int borrowedCount = 0;
    float totalFine = 0, fineAfterWaiver = 0;
    int registered = 0;
    int choice;

    do
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (registered == 1)
                {
                    printf("A member is already registered.\n");
                }
                else
                {
                    registerMember(name, &studentID, &memberType);
                    registered = 1;
                }
                break;

            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;

            case 3:
                if (registered == 0)
                    printf("Please register first.\n");
                else
                    borrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
                break;

            case 4:
                if (registered == 0)
                    printf("Please register first.\n");
                else
                    fineAfterWaiver = fineAfterWaiver + returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                break;

            case 5:
                if (registered == 0)
                    printf("Please register first.\n");
                else
                    displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
                break;

            case 6:
                printf("Exiting the program. Goodbye.\n");
                break;

            default:
                printf("Invalid choice. Please enter a number from 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}
