#include <stdio.h>

void print_frame(int frame[], int capacity)
{
    printf("Frame: ");
    for (int i = 0; i < capacity; i++)
    {
        if (frame[i] == -1)
            printf("_ ");
        else
            printf("%d ", frame[i]);
    }
    printf("\n");
}

void fifo(int pages[], int n, int capacity)
{
    int frame[capacity], index = 0, faults = 0;
    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int page = pages[i], found = 0;

        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            frame[index] = page;
            index = (index + 1) % capacity;
            faults++;
        }

        print_frame(frame, capacity);
    }

    printf("Total Page Faults (FIFO): %d\n", faults);
}

void lru(int pages[], int n, int capacity)
{
    int frame[capacity], timeStamp[capacity], faults = 0; // timestamp stors when was
                                                          // this index used last time
    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int page = pages[i], found = 0;

        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == page)
            {
                found = 1;
                timeStamp[j] = i + 1;
                break;
            }
        }

        if (!found)
        {
            int least_recent = 0;
            for (int j = 1; j < capacity; j++)
            {
                if (timeStamp[j] < timeStamp[least_recent])
                    least_recent = j;
            }
            frame[least_recent] = page;
            timeStamp[least_recent] = i + 1;
            faults++;
        }

        print_frame(frame, capacity);
    }

    printf("Total Page Faults (LRU): %d\n", faults);
}

void optimal(int pages[], int n, int capacity)
{
    int frame[capacity], faults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int page = pages[i], found = 0;

        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == page)
            {
                found = 1;
                break;
            }
        }
        // 2 4 5
        // 2 4 5 1 2 4 5

        if (!found)
        {
            int replace_index = -1, farthestIndexInUse = i + 1;

            for (int j = 0; j < capacity; j++)
            {
                int next_use = n; // to show if the index is not found
                                  // it will be n, the max index
                for (int k = i + 1; k < n; k++)
                {
                    if (frame[j] == pages[k])
                    {
                        next_use = k;
                        break;
                    }
                }

                if (next_use >= farthestIndexInUse)
                {
                    farthestIndexInUse = next_use;
                    replace_index = j;
                }

                if (replace_index == -1 || next_use == n)
                {
                    replace_index = j;
                    break;
                }
            }

            frame[replace_index] = page;
            faults++;
        }

        print_frame(frame, capacity);
    }

    printf("Total Page Faults (Optimal): %d\n", faults);
}

int main()
{
    int n, capacity, choice;
    printf("Enter number of pages: "); // The array that we have to fit in the memory
    scanf("%d", &n);

    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter the frame capacity: ");
    scanf("%d", &capacity); // the capacity we have

    do
    {
        printf("Choose Page Replacement Algorithm:\n1. FIFO\n2. LRU\n3. Optimal\n4. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fifo(pages, n, capacity);
            break;
        case 2:
            lru(pages, n, capacity);
            break;
        case 3:
            optimal(pages, n, capacity);
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
