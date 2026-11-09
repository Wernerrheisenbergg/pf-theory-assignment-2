#include <stdio.h>

int main()
{
    int hall[50][50];
    int rows, seats, k;
    int i, j, d, c;
    int total = 0, rowcount, count;
    int mid, row, found = 0, start = 0;

    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of seats per row: ");
    scanf("%d", &seats);

    if (rows <= 0 || rows > 50 || seats <= 0 || seats > 50)
    {
        printf("Invalid hall size.\n");
        return 0;
    }

    printf("Enter seating status (0 = available, 1 = booked):\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < seats; j++)
        {
            scanf("%d", &hall[i][j]);
        }
    }

    printf("\nSeating Arrangement\n");
    printf("     ");
    for (j = 0; j < seats; j++)
    {
        printf("%d ", j);
    }
    printf("\n");
    for (i = 0; i < rows; i++)
    {
        printf("%d    ", i);
        for (j = 0; j < seats; j++)
        {
            if (hall[i][j] == 0)
                printf("_ ");
            else
                printf("X ");
        }
        printf("\n");
    }

    printf("\nSeat Availability Report\n");
    for (i = 0; i < rows; i++)
    {
        rowcount = 0;
        for (j = 0; j < seats; j++)
        {
            if (hall[i][j] == 0)
                rowcount++;
        }
        printf("Row %d: %d available\n", i, rowcount);
        total += rowcount;
    }
    printf("Total available seats: %d\n", total);

    printf("\nEnter number of customers: ");
    scanf("%d", &k);

    if (k <= 0 || k > seats)
    {
        printf("Invalid group size.\n");
        return 0;
    }

    mid = rows / 2;

    for (d = 0; d < rows && !found; d++)
    {
        for (c = 0; c < 2 && !found; c++)
        {
            if (c == 0)
                row = mid - d;
            else
                row = mid + d;

            if (c == 1 && d == 0)
                continue;
            if (row < 0 || row >= rows)
                continue;

            count = 0;
            for (j = 0; j < seats; j++)
            {
                if (hall[row][j] == 0)
                {
                    count++;
                    if (count == k)
                    {
                        found = 1;
                        start = j - k + 1;
                        break;
                    }
                }
                else
                {
                    count = 0;
                }
            }
        }
    }

    if (found)
    {
        row = row;
        for (j = start; j < start + k; j++)
        {
            hall[row][j] = 1;
        }
        total = total - k;

        printf("\nBooking successful.\n");
        printf("Row: %d\n", row);
        printf("Seats: ");
        for (j = start; j < start + k; j++)
        {
            printf("%d ", j);
        }
        printf("\n");

        printf("\nUpdated Seating Arrangement\n");
        printf("     ");
        for (j = 0; j < seats; j++)
        {
            printf("%d ", j);
        }
        printf("\n");
        for (i = 0; i < rows; i++)
        {
            printf("%d    ", i);
            for (j = 0; j < seats; j++)
            {
                if (hall[i][j] == 0)
                    printf("_ ");
                else
                    printf("X ");
            }
            printf("\n");
        }

        printf("\nRemaining available seats: %d\n", total);
    }
    else
    {
        printf("\nNo row has %d consecutive available seats.\n", k);
    }

    return 0;
}
